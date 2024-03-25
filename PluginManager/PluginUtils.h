#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include <cstring>
#include <filesystem>
#include <functional>
#include <iostream>
#include <string>


#if defined(__unix__) || defined(__APPLE__)
#  include <dlfcn.h>
#  include <unistd.h>
#endif

class PIM_LOGGER
{
public:
    /// Used by the PluginManager to log info messages
    ///
    /// The default implementation logs to std::cout, but this can be overridden
    /// by clients of the PluginManager by calling \ref setLogInfoHandler
    static void info(std::string const& msg)
    {
        instance().logInfoHandler(msg);
    }

    /// Used by the PluginManager to log error messages
    ///
    /// The default implementation logs to std::cerr, but this can be overridden
    /// by clients of the PluginManager by calling \ref setLogErrorHandler
    static void error(std::string const& msg)
    {
        instance().logErrorHandler(msg);
    }

    /// Allows clients of the PluginManager to set their own info logging function
    static void setLogInfoHandler(std::function<void(std::string)> const& logInfoFunc)
    {
        instance().logInfoHandler = logInfoFunc;
    };

    /// Allows clients of the PluginManager to set their own error logging function
    static void setLogErrorHandler(std::function<void(std::string)> const& logErrorFunc)
    {
        instance().logErrorHandler = logErrorFunc;
    };

private:
    std::function<void(std::string)> logInfoHandler  = [](std::string const& msg) { std::cout << "[INFO]  PluginManager:  " << msg << std::endl; };
    std::function<void(std::string)> logErrorHandler = [](std::string const& msg) { std::cerr << "[ERROR] PluginManager:  " << msg << std::endl; };

    PIM_LOGGER() = default;
    PIM_LOGGER(PIM_LOGGER const&) = delete;
    PIM_LOGGER& operator=(PIM_LOGGER const&) = delete;

    static PIM_LOGGER& instance()
    {
        static PIM_LOGGER instance;
        return instance;
    }

};

// [DO NOT MERGE] RKERR TODO : Improve this file:
//       - test on and handle more platforms
//       - split into h/cpp to remove inlines
//       - consider using boost, for example executable path from
//         boost::dll::program_location -- or remove the assumption about
//         executable path

namespace plugin::detail
{

inline void *libraryOpen(const char *filename)
{
#if defined(_WIN32)
    return ((void*)LoadLibrary(filename));
#elif defined(__unix__) || defined(__APPLE__)
    return dlopen(filename, RTLD_NOW | RTLD_GLOBAL);
#else
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.");
#endif
}

inline void *librarySymbol(void *handle, const char *symbol)
{
#if defined(_WIN32)
    return ((void*)GetProcAddress((HINSTANCE)handle, symbol));
#elif defined(__unix__) || defined(__APPLE__)
    return dlsym(handle, symbol);
#else
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.");
#endif
}

inline int libraryClose(void *handle)
{
#if defined(_WIN32)
    return FreeLibrary((HINSTANCE)handle);
#elif defined(__unix__) || defined(__APPLE__)
    return dlclose(handle);
#else
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.");
#endif
}

inline std::filesystem::path GetApplicationPath()
{
#if defined(__unix__) || defined(__APPLE__)
    const size_t bufSize = 512;
    char nameBuf[bufSize] = {0};
    const auto retVal = readlink("/proc/self/exe", nameBuf, bufSize);
    if (retVal < 0) {
        PIM_LOGGER::error("Failed to read application path with error " + std::to_string(errno) +  ":" + std::strerror(errno));
        return {};
    }

    return std::filesystem::path{ nameBuf }.remove_filename();
#else
    static_assert(false, "This platform is not yet handled, please update PluginUtils.h and submit a change request.");
#endif
}

template<typename OUTVECT, typename APPENDEDVECT>
inline void AppendVector(OUTVECT& outputVector, APPENDEDVECT const& inputVector)
{
    if(!inputVector.empty())
    {
        outputVector.insert(end(outputVector), cbegin(inputVector), cend(inputVector));
    }
}

} // end namespaces

#endif

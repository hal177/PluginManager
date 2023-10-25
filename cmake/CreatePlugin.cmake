# Create a plugin library
#
# This macro creates a plugin library with the given name and type.
#
# PLUGIN: The name of the plugin library to create
# PLUGIN_TYPE:  The type of plugin to create.  This is used to determine the
#               installation location of the plugin.  Valid values are:
#
#               - "TEST":  This is a test plugin.  It will be installed in the
#                          test plugin directory.
#
macro(CreatePluginMacro PLUGIN PLUGIN_TYPE)
    string(COMPARE EQUAL "${PLUGIN_TYPE}" TEST _cmp)
    if(NOT _cmp)
        message(FATAL_ERROR "Invalid plugin type: ${PLUGIN_TYPE} for plugin ${PLUGIN}")
    endif()

    message("Creating plugin ${PLUGIN}")

    add_library(${PLUGIN} SHARED
            ${${PLUGIN}_SRC}
            ${${PLUGIN}_HDR}
        )

    target_link_libraries(${PLUGIN} PUBLIC
            ${${PLUGIN}_LIB}
        )

    message(VERBOSE "Adding include directories for ${PLUGIN}: ${${PLUGIN}_INC}")
    target_include_directories(${PLUGIN}
        PRIVATE
            ${${PLUGIN}_INC}
        )

    foreach(LIB ${${PLUGIN}_LIB})
        message(VERBOSE "Adding include directories for ${PLUGIN}: $<TARGET_PROPERTY:${LIB},INTERFACE_INCLUDE_DIRECTORIES>")
        target_include_directories(${PLUGIN}
            PRIVATE
            $<TARGET_PROPERTY:${LIB},INTERFACE_INCLUDE_DIRECTORIES>
            )
    endforeach()

    if(_cmp)
        # See the if statement at the top, this assumes that the plugin type is TEST for now
        message(VERBOSE "Copying test plugin ${PLUGIN}")

        if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
            # This is the top-level project
            message(STATUS "This is the top-level project.")
            set_target_properties(${PLUGIN} PROPERTIES
                LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Test/plugins
            )
        else()
            # This is being included from another project
            message(STATUS "This is being included from another project.")
            set_target_properties(${PLUGIN} PROPERTIES
                LIBRARY_OUTPUT_DIRECTORY ${pluginmanager_BINARY_DIR}/Test/plugins
            )
        endif()

    endif()

endmacro()

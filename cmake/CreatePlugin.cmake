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
    string(COMPARE EQUAL "${PLUGIN_TYPE}" TEST _isTestPlugin)
    if(NOT _isTestPlugin)
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

    if(_isTestPlugin)
        message(VERBOSE "Setting output directory for ${PLUGIN} to ${CMAKE_BINARY_DIR}/Test/plugins")
        set_target_properties(${PLUGIN} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Test/plugins/
        )
    endif()

endmacro()

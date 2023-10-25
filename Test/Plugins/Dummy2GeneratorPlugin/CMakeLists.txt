set(TARGET Dummy2GeneratorPlugin)

set(${TARGET}_HDR
  ${CMAKE_CURRENT_SOURCE_DIR}/Dummy2Generator.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Dummy2GeneratorPlugin.h
  )

set(${TARGET}_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/Dummy2Generator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Dummy2GeneratorPlugin.cpp
  )

set(${TARGET}_INC
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  )

set(${TARGET}_LIB
  PluginManager
  )

CreatePluginMacro(${TARGET} TEST)


cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.15)
project(QPluginFrameworkDemo VERSION 1.0.0)

set(PROJ_HOME ${CMAKE_CURRENT_SOURCE_DIR})
message("PROJ_HOME" ${PROJ_HOME})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/pluginspackage)

set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_EXECUTABLE_SUFFIX "_d")

add_subdirectory(PluginsManager)
add_subdirectory(PluginsPackageDemo)
add_subdirectory(AppDemo)

cmake_minimum_required(VERSION 3.14)

project(PluginsPackageDemo LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets LinguistTools)

set(TS_FILES PluginsPackageDemo_zh_CN.ts)

include(../Interface/PluginsCore/PluginsCore.cmake)
include(../Interface/PluginsDemo/PluginsDemo.cmake)

add_library(PluginsPackageDemo SHARED
    PluginDemo.cpp
    PluginDemo.h
    PluginsPackageDemo.cpp
    PluginsPackageDemo.h
    PluginsPackageDemo.json
    ${TS_FILES}
    ${Interface}
)

target_link_libraries(PluginsPackageDemo PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(PluginsPackageDemo PROPERTIES SUFFIX ".plugin")

target_compile_definitions(PluginsPackageDemo PRIVATE PLUGINSPACKAGEDEMO_LIBRARY)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

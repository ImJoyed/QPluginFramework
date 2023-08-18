cmake_minimum_required(VERSION 3.14)

project(UiPluginsPackageDemo LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets LinguistTools)

set(TS_FILES UiPluginsPackageDemo_zh_CN.ts)

include(../Interface/PluginsCore/PluginsCore.cmake)
include(../Interface/UiPluginsDemo/UiPluginsDemo.cmake)

add_library(UiPluginsPackageDemo SHARED
    CommandPlugin.cpp
    CommandPlugin.h
    ToolPlugin.cpp
    ToolPlugin.h
    DockPlugin.cpp
    DockPlugin.h
    WindowPlugin.cpp
    WindowPlugin.h
    UiPluginsPackageDemo.cpp
    UiPluginsPackageDemo.h
    UiPluginsPackageDemo.json
    Resource/Resource.qrc
    ${TS_FILES}
    ${Interface}
)

target_link_libraries(UiPluginsPackageDemo PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(UiPluginsPackageDemo PROPERTIES SUFFIX ".plugin")

target_compile_definitions(UiPluginsPackageDemo PRIVATE UIPLUGINSPACKAGEDEMO_LIBRARY)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

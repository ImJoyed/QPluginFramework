﻿cmake_minimum_required(VERSION 3.14)

project(PluginsManager LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets LinguistTools)

set(TS_FILES PluginsManager_zh_CN.ts)

include(../Interface/PluginsCore/PluginsCore.cmake)
include(../Interface/PluginsManager/PluginsManager.cmake)
include(../Interface/Ui/Ui.cmake)

add_library(PluginsManager SHARED
    PluginsManager.cpp
    PluginsManager.h
    PluginsManager.json
    ${TS_FILES}
    ${Interface}
)

target_link_libraries(PluginsManager PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(PluginsManager PROPERTIES SUFFIX ".plugin")

link_directories(${PROJECT_SOURCE_DIR}/Build/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib)
target_link_libraries(PluginsManager PRIVATE Ui)

target_compile_definitions(PluginsManager PRIVATE PLUGINSMANAGER_LIBRARY)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

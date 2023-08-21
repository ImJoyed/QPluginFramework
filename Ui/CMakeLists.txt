cmake_minimum_required(VERSION 3.14)

project(Ui LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets LinguistTools)

set(TS_FILES Ui_zh_CN.ts)

include(../Interface/Ui/Ui.cmake)

set(SRC_FILES
    RibbonPanel.cpp
    RibbonCategory.cpp
    RibbonBar.cpp
    SubWindowList.cpp
    ${TS_FILES}
    ${Interface}
)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_library(Ui SHARED ${SRC_FILES})
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_library(Ui ${SRC_FILES})
ENDIF()
target_link_libraries(Ui PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Build/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib)
#set_target_properties(RibbonUi PROPERTIES SUFFIX ".plugin")

target_compile_definitions(Ui PRIVATE UI_LIBRARY)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

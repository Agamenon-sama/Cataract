cmake_minimum_required(VERSION 3.5)

project(cataract VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Define include path
include_directories("${CMAKE_SOURCE_DIR}/include")

set(PROJECT_SOURCES
        src/main.cpp
        src/utils.cpp
        src/utils.h
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/gui/mainwindow.ui
        src/gui/scanresultmodel.cpp
        src/gui/scanresultmodel.h
        src/Cataract/core.h
        src/Cataract/core.cpp
        src/Cataract/tcpScanner.h
        src/Cataract/tcpScanner.cpp
        src/Cataract/Cataract.h
        static/res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cataract
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cataract APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(cataract SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(cataract
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(cataract PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(cataract PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cataract)
endif()

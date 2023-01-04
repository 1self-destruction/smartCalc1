cmake_minimum_required(VERSION 3.5)

project(smartCalc1 VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/iseestarz/Qt/6.4.1/gcc_64/lib/cmake/Qt6/")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(QCustomPlot-library)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        input_x.cpp
        input_x.h
        input_x.ui
        graph.cpp
        graph.h
        graph.ui
        credit.cpp
        credit.h
        credit.ui
        SmartCalc_v1_0.c
        SmartCalc_v1_0.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smartCalc1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET smartCalc1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(smartCalc1 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(smartCalc1
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(smartCalc1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(smartCalc1 PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE qcustomplot)

set_target_properties(smartCalc1 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smartCalc1)
endif()

cmake_minimum_required(VERSION 3.22)
project(QDesktopPet_2_cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(PROJECT_SOURCES
        main.cpp
        widget.h
        widget.cpp
        QLive2dWidget.hpp
        mouseEventThread.cpp
        mouseEventThread.h
        )

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        X11Extras
        OpenGL
        REQUIRED)

add_executable(QDesktopPet_2_cmake main.cpp)
target_link_libraries(QDesktopPet_2_cmake
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::X11Extras
        Qt5::OpenGL
        -lX11 -lXext -lXi
        -lLive2dWidget
        -lGL
        -lFramework
        -lLive2DCubismCore
        -L.
        )
target_sources(QDesktopPet_2_cmake
        PRIVATE
        main.cpp
        QLive2dWidget.hpp
        widget.cpp
        widget.h
        mouseEventThread.cpp
        mouseEventThread.h
)


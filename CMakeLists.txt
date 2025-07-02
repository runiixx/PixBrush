cmake_minimum_required(VERSION 3.31)
project(PixBrush)

set(CMAKE_CXX_STANDARD 23)
target_link_libraries(PixBrush PRIVATE raylib rimgui)
target_include_directories(PixBrush PRIVATE /usr/include)
add_executable(PixBrush main.cpp
        gui/windows/create_new_project_menu.cpp
        gui/windows.h
        gui/windows/main_window.cpp
        chunk/chunk.h
        chunk/chunk.cpp
        chunk/chunk_renderer.cpp
        gui/components/textbox.cpp
        gui/components.h
        input/keyboard_input.cpp
        input/keyboard_input.h
        chunk/chunk_fill.cpp
        input/brushes.cpp
        logger/logger.h)

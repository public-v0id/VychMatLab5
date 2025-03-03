cmake_minimum_required(VERSION 2.8)

project(VychMatLab2)

find_package(cln::ginac)

find_package(Qt5 REQUIRED
        Core
        Gui
        Widgets)

set(SOURCES src/main.cpp src/methods.cpp src/window.cpp)

add_executable(lab ${SOURCES})

target_include_directories(lab PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(lab ginac Qt5::Widgets Qt5::Gui)

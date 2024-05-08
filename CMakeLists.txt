cmake_minimum_required(VERSION 3.2)
project(CSFMLintro C)

set(CMAKE_C_STANDARD 11)

add_executable(CSFMLintro main.c)
include_directories( ${CMAKE_SOURCE_DIR}/CSFML/include)
target_link_libraries(CSFMLintro ${CMAKE_SOURCE_DIR}/CSFML/lib/msvc/csfml-window.lib)
target_link_libraries(CSFMLintro ${CMAKE_SOURCE_DIR}/CSFML/lib/msvc/csfml-graphics.lib)
target_link_libraries(CSFMLintro ${CMAKE_SOURCE_DIR}/CSFML/lib/msvc/csfml-system.lib)

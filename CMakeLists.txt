cmake_minimum_required(VERSION 3.2)
project(Warcaby C)

set(CMAKE_C_STANDARD 11)

add_executable(Warcaby main.c
        Auxilary.c
        Board.c
        Displayer.c
        GameLogicHandler.c
        MoveHandler.c
        Piece.c
        Auxilary.h
        Board.h
        Displayer.h
        GameLogicHandler.h
        MoveHandler.h
        Piece.h
        Displayer.h
        GameFileHandler.c
        GameFileHandler.h
)
include_directories( ${CMAKE_SOURCE_DIR}/CSFML/include)
target_link_libraries(Warcaby ${CMAKE_SOURCE_DIR}/CSFML/lib/msvc/csfml-window.lib)
target_link_libraries(Warcaby ${CMAKE_SOURCE_DIR}/CSFML/lib/msvc/csfml-graphics.lib)
target_link_libraries(Warcaby ${CMAKE_SOURCE_DIR}/CSFML/lib/msvc/csfml-system.lib)

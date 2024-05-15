//
// Created by Wojciech on 14.05.2024.
//

#ifndef WARCABY_GAMESTATEHANDLER_H
#define WARCABY_GAMESTATEHANDLER_H
#pragma once
#include "Board.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



enum GameState{
    BlackWon,WhiteWon,Draw,InGame
} typedef GameState;

struct GameStateHandler{
    Board * board;

    char * gameDirectory;
    char * currentGameFile;
}typedef GameStateHandler;
void initializeGameStateHandler(GameStateHandler * gameStateHandler,Board * board,PieceColour turn);
GameState getGameState(GameStateHandler* gameStateHandler);

void readBoardFromFile(GameStateHandler *gameStateHandler, Board *board);
PieceColour  readTurnFromTheFile(GameStateHandler gameStateHandler);
void resetBoardFile(GameStateHandler* gameStateHandler);
void saveGame(GameStateHandler *gameStateHandler, PieceColour turn);

bool isGameDirectoryEmpty(GameStateHandler * gameStateHandler);
Board constructBoardFromFile(FILE *file);






#endif //WARCABY_GAMESTATEHANDLER_H

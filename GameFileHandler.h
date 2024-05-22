
#ifndef WARCABY_GAMEFILEHANDLER_H
#define WARCABY_GAMEFILEHANDLER_H
#pragma once
#include "Board.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>





struct GameFileHandler{
    Board * board;
    char * gameDirectory;
    char * currentGameFile;
}typedef GameFileHandler;
void initializeGameFileHandler(GameFileHandler * gameFileHandler, Board * board, PieceColour turn);

void readBoardFromFile(GameFileHandler *gameFileHandler, Board *board);
PieceColour  readTurnFromTheFile(GameFileHandler gameFileHandler);
void resetBoardFile(GameFileHandler* gameFileHandler);
void saveGame(GameFileHandler *gameFileHandler, PieceColour turn);

bool isGameDirectoryEmpty(GameFileHandler * gameFileHandler);
Board constructBoardFromFile(FILE *file);






#endif //WARCABY_GAMEFILEHANDLER_H

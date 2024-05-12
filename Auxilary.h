#pragma once
#include "SFML/Graphics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0
#define BOARD_SIZE 5
#define WINDOW_SIZE 500
#define DARK_TILE_COLOUR "#252525"
#define LIGHT_TILE_COLOUR "#d18978"
#define DARK_PIECE_COLOUR "#691717"
#define LIGHT_PIECE_COLOUR "#fefdf8"



enum PieceColour { Black, White }typedef PieceColour;

sfColor hex_to_sfColor(const char* hex);

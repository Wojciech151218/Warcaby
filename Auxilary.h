#pragma once
#include "SFML/Graphics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#define bool int
#define true 1
#define false 0
#define BOARD_SIZE 10
#define WINDOW_SIZE 1000
#define DARK_TILE_COLOUR "#252525"
#define LIGHT_TILE_COLOUR "#d18978"
#define DARK_PIECE_COLOUR "#691717"
#define LIGHT_PIECE_COLOUR "#fefdf8"




enum PieceColour { Black, White }typedef PieceColour;

sfColor hex_to_sfColor(const char* hex);
char* sum_strings(char* str1, char* str2);
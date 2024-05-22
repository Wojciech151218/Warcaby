#include "Auxilary.h"
struct Square {
    int x, y;
}typedef Square;

bool equalSquare(Square a, Square b);
bool isSquareOnTheBoard(Square square);
Square minusSquare(Square a, Square b);
Square plusSquare(Square a, Square b);
Square multiplySquare(Square a,int factor);
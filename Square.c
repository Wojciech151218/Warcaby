#pragma once
#include "Square.h"
bool equalSquare(Square a, Square b) {
    return a.x == b.x && a.y == b.y;
}
Square multiplySquare(Square a,int factor){
    return (Square){a.x*factor,a.y*factor};
}
Square minusSquare(Square a, Square b) {
    return (Square){a.x-b.x,a.y-b.y};
}
Square plusSquare(Square a, Square b) {
    return (Square){a.x+b.x,a.y+b.y};
}
int distanceBetweenSquares(Square a, Square b){
    return abs(a.x-b.x);
}
bool isSquareOnTheBoard(Square square){
    return !(square.x<0 || square.y< 0 || square.x >= BOARD_SIZE || square.y >= BOARD_SIZE);
}


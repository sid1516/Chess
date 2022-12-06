//
// Created by Siddharth Tangri on 11/30/22.
//
#include "../headers/Piece.h"

Piece::Piece(Team t, int xCoord, int yCoord): team(t),x(xCoord), y(yCoord) {}

Piece::PieceType Piece::getPieceType() {
    return pieceType;
}
Piece::Team Piece::getTeam() {
    return team;
}

int Piece::getX() {
    return x;
}
int Piece::getY() {
    return y;
}
void Piece::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Piece::setHasMoved(bool moved) {
    hasMoved = moved;
}
bool Piece::getHasMoved() {
    return hasMoved;
}


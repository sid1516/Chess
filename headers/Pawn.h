#pragma once
#include "Piece.h"

class Pawn: public Piece {
public:
    Pawn(Team t, int x, int y);
    const std::vector<std::vector<Direction>>& getPossibleMoves();
};

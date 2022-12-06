#pragma once
#include "Piece.h"

class Knight: public Piece {
public:
    Knight(Team t, int x, int y);
    const std::vector<std::vector<Direction>>& getPossibleMoves();
};
//
// Created by Siddharth Tangri on 11/30/22.
//

#pragma once
#include "Piece.h"

class Bishop: public Piece {
    public:
        Bishop(Team t, int x, int y);
        const std::vector<std::vector<Direction>>& getPossibleMoves();
};

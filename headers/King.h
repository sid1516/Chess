//
// Created by Siddharth Tangri on 11/30/22.
//
#include "Piece.h"
class King: public Piece {
public:
    King(Team t, int x, int y);
    const std::vector<std::vector<Direction>>& getPossibleMoves();
};

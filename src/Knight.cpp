//
// Created by Siddharth Tangri on 11/30/22.
//

#include "../headers/Knight.h"

Knight::Knight(Team t, int x, int y): Piece(t, x, y) {
    possibleMoves = {{{2, 1}},
                     {{-2, -1}},
                     {{-2, 1}},
                     {{2, -1}},
                     {{1, 2}},
                     {{-1, -2}},
                     {{-1, 2}},
                     {{1, -2}},};
    pieceType = PieceType::KNIGHT;
}
const std::vector<std::vector<Piece::Direction>>& Knight::getPossibleMoves(){
    return possibleMoves;
}


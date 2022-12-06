//
// Created by Siddharth Tangri on 11/30/22.
//
//
// Created by Siddharth Tangri on 11/30/22.
//

#include "../headers/King.h"

King::King(Team t, int x, int y): Piece(t, x, y) {
    possibleMoves = {{{1, 0}},
                     {{-1, 0}},
                     {{1, 1}},
                     {{-1, -1}},
                     {{1, -1}},
                     {{-1, 1}},
                     {{0, 1}},
                     {{0, -1}}};
    pieceType = PieceType::KING;
}
const std::vector<std::vector<Piece::Direction>>& King::getPossibleMoves(){
    return possibleMoves;
}



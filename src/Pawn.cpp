//
// Created by Siddharth Tangri on 11/30/22.
//

#include "../headers/Pawn.h"

//Change according to piece color;
Pawn::Pawn(Team t, int x, int y): Piece(t, x, y) {
    possibleMoves = {{{1, 0}, {2,0}},
                     {{1, 1}},
                     {{1, -1}},};
    pieceType = PieceType::PAWN;
}
const std::vector<std::vector<Piece::Direction>>& Pawn::getPossibleMoves(){
    return possibleMoves;
}


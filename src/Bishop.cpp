//
// Created by Siddharth Tangri on 11/30/22.
//

#include "../headers/Bishop.h"

Bishop::Bishop(Team t, int x, int y): Piece(t, x, y) {
    std::vector<Direction> topLeft;
    std::vector<Direction> topRight;
    std::vector<Direction> bottomLeft;
    std::vector<Direction> bottomRight;
    for(int i = 1; i <= 7; i++) {
        topLeft.push_back({-i, -i});
        topRight.push_back({-i, i});
        bottomLeft.push_back({i, -i});
        bottomRight.push_back({i, i});
    }
    possibleMoves.emplace_back(topLeft);
    possibleMoves.emplace_back(topRight);
    possibleMoves.emplace_back(bottomLeft);
    possibleMoves.emplace_back(bottomRight);
    pieceType = PieceType::BISHOP;
}
const std::vector<std::vector<Piece::Direction>>& Bishop::getPossibleMoves(){
    return possibleMoves;
}


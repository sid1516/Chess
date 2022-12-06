
//
// Created by Siddharth Tangri on 11/30/22.
//
#include "../headers/Rook.h"

Rook::Rook(Team t, int x, int y): Piece(t,x,y) {
    std::vector<Direction> left;
    std::vector<Direction> right;
    std::vector<Direction> bottom;
    std::vector<Direction> top;
    for(int i = 1; i <= 7; i++) {
        left.push_back({0, -i});
        right.push_back({0, i});
        top.push_back({-i, 0});
        bottom.push_back({i, 0});
    }
    possibleMoves.emplace_back(left);
    possibleMoves.emplace_back(right);
    possibleMoves.emplace_back(bottom);
    possibleMoves.emplace_back(top);

    pieceType = PieceType::ROOK;
}
const std::vector<std::vector<Piece::Direction>>& Rook::getPossibleMoves(){
    return possibleMoves;
}


//
// Created by Siddharth Tangri on 11/30/22.
//
#include "../headers/Queen.h"

Queen::Queen(Team t, int x, int y): Piece(t, x, y) {
    std::vector<Direction> topLeft;
    std::vector<Direction> topRight;
    std::vector<Direction> bottomLeft;
    std::vector<Direction> bottomRight;
    std::vector<Direction> left;
    std::vector<Direction> right;
    std::vector<Direction> bottom;
    std::vector<Direction> top;
    for(int i = 1; i <= 7; i++) {
        topLeft.push_back({-i, -i});
        topRight.push_back({-i, i});
        bottomLeft.push_back({i, -i});
        bottomRight.push_back({i, i});
        left.push_back({0, -i});
        right.push_back({0, i});
        top.push_back({-i, 0});
        bottom.push_back({i, 0});
    }
    possibleMoves.emplace_back(topLeft);
    possibleMoves.emplace_back(topRight);
    possibleMoves.emplace_back(bottomLeft);
    possibleMoves.emplace_back(bottomRight);
    possibleMoves.emplace_back(left);
    possibleMoves.emplace_back(right);
    possibleMoves.emplace_back(bottom);
    possibleMoves.emplace_back(top);

    pieceType = PieceType::QUEEN;
}
const std::vector<std::vector<Piece::Direction>>& Queen::getPossibleMoves(){
    return possibleMoves;
}

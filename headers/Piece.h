//
// Created by Siddharth Tangri on 11/30/22.
//

#pragma once

#include<vector>
#include<iostream>

class Piece {
public:
    struct Direction {
        int x, y;
        Direction(int xCoord, int yCoord): x(xCoord), y(yCoord) {}
    };
    enum Team {WHITE = 1, BLACK = 0};

    enum PieceType {PAWN = 2, ROOK = 3, KNIGHT = 4, BISHOP = 5, KING = 6, QUEEN = 7};

    Piece(Team t, int x, int y);

    virtual const std::vector<std::vector<Direction>>& getPossibleMoves() = 0;

    virtual ~Piece() = default;

    PieceType getPieceType();

    Team getTeam();

    void setPosition(int x, int y);

    int getX();

    int getY();

    void setHasMoved(bool moved);

    bool getHasMoved();

protected:
    std::vector<std::vector<Direction>> possibleMoves;
    Team team;
    PieceType pieceType;
    bool hasMoved = false;
    int x;
    int y;
};

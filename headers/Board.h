//
// Created by Siddharth Tangri on 11/30/22.
//
#pragma once
#include "Piece.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include <vector>
#include <iostream>
class Board {
public:
    struct Point {
        int x, y;
        Point(int x, int y): x(x), y(y) {};
        bool operator==(const Point& other) const {
            return (x == other.x) && (y == other.y);
        }
    };
    Piece* board[8][8] = {nullptr};
    Board();
    ~Board();
    std::vector<Point> calcLegalMoves(Piece * piece);
    void movePiece(Piece* piece, int newX, int newY);
    int getMoveNumber() const;
    bool isStalemate(Piece::Team team);
    bool isCheckmate(Piece::Team team);

private:
    int moveNumber = 1;
    std::vector<Point> calcMovesKing(King* king);
    std::vector<Point> calcMovesPawn(Pawn* pawn);
    std::vector<Point> calcPseudoLegalMoves(Piece* piece);
    void castle(int newX, int newY);
    King* blackKing;
    King* whiteKing;
    Pawn* enPassantPawn = nullptr;
    bool controlsSquare(int x, int y, Piece::Team team);
    bool notCheck(Piece* piece,  int newX, int newY);
    bool cantMove(Piece::Team team);
};

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Board.h"

using namespace sf;

void handleCastling(std::vector<Sprite>& sprites, int newX, int newY) {
    if(newX == 0) {
        if(newY == 2) {
            sprites[0].setPosition(450, 0);
        } else {
            sprites[7].setPosition(750, 0);
        }
    } else {
        if(newY == 2) {
            sprites[24].setPosition(450, 1050);
        } else {
            sprites[31].setPosition(750, 1050);
        }
    }
}

int main()
{
    RenderWindow window(VideoMode(1200, 1200), "Chess");



    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13;
    t1.loadFromFile("resources/board.png");
    t2.loadFromFile("resources/BlackBishop.png");
    t3.loadFromFile("resources/WhiteBishop.png");
    t4.loadFromFile("resources/BlackKing.png");
    t5.loadFromFile("resources/WhiteKing.png");
    t6.loadFromFile("resources/BlackKnight.png");
    t7.loadFromFile("resources/WhiteKnight.png");
    t8.loadFromFile("resources/BlackPawn.png");
    t9.loadFromFile("resources/WhitePawn.png");
    t10.loadFromFile("resources/BlackQueen.png");
    t11.loadFromFile("resources/WhiteQueen.png");
    t12.loadFromFile("resources/BlackRook.png");
    t13.loadFromFile("resources/WhiteRook.png");

    Sprite chessBoard(t1);

    chessBoard.setScale(1.02915951973, 1.02915951973);

    Sprite BlackBishop(t2);
    Sprite WhiteBishop(t3);
    Sprite BlackKing(t4);
    Sprite WhiteKing(t5);
    Sprite BlackKnight(t6);
    Sprite WhiteKnight(t7);
    Sprite BlackPawn(t8);
    Sprite WhitePawn(t9);
    Sprite BlackQueen(t10);
    Sprite WhiteQueen(t11);
    Sprite BlackRook(t12);
    Sprite WhiteRook(t13);

    std::vector<Sprite> pieces(32, WhiteKing);
    std::vector<bool> piecesExist(32, true);
    for(int i = 0; i < 16; i++) {
        if(i == 0 || i == 7) {
            pieces[i] = BlackRook;
            pieces[31-i] = WhiteRook;
        } else if(i == 1 || i == 6) {
            pieces[i] = BlackKnight;
            pieces[31-i] = WhiteKnight;
        } else if(i == 2 || i == 5) {
            pieces[i] = BlackBishop;
            pieces[31- i] = WhiteBishop;
        } else if(i == 3) {
            pieces[i] = BlackQueen;
            pieces[31 - i] = WhiteKing;
        } else if(i == 4) {
            pieces[i] = BlackKing;
            pieces[31 - i] = WhiteQueen;
        } else {
            pieces[i] = BlackPawn;
            pieces[31-i] = WhitePawn;
        }
    }
    for(int i = 0; i < pieces.size(); i++) pieces[i].setScale(2.5,2.5);

    Board b;

    int index = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(b.board[i][j] != nullptr) {
                pieces[index++].setPosition(j * 150, i * 150);
            }
        }
    }

    Piece* piece = nullptr;
    int pieceIndex = -1;
//    sf::RectangleShape finalResult;
//    finalResult.setSize({400, 400});
//    finalResult.setPosition(400, 400);
//    Text resultString;
//    resultString.setPosition(400, 600);
//    resultString.setColor(sf::Color::Black);
//    bool gameEnd = false;
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.key.code == Mouse::Left) {
                    Vector2<int> pos =  sf::Mouse::getPosition(window);
                    for(int i = 0; i < pieces.size(); i++) {
                        if(piecesExist[i] && pieces[i].getGlobalBounds().contains(pos.x, pos.y)) {
                            auto coords =  pieces[i].getPosition();
                            int x = coords.x/150;
                            int y = coords.y/150;
                            if(b.board[y][x] && b.board[y][x] -> getTeam() == (b.getMoveNumber() % 2)) {
                                piece = b.board[y][x];
                                pieceIndex = i;
                            }
                            break;
                        }
                    }
                }
            }
            if (event.type == Event::MouseButtonReleased) {
                if(event.key.code == Mouse::Left) {
                    Vector2<int> pos =  sf::Mouse::getPosition(window);
                    int x = pos.x/150;
                    int y = pos.y/150;
                    for(Board::Point p : b.calcLegalMoves(piece)) {
                        if(p.x == y && p.y == x) {
                            if(b.board[y][x]) {
                                for(int i = 0; i < pieces.size(); i++) {
                                    auto [sx, sy] = pieces[i].getPosition();
                                    if(sx == (x * 150) && sy == (y * 150) && piecesExist[i]) {
                                        piecesExist[i] = false;
                                        break;
                                    }
                                }
                            } else {
                                if(piece -> getPieceType() == Piece::PieceType::PAWN && piece -> getY() != x) {
                                    int offset = (piece -> getTeam() == Piece::Team::WHITE) ? 1 : -1;
                                    for(int i = 0; i < pieces.size(); i++) {
                                        auto [sx, sy] = pieces[i].getPosition();
                                        if(sx == (x * 150) && sy == ((y+offset) * 150) && piecesExist[i]) {
                                            piecesExist[i] = false;
                                            break;
                                        }
                                    }
                                }
                            }
                            //Will have to check for en passant
                            if(piecesExist[pieceIndex] && piece ->getPieceType() == Piece::PieceType::PAWN && ((y == 7) || (y == 0))) {
                                pieces[pieceIndex] = (y == 7) ? BlackQueen : WhiteQueen;
                                pieces[pieceIndex].setScale(2.5, 2.5);
                            }
                            if(piecesExist[pieceIndex] && piece -> getPieceType() == Piece::PieceType::KING && abs(x - piece -> getY()) == 2) {
                                handleCastling(pieces, y, x);
                            }
                            b.movePiece(piece, y, x);
                            pieces[pieceIndex].setPosition(x * 150, y * 150);
                            piece = nullptr;
                            pieceIndex = -1;
                            break;
                        }
                    }
                }
            }
        }
        /* Draw */
        window.clear();
        window.draw(chessBoard);
        for(Board::Point& p : b.calcLegalMoves(piece)) {
            sf::RectangleShape rectangle;
            rectangle.setSize({150, 150});
            rectangle.setPosition(p.y * 150, p.x * 150);
            rectangle.setFillColor(sf::Color::Cyan);
            rectangle.setOutlineColor(sf::Color::Black);
            rectangle.setOutlineThickness(2);
            window.draw(rectangle);
        }
        for(int i = 0; i < pieces.size(); i++) {
            if(piecesExist[i]) window.draw(pieces[i]);
        }
        window.display();
    }
}

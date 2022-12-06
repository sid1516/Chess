//
// Created by Siddharth Tangri on 11/30/22.
//
#include "../headers/Board.h"

Board::Board() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j <= 7; j+=7) {
            Piece::Team team = (j == 0) ? Piece::Team::BLACK : Piece::Team::WHITE;
            if(i == 0 || i == 7) {
                board[j][i] = new Rook(team, j, i);
            } else if(i == 1 || i == 6) {
                board[j][i] = new Knight(team, j, i);
            } else if(i == 2 || i == 5) {
                board[j][i] = new Bishop(team, j, i);
            } else if(i == 3) {
                board[j][i] = new Queen(team, j, i);
            } else {
                board[j][i] = new King(team, j, i);
            }
            if(j == 0) {
                board[j+1][i] = new Pawn(team, j+1, i);
            } else {
                board[j-1][i] = new Pawn(team, j-1, i);
            }
        }
    }
    blackKing = (King*)board[0][4];
    whiteKing = (King*)board[7][4];
}

Board::~Board() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}

std::vector<Board::Point> Board::calcPseudoLegalMoves(Piece* piece) {
    std::vector<Point> points;
    if(!piece) {
        return points;
    }
    if(piece -> getPieceType() == Piece::PieceType::PAWN) {
        return calcMovesPawn((Pawn*) piece);
    }
    if(piece -> getPieceType() == Piece::PieceType::KING) {
        return calcMovesKing((King*) piece);
    }
    const std::vector<std::vector<Piece::Direction>>& directions = piece -> getPossibleMoves();
    int x = piece -> getX();
    int y = piece -> getY();
    for(size_t i = 0; i < directions.size(); i++) {
        for(size_t j = 0; j < directions[i].size(); j++) {
            const Piece::Direction& d = directions.at(i).at(j);
            int newX = x + d.x;
            int newY = y + d.y;
            if(newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
                break;
            }
            if(!board[newX][newY]) {
                points.push_back({newX, newY});
            } else {
                if(board[newX][newY]->getTeam() != piece->getTeam()) {
                    points.push_back({newX, newY});
                }
                break;
            }
        }
    }
    return points;
}

void Board::movePiece(Piece* piece, int newX, int newY) {
//    std::cout << newX << ", " << newY << std::endl;
//    std::cout << !board[newX][newY] << std::endl;
//    std::cout << (piece ->getPieceType() == Piece::PieceType::PAWN) << std::endl;
//    std::cout <<  (newY != piece -> getY()) << std::endl;
    if(!board[newX][newY] && (piece ->getPieceType() == Piece::PieceType::PAWN) && (newY != piece -> getY())) {
        std::cout << "entered" << std::endl;
        if(piece -> getTeam() == Piece::WHITE) {
            delete board[newX + 1][newY];
            board[newX + 1][newY] = nullptr;
        } else {
            delete board[newX - 1][newY];
            board[newX - 1][newY] = nullptr;
        }
    }
    enPassantPawn = (piece -> getPieceType() == Piece::PieceType::PAWN && abs(newX - piece -> getX()) == 2)
            ? (Pawn*) piece : nullptr;

    if(board[newX][newY]) {
        delete board[newX][newY];
        board[newX][newY] = nullptr;
    }
    board[piece->getX()][piece->getY()] = nullptr;
    if(piece -> getPieceType() == Piece::PieceType::PAWN && (newX == 7 || newX == 0)) {
        Piece::Team team = (newX == 0) ? Piece::Team::WHITE : Piece::Team::BLACK;
        delete piece;
        piece = new Queen(team, newX, newY);
    }
    if(piece -> getPieceType() == Piece::PieceType::KING && abs(newY - piece ->getY()) == 2) {
        castle(newX, newY);
    }
    board[newX][newY] = piece;
    piece->setPosition(newX, newY);
    piece ->setHasMoved(true);
    moveNumber++;
}
std::vector<Board::Point> Board::calcMovesPawn(Pawn* pawn) {
    std::vector<Board::Point> points;
    const std::vector<std::vector<Piece::Direction>>& directions = pawn -> getPossibleMoves();
    int mult = 1;
    if(pawn -> getTeam() == Piece::Team::WHITE) {
        mult = -1;
    }
    int x = pawn -> getX();
    int y = pawn -> getY();

    for(int i = 0; i < directions.size(); i++) {
        for(int j = 0; j < directions[i].size(); j++) {
            const Piece::Direction& d = directions.at(i).at(j);
            int newX = x + (mult * d.x);
            int newY = y + d.y;
            if(newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
                break;
            }
            if(d.x == 2 || d.x == -2 && d.y == 0) {
                if(!pawn ->getHasMoved() && board[newX][newY] == nullptr) {
                    points.push_back({newX, newY});
                }
            } else if(d.y == -1 || d.y == 1) {
                if(board[newX][newY] != nullptr && board[newX][newY] -> getTeam() != pawn -> getTeam()) {
                    points.push_back({newX, newY});
                }
            } else {
                if(board[newX][newY] == nullptr) {
                    points.push_back({newX, newY});
                } else {
                    break;
                }
            }
        }
    }
    if(enPassantPawn && enPassantPawn -> getTeam() != pawn -> getTeam()) {
        if(enPassantPawn->getX() == pawn -> getX() && abs(enPassantPawn -> getY() - pawn -> getY()) == 1) {
            int direction = (enPassantPawn -> getY() - pawn -> getY() == 1) ? 1 : -1;
            if(pawn -> getTeam() == Piece::Team::WHITE) {
                points.push_back({pawn -> getX() - 1, pawn -> getY() + direction});
            } else {
                points.push_back({pawn -> getX() + 1, pawn -> getY() + direction});
            }
        }
    }
    return points;
}

int Board::getMoveNumber() const {
    return moveNumber;
}

std::vector<Board::Point> Board::calcMovesKing(King* king) {
    std::vector<Point> points;
    const std::vector<std::vector<Piece::Direction>>& directions = king -> getPossibleMoves();
    int x = king -> getX();
    int y = king -> getY();
    for(size_t i = 0; i < directions.size(); i++) {
        for(size_t j = 0; j < directions[i].size(); j++) {
            const Piece::Direction& d = directions.at(i).at(j);
            int newX = x + d.x;
            int newY = y + d.y;
            if(newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
                break;
            }
            if(!board[newX][newY]) {
                points.push_back({newX, newY});
            } else {
                if(!board[newX][newY]->getTeam() == king->getTeam()) {
                    points.push_back({newX, newY});
                }
                break;
            }
        }
    }
    if(king ->getTeam() == Piece::Team::WHITE) {
        if(board[7][7] && board[7][7]->getPieceType() == Piece::PieceType::ROOK && !board[7][7] ->getHasMoved()) {
            if(!king->getHasMoved() && !board[7][6] && !board[7][5] && board[7][7] -> getTeam() == Piece::Team::WHITE) {
                points.push_back({7, 6});
            }
        }
        if(board[7][0] && board[7][0] ->getPieceType() == Piece::PieceType::ROOK && !board[7][0] -> getHasMoved()) {
            if(!king->getHasMoved() && !board[7][1] && !board[7][2] && !board[7][3] && board[7][0] -> getTeam() == Piece::Team::WHITE) {
                points.push_back({7, 2});
            }
        }
    } else {
        if(board[0][7] && board[0][7]->getPieceType() == Piece::PieceType::ROOK && !board[0][7] ->getHasMoved()) {
            if(!king->getHasMoved() && !board[0][6] && !board[0][5] && board[0][7] -> getTeam() == Piece::Team::BLACK) {
                points.push_back({0, 6});
            }
        }
        if(board[0][0] && board[0][0] ->getPieceType() == Piece::PieceType::ROOK && !board[0][0] -> getHasMoved()) {
            if(!king->getHasMoved() && !board[0][1] && !board[0][2] && !board[0][3] && board[0][0] -> getTeam() == Piece::Team::BLACK) {
                points.push_back({0, 2});
            }
        }
    }
    return points;
}

void Board::castle(int newX, int newY) {
    Piece* piece;
    if(newX == 0) {
        if (newY == 2) {
            piece = board[0][0];
            board[0][0] = nullptr;
            board[0][3] = piece;
            piece->setPosition(0, 3);
        } else {
            piece = board[0][7];
            board[0][7] = nullptr;
            board[0][5] = piece;
            piece ->setPosition(0, 5);
        }
    }
    else {
        if(newY == 2) {
            piece = board[7][0];
            board[7][0] = nullptr;
            board[7][3] = piece;
            piece ->setPosition(7, 3);
        } else {
            piece = board[7][7];
            board[7][7] = nullptr;
            board[7][5] = piece;
            piece ->setPosition(7, 5);
        }
    }
    piece ->setHasMoved(true);
}
bool Board::controlsSquare(int x, int y, Piece::Team team) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            Piece* p = board[i][j];
            if(p && p -> getTeam() == team) {
                for(auto const [px, py] : calcPseudoLegalMoves(p)) {
                    if(px == x && py == y) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

std::vector<Board::Point> Board::calcLegalMoves(Piece * piece) {

    std::vector<Board::Point> points = calcPseudoLegalMoves(piece);
    std::vector<Board::Point> validPoints;
    if(!piece) {
        return validPoints;
    }
    for(Point p : points) {
        if(piece ->getPieceType() == Piece::PieceType::KING && abs(piece ->getY() - p.y) == 2) {
            int offset = (p.y - piece ->getY() > 0) ? 1 : -1;
            if(notCheck(piece, piece -> getX(), piece->getY()) &&
                notCheck(piece, piece -> getX(), piece->getY() + offset) &&
                notCheck(piece, piece -> getX(), piece->getY() + (2*offset))) {
                validPoints.emplace_back(p);
            }
        } else {
            if(notCheck(piece, p.x, p.y)) {
                validPoints.emplace_back(p);
            }
        }
    }
    return validPoints;
}
//Have to add the en passant move
bool Board::notCheck(Piece* piece, int newX, int newY) {
    Piece* temp = nullptr;
    Piece::Team team  = (piece -> getTeam() == Piece::Team::WHITE) ? Piece::Team::BLACK : Piece::Team::WHITE;
    King* king = (team == Piece::Team::BLACK)? whiteKing : blackKing;
    bool enPassant = (!board[newX][newY]) && piece ->getPieceType() == Piece::PieceType::PAWN && newY != piece -> getY();
    if(board[newX][newY]) {
        temp = board[newX][newY];
    } else {
        if(enPassant) {
            int direction = (enPassantPawn -> getY() - piece -> getY() == 1) ? 1 : -1;
            temp = board[piece -> getX()][piece -> getY() + direction];
            board[piece -> getX()][piece -> getY() + direction] = nullptr;
        }
    }
    board[newX][newY] = piece;
    board[piece ->getX()][piece -> getY()] = nullptr;
    bool result = false;
    result = (piece->getPieceType() == Piece::PieceType::KING) ?
            controlsSquare(newX, newY, team) : controlsSquare(king -> getX(), king -> getY(), team);
    if(enPassant) {
        int direction = (enPassantPawn -> getY() - piece -> getY() == 1) ? 1 : -1;
        board[piece -> getX()][piece -> getY() + direction] = temp;
        board[newX][newY] = nullptr;
    } else {
        board[newX][newY] = temp;
    }
    board[piece -> getX()][piece -> getY()] = piece;

    return !result;
}

bool Board::cantMove(Piece::Team team) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            Piece* p = board[i][j];
            if(p && p -> getTeam() == team) {
                if(calcLegalMoves(p).size() != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::isStalemate(Piece::Team team){
    King* king = (team == Piece::Team::WHITE) ? whiteKing : blackKing;
    Piece::Team opposingTeam = (team == Piece::Team::WHITE) ? Piece::Team::BLACK : Piece::Team::WHITE;
    return cantMove(team) && (!controlsSquare(king -> getX(), king -> getY(), opposingTeam));
}
bool Board::isCheckmate(Piece::Team team){
    King* king = (team == Piece::Team::WHITE) ? whiteKing : blackKing;
    Piece::Team opposingTeam = (team == Piece::Team::WHITE) ? Piece::Team::BLACK : Piece::Team::WHITE;
    return cantMove(team) && controlsSquare(king -> getX(), king -> getY(), opposingTeam);
}


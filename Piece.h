#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>

const int BOARD_SIZE = 8;

using namespace std;

class ChessBoard;

enum class Type : int {
    KING,
    QUEEN,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN,
    INVALID
};

enum class Color : int {
    WHITE,
    BLACK,
    INVALID
};


class Piece {

    friend class ChessBoard;

    private:

        int x;
        int y;
        Type type;
        Color color;
        ChessBoard* board;
        double value;
        bool moved;

    public:

        Piece();
        Piece(int _x, int _y, ChessBoard *_board, Type _type, Color _color, bool _moved, double _value);

        bool isKing() const;
        void setMoved(bool _moved);
        bool hasMoved() const;
        Type getType() const;
        Color getColor() const;
        double getValue() const;
        void setX(int _x);
        void setY(int _y);
        int getX() const;
        int getY() const;

};

#endif
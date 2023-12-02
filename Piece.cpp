#include "Piece.h"
#include "ChessBoard.h"

Piece::Piece()
{
    this->x = 0;
    this->y = 0;
    this->moved = false;
    this->board = nullptr;
    this->value = 0.0;
}

Piece::Piece(int _x, int _y, ChessBoard* _board, Type _type, Color _color, bool _moved, double _value) : 
    x(_x), 
    y(_y),
    board(_board),
    type(_type),
    color(_color),
    value(_value),
    moved(_moved)
{
    _board->setAt(_x, _y, this);
}



int   Piece::getX()     const {return this->x;}
int   Piece::getY()     const {return this->y;}
double   Piece::getValue() const {return this->value;}
Type  Piece::getType()  const {return this->type;}
Color Piece::getColor() const {return this->color;}
bool  Piece::hasMoved() const {return this->moved;}
bool  Piece::isKing()   const {return (this->type==Type::KING);}

void Piece::setMoved(bool _moved) {this->moved = _moved;}
void Piece::setX(int _x) {this->x = _x;}
void Piece::setY(int _y) {this->y = _y;}
#include "Move.h"

Move::Move()
{
    this->x_start     = 0;
    this->y_start     = 0;
    this->x_end       = 0;
    this->y_end       = 0;
}

Move::Move(int _xStart, int _yStart, int _xEnd, int _yEnd)
{
    this->x_start     = _xStart;
    this->y_start     = _yStart;
    this->x_end       = _xEnd;
    this->y_end       = _yEnd;
}


void Move::operator=(const Move M)
{
    this->x_start     = M.x_start;
    this->y_start     = M.y_start;
    this->x_end       = M.x_end;
    this->y_end       = M.y_end;
}

Move&  Move::reverse() 
{
    int startX = this->x_start;
    int startY = this->y_start;
    this->x_start = this->x_end;
    this->y_start = this->y_end;
    this->x_end = startX;
    this->y_end = startY;
    return *this;
}


int   Move::fromX()   const {return this->x_start;}
int   Move::fromY()   const {return this->y_start;}
int   Move::toX()     const {return this->x_end;}
int   Move::toY()     const {return this->y_end;}

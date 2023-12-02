#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

class Move {

    private:
        int x_start;
        int y_start;
        int x_end;
        int y_end;
        
    public:

        Move();
        Move(int _xStart, int _yStart, int _xEnd, int _yEnd);

        Move& reverse();
        void operator=(const Move M);
        int fromX() const;
        int fromY() const;
        int toX() const;
        int toY() const;
};

#endif
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include "Piece.h"
#include "Move.h"


using namespace std;

class Piece;


class ChessBoard {

    friend class Piece;

    private:

        vector<vector<Piece*>> gameboard;


    public:

        ChessBoard();
        ChessBoard(ChessBoard& chessboard);
        ~ChessBoard();

        void Initialize();
        void Display();
        void Clear();
        double EvaluateBoard();

            
        bool isLegal(const Move& move);
        bool isCheck(Color king_color);
        bool isMate(Color king_color);
        bool CanAttack(const Move& move);
        bool CanAttack(const Piece& obj, int attackX, int attackY);
        bool CanMove(const Move& move);
        bool CanMove(const string& move_str);
        bool CanMoveKing(const Move& move);
        bool MovePiece(const Move& move);
        bool MovePiece(const string& move_str);
        bool IsUnderThreat(const Piece& obj);
        bool IsUnderThreatByColor(const Color& color, int x, int y);
        static void DirectMove(ChessBoard& chessboard, const Move& move);
        

        vector<Move> CalculateVision(const Piece& obj);
        vector<Move> calcStraight(const Piece& obj);
        vector<Move> calcDiagonal(const Piece& obj);
        vector<Move> calcLShape(const Piece& obj);
        vector<Move> calcPawn(const Piece& obj);
        vector<Move> calcKing(const Piece& obj);

        bool inBorder(int x = 0, int y = 0);
        void setAt(const int x, const int y, Piece*);
        bool isEmpty(const int x, const int y) const;
        bool isBlack(const int x, const int y) const;
        bool isWhite(const int x, const int y) const;

        Piece& getKing(Color color) const;
        vector<Piece*> GetPieces(const Color& piece_color) const;
        bool   getPoint(const int x, const int y) const;
        Type   getType(const int x, const int y) const;

        void setAt(const Piece* obj, const int x, const int y);
        Piece* getAt(const int x, const int y) const;
        
        
};


#endif
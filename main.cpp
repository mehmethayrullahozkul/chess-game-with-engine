#include <iostream>
#include "Piece.h"
#include "ChessBoard.h"
#include "Gameplay.h"
#include "utils.h"
//#include "Piece.cpp"
//#include "Board.cpp"


using namespace std;

int main() 
{
    Game game("example_chess.txt");
    cout << endl;
    //game.Gameboard().Display();
    game.Gameplay();
}
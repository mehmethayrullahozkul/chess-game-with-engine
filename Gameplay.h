#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include <string>
#include <fstream>
#include "ChessBoard.h"
#include "Piece.h"
#include "Move.h"
#include "utils.h"

class Game;
using namespace std;


class Game {

    public:

        Game();
        Game(const string& filename);
        ~Game();

        // enter the gameplay of game
        void Gameplay();

        // save the game to file
        void SaveGame(const string& filename);

        // print out ending information
        void EndScreen(Color winner);

        // play the turn
        bool PlayTurnOnce();

        // perform the given move
        void PerformMove(const string& play_string);

        // get the gameboard object
        ChessBoard& Gameboard();

        // get the active turn
        Color ActiveTurn() const;

        // switch the active turn
        void SwitchTurn();

        // Load another game from file
        bool ReadFromFile(const string& filename);
        
        // Play the bot
        void PlayBot();
        
        // clear the old game and create new one
        void New();

        bool hasGameEnd() const;

        // clear the old game
        void Clear();

        bool IsPlayValid(string play_string);
        


        private:

            // Private data members

            ChessBoard* chessboard;
            Color active_turn;
            bool game_ended;

            // Private helper functions, 
            // end-user wont use them.

            string input();

            bool isMoveValidForTurn(const Move& move);
        

};




#endif
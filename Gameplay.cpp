#include "Gameplay.h"


Game::Game()
{
    this->chessboard = new ChessBoard();
    chessboard->Initialize();
    this->game_ended = false;
    this->active_turn = Color::WHITE;
}

Game::Game(const string& filename)
{
    this->chessboard = new ChessBoard();
    this->active_turn = Color::WHITE;
    this->game_ended = false;
    ReadFromFile(filename);
}


void Game::Gameplay()
{
    string main_menu;
    string game_menu;

    while(main_menu != "0")
    {
        main_menu = "";
        cout << "Welcome to chess game!" << endl << endl;
        cout << "1 - Play Game!" << endl;
        cout << "2 - New Game" << endl;
        cout << "3 - Load Game" << endl;
        cout << "4 - Save Game" << endl;
        cout << "0 - Exit" << endl;
        cout << "Select:  ";

        cin >> main_menu;

        if(main_menu == "1")
        {
            if(hasGameEnd())
            {
                Gameboard().Initialize();
                this->game_ended = false;
            }
            while(PlayTurnOnce());
        }
        else if(main_menu == "0")
        {
            cout << "Terminating the game." << endl;
            return;
        }
        else
        {
            cout << "You've entered a invalid option, try again." << endl;
        }
        
    }
}


bool Game::PlayTurnOnce() 
{
    bool   king_under_threat = false;
    string input_str = "";
    bool   play_valid = false;

    while(input_str != "q")
    {
        if(Gameboard().isMate(ActiveTurn()))
        {
           EndScreen(!ActiveTurn());
           return false;
        }
        Gameboard().Display();
        cout << ActiveTurn();
        if(Gameboard().isCheck(ActiveTurn()))
            cout << "Your king is under threat." << endl;
        
        while(!play_valid)
        {
            input_str = input();

            if(input_str == "q")
                return false;

            else if(input_str == "suggest")
            {
                //PlayBot();
                play_valid = true;
            } 
            else
            {
                // --input valid
                play_valid = IsPlayValid(input_str);
                
                if(!play_valid)
                {
                    cout << "move not valid" << endl;
                    continue;
                }
                // means play and input both valid so far
                
                Move move = strToMove(input_str);
                if(!Gameboard().isLegal(move))
                {
                    cout << "entered move is not legal" << endl;
                    continue;
                }
                if(Gameboard().MovePiece(input_str))
                    cout << "succesfully moved" << endl;
                cout << endl;
                SwitchTurn();
                return true;
            }
        }

        // check if game has ended or not?
        if(false) {}
        //PerformMove(input);
        return true;
    }
    return true;
}

void Game::SwitchTurn()
{
    this->active_turn = (this->active_turn == Color::BLACK) ? Color::WHITE : Color::BLACK;
}

ChessBoard& Game::Gameboard()
{
    return *(this->chessboard);
}

void Game::New()
{
    // delete the old chessboard and pieces
    this->Clear();
    // replace them with new one
    this->chessboard = new ChessBoard();
    this->active_turn = Color::WHITE;
}

void Game::EndScreen(Color winner)
{
    Gameboard().Display();
    if(winner==Color::BLACK)
        cout << endl << "***    The game has ended, winner Black.    ***" << endl;
    else
        cout << endl << "***    The game has ended, winner White.    ***" << endl;

    cout << endl << "press enter to continue..." << endl;
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cin.get();
    this->game_ended = true;
}



void Game::Clear()
{
    if(this->chessboard != nullptr)
    {
        for(int row = 0 ; row < BOARD_SIZE ; row++)
        {
            for(int column = 0 ; column < BOARD_SIZE ; column++)
            {
                if(chessboard->getAt(row, column) != nullptr) delete chessboard->getAt(row, column);
            }
        }
        delete chessboard;
    }
}

string Game::input()
{

    bool isValid = false;
    string input = "";
    while(!isValid)
    {
        cout << "Enter your move (or 'q' to quit): ";
        cin >> input;

        if(!validateInput(input))
            continue;

        isValid = true;
    }
    return input;
}




bool Game::isMoveValidForTurn(const Move& move)
{
    Piece* MovePiece = Gameboard().getAt(move.fromX(), move.fromY());
    if(MovePiece == nullptr) 
        return false;
    else if(MovePiece->getColor() == ActiveTurn())
        return true;
    return false;
}


bool Game::IsPlayValid(string play_string)
{
    Move move;
    move = strToMove(play_string);
    if(!isMoveValidForTurn(move))
        return false;

    return true;
}


Color Game::ActiveTurn() const
{
    return this->active_turn;
}

bool Game::hasGameEnd() const
{
    return this->game_ended;
}

bool Game::ReadFromFile(const string& filename)
{
    this->Clear();
    this->chessboard = new ChessBoard();
    ifstream read;
    string buffer;
    read.open(filename, ios::in);
    if(!read)
        return false;

    vector<vector<Piece*>> gameboard(BOARD_SIZE, vector<Piece*> (BOARD_SIZE, nullptr));
    int i = 0;
    int row = 0;
    int column = 0;
    while(read >> buffer && i < BOARD_SIZE * BOARD_SIZE)
    {
        
        if(buffer==".") 
        {
            i++;
            continue;
        }

        Type type   = strToType(buffer);
        Color color = strToColor(buffer);

        row    = i / (BOARD_SIZE);
        column = i % (BOARD_SIZE);
        Piece* piece = new Piece(column, row, this->chessboard, type, color, ((type==Type::PAWN) && (row==1 || row==BOARD_SIZE-2))? false : true, valueOfType(type));

        i++;
    }
    read >> buffer;
    this->active_turn = (buffer=="BLACK") ? Color::BLACK : Color::WHITE;
    read.close();
    return true;
}


Game::~Game()
{
    if(this->chessboard != nullptr)
    {
        for(int row = 0 ; row < BOARD_SIZE ; row++)
        {
            for(int column = 0 ; column < BOARD_SIZE ; column++)
            {
                if(chessboard->getAt(row, column) != nullptr) delete chessboard->getAt(row, column);
            }
        }
        delete chessboard;
    }
}
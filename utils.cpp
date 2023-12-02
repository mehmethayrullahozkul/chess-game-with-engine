#include "utils.h"


using namespace std;

ostream& operator << (ostream& out, const Piece& obj)
{
    if(obj.getColor() == Color::BLACK)
    {
        if(obj.getType() == Type::BISHOP)
            out << "b ";
        else if(obj.getType() == Type::ROOK)
            out << "r ";
        else if(obj.getType() == Type::QUEEN)
            out << "q ";
        else if(obj.getType() == Type::PAWN)
            out << "p ";
        else if(obj.getType() == Type::KING)
            out << "k ";
        else if(obj.getType() == Type::KNIGHT)
            out << "n ";
    }
    else if(obj.getColor() == Color::WHITE)
    {
        if(obj.getType() == Type::BISHOP)
            out << "B ";
        else if(obj.getType() == Type::ROOK)
            out << "R ";
        else if(obj.getType() == Type::QUEEN)
            out << "Q ";
        else if(obj.getType() == Type::PAWN)
            out << "P ";
        else if(obj.getType() == Type::KING)
            out << "K ";
        else if(obj.getType() == Type::KNIGHT)
            out << "N "; 
    }
    return out;
}

bool operator == (const Move& M1, const Move& M2)
{
    if(M1.fromX() == M2.fromX() && M2.toX() == M2.toY())
        return true;
    return false;
}

ostream& operator << (ostream& out, const Move& M)
{
    out << "X: " << M.fromX() << " Y: " << M.fromY() << " | X: " << M.toX() << " Y: " << M.toY() << endl;
    return out;
}

ostream& operator << (ostream& out, std::vector<Move>& M)
{
    for(int i = 0 ; i < M.size() ; i++)
        out << M[i];
    return out;
}

ostream& operator << (ostream& out, const Color t)
{
    if(t == Color::BLACK)
        out << "[Black's Turn]" << endl;
    else if (t == Color::WHITE)
        out << "[White's Turn]" << endl;
    return out;
}

double valueOfType(Type _type)
{
    if(_type==Type::BISHOP)
        return 3.0;
    else if(_type==Type::ROOK)
        return 5.0;
    else if(_type==Type::KING)
        return 20.0;
    else if(_type==Type::KNIGHT)
        return 3.0;
    else if(_type==Type::PAWN)
        return 1.0;
    else if(_type==Type::QUEEN)
        return 9.0;
    return 0;
}

Type strToType(const string& piece_str) 
{
    if(piece_str=="b" || piece_str=="B")
        return Type::BISHOP;
    else if(piece_str=="p" || piece_str=="P")
        return Type::PAWN;
    else if(piece_str=="r" || piece_str=="R")
        return Type::ROOK;
    else if(piece_str=="n" || piece_str=="N")
        return Type::KNIGHT;
    else if(piece_str=="k" || piece_str=="K")
        return Type::KING;
    else if(piece_str=="q" || piece_str=="Q")
        return Type::QUEEN;
    return Type::PAWN;
}
Color strToColor(const string& piece_str) 
{
    if(piece_str > "Z")
        return Color::BLACK;
    return Color::WHITE;
}

bool validateInput(const string& input)
{
    const char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int is_letters_valid = 0;
    if(input == "q" || input == "suggest")
        return true;
    if(input.length() != 4)
        return false;
    if(input[1] > '8' || input[3] < '1')
        return false;
    for(int i = 0 ; i < 8 ; i++)
    {
        if(input[0] == letters[i])
            is_letters_valid++;
        if(input[2] == letters[i])
            is_letters_valid++;
    }
    if(is_letters_valid != 2)   
        return false;
    return true;
}

string numeric(const string& play_string)
{
    string tmp = play_string;
    if     (play_string[0]=='a') tmp[0]='0';
    else if(play_string[0]=='b') tmp[0]='1';
    else if(play_string[0]=='c') tmp[0]='2';
    else if(play_string[0]=='d') tmp[0]='3';
    else if(play_string[0]=='e') tmp[0]='4';
    else if(play_string[0]=='f') tmp[0]='5';
    else if(play_string[0]=='g') tmp[0]='6';
    else if(play_string[0]=='h') tmp[0]='7';

    if     (play_string[2]=='a') tmp[2]='0';
    else if(play_string[2]=='b') tmp[2]='1';
    else if(play_string[2]=='c') tmp[2]='2';
    else if(play_string[2]=='d') tmp[2]='3';
    else if(play_string[2]=='e') tmp[2]='4';
    else if(play_string[2]=='f') tmp[2]='5';
    else if(play_string[2]=='g') tmp[2]='6';
    else if(play_string[2]=='h') tmp[2]='7';
    return tmp;
}

Move strToMove(const string& play_string)
{ 
    string move_str = numeric(play_string);
    return Move(int(move_str[0] - '0'),
                BOARD_SIZE -  int(move_str[1] - '0'),
                int(move_str[2] - '0'),
                BOARD_SIZE -  int(move_str[3] - '0')
                );
}

Color operator ! (const Color C)
{
    return (C==Color::BLACK) ? Color::WHITE : Color::BLACK;
}
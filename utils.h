#ifndef UTILS_H
#define UTILS_H

#include "Piece.h"
#include "Move.h"
#include <vector>

using namespace std;


// Overload of stream insertion
ostream& operator << (ostream& out, const Piece& obj);
ostream& operator << (ostream& out, const Color t);
ostream& operator << (ostream& out, std::vector<Move>& M);
ostream& operator << (ostream& out, const Move& M);

Type strToType(const string& piece_str);
Color strToColor(const string& piece_str);

Color operator ! (const Color C);
bool operator == (const Move& M1, const Move& M2);

double valueOfType(Type _type);
bool validateInput(const string& play_string);
string numeric(const string& play_string);
Move strToMove(const string& play_string);


#endif
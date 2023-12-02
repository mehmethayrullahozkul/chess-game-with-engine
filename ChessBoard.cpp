#include "ChessBoard.h"
#include "utils.h"

/*
 * Chessboard::Chessboard
 * -params:none
 * 
 * constructor:
 * 
 *  create a vector of vector<Piece*> which holds Piece pointers
 *  and initialize them with nullptr 
 *
*/
ChessBoard::ChessBoard()
{
    gameboard = vector<vector<Piece*>>(BOARD_SIZE, vector<Piece*> (BOARD_SIZE, nullptr));
}





ChessBoard::ChessBoard(ChessBoard& chessboard)
{
    gameboard = vector<vector<Piece*>>(BOARD_SIZE, vector<Piece*> (BOARD_SIZE, nullptr));
    for(int a = 0; a < BOARD_SIZE ; a++)
    {
        for(int b = 0 ; b < BOARD_SIZE ; b++)
        {
            if(chessboard.getAt(a, b) == nullptr)
                continue;
            Piece *piece = new Piece(a, b, this, 
                                     chessboard.getAt(a, b)->getType(), 
                                     chessboard.getAt(a, b)->getColor(),  
                                     chessboard.getAt(a, b)->hasMoved(),
                                     chessboard.getAt(a, b)->getValue());
        }
    }
}


/*
 * Chessboard::Initialize
 * -params:none
 * -return:none
 *
 * function:
 *      initialize the current gameboard with standart chess pieces with standart locations
 * 
*/
void ChessBoard::Initialize()
{
    Clear();
    Color PieceColor;
    for(int row = 0 ; row < BOARD_SIZE ; row++)
    {
        PieceColor = (row<=3) ? Color::BLACK : Color::WHITE;
        for(int column = 0 ; column < BOARD_SIZE ; column++)
        {
            if(row==0 || row==BOARD_SIZE-1)
            {
                    if(column==0)
                        Piece *piece = new Piece(column, row, this, Type::ROOK, PieceColor, false, 5.0);
                    else if (column==1)
                        Piece *piece = new Piece(column, row, this, Type::KNIGHT, PieceColor, false, 3.0);
                    else if(column==2)
                        Piece *piece = new Piece(column, row, this, Type::BISHOP, PieceColor, false,  3.0);
                    else if(column==3)
                        Piece *piece = new Piece(column, row, this, Type::QUEEN, PieceColor, false,  9.0);
                    else if(column==4)
                        Piece *piece = new Piece(column, row, this, Type::KING, PieceColor, false,  20.0);
                    else if(column==5)
                        Piece *piece = new Piece(column, row, this, Type::BISHOP, PieceColor, false,  3.0);
                    else if(column==6)
                        Piece *piece = new Piece(column, row, this, Type::KNIGHT, PieceColor, false,  3.0);
                    else if(column==7)
                        Piece *piece = new Piece(column, row, this, Type::ROOK, PieceColor, false,  5.0);
            }
            else if(row==1 || row==BOARD_SIZE-2)
            {
                Piece *piece = new Piece(column, row, this, Type::PAWN, PieceColor, false,  1);
            }
        }
    }
}

double ChessBoard::EvaluateBoard()
{
    Piece* piece;
    Color piece_color;
    double overall = 0;
    for(int row = 0 ; row < BOARD_SIZE ; row++)
    {
        for(int column = 0 ; column < BOARD_SIZE ; column++)
        {
            piece = getAt(row, column);
            if(piece != nullptr)
            {
                piece_color = piece->getColor();
                if(piece_color==Color::BLACK)
                {
                    overall = overall - piece->getValue();
                    if(IsUnderThreat(*(piece)))
                        overall = overall + piece->getValue() / 2.0;
                }
                else if(piece_color==Color::WHITE)
                {
                    overall = overall + piece->getValue();
                    if(IsUnderThreat(*(piece)))
                        overall = overall - piece->getValue() / 2.0;
                }
            }

        }
    }
    return overall;
}


/*
 * ChessBoard::getKing
 * -params: color of the desired king
 * -return: reference to the king piece
 * 
 * function:
 *  iterate through the gameboard:
 *      if pointer is not null and color matches and type is king
 *          return reference to that piece
*/
Piece& ChessBoard::getKing(Color color) const
{
    Piece *piece;
    for(int row = 0 ; row < BOARD_SIZE ; row++)
    {
        for(int column = 0 ; column < BOARD_SIZE ; column++)
        {
            piece = getAt(row, column);
            if(piece != nullptr && (piece->getColor() == color) && (piece->getType() == Type::KING))
                return *(piece);
        }
    }
    return *(piece);
}

/*
 * ChessBoard::IsUnderThreat
 * -params: reference to piece object
 * -return: whether the object can be attacked or not
 * 
 * function:
 *  iterate through the gameboard:
 *      if pointer is not null and piece is not the same color:
 *          call CanAttack function on iterating object to the parameter object's location
 *          if CanAttack:
 *              return true
 *  if could not find any piece that's able to attack object:
 *      return false
 *
*/
bool ChessBoard::IsUnderThreat(const Piece& obj)
{
    Piece* piece;
    for(int row = 0 ; row < BOARD_SIZE ; row++)
    {
        for(int column = 0 ; column < BOARD_SIZE ; column++)
        {
            piece = getAt(row, column);
            if(piece != nullptr && piece->getColor() != obj.getColor())
            {
                if(CanAttack(*(piece), obj.getX(), obj.getY()))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::IsUnderThreatByColor(const Color& color, int x, int y)
{
    Piece* piece;
    for(int row = 0 ; row < BOARD_SIZE ; row++)
    {
        for(int column = 0 ; column < BOARD_SIZE ; column++)
        {
            piece = getAt(row, column);
            if(piece != nullptr && piece->getColor() == color)
            {
                if(CanAttack(*(piece), x, y))
                {
                    return true;
                }
            }
        }
    }
    return false;
}


bool ChessBoard::isMate(Color king_color)
{
    if(!isCheck(king_color))
        return false;
    
    ChessBoard chessgame(*(this));

    vector<Piece*> pieces = GetPieces(king_color);

    for(auto piece : pieces)
    {
        vector<Move> vision = CalculateVision(*(piece));

        for(auto move : vision)
        {     
            DirectMove(chessgame, move);
            if(!chessgame.isCheck(king_color))
            {
                cout << "--king under threat but possible move: " << move.fromX() << move.fromY() << " to " << move.toX() << move.toY() << endl;
                return false;
            }
            DirectMove(chessgame, move.reverse());
        }
    }
    chessgame.Clear();
    cout << endl;
    return true;
}

/*
 * ChessBoard::isCheck
 * -params: color of the king
 * -return: whether king is under threat or not
 * 
 * function:
 *  use getKing function to get king reference,
 *  check if king can be attacked using IsUnderThreat
 *  if king can be attacked:
 *      return true
 *  if not:
 *      return false
 *
*/
bool ChessBoard::isCheck(Color king_color)
{
    if(IsUnderThreat(getKing(king_color)))
        return true;
    return false;
}


Piece* ChessBoard::getAt(const int x, const int y) const
{
    return this->gameboard[y][x];
}


void ChessBoard::setAt(const int x, const int y, Piece* obj)
{
    this->gameboard[y][x] = obj;
}

bool ChessBoard::MovePiece(const Move& move)
{
    Piece* piece = getAt(move.fromX(), move.fromY());
    if(piece == nullptr)
        return false;
    
    if(piece->isKing() && !CanMoveKing(move))
        return false;
    else if(!CanMove(move))
        return false;
    if(piece != nullptr)
        delete getAt(move.toX(), move.toY());
    
    
    if(piece->getType() == Type::PAWN)
        piece->setMoved(true);
    piece->setX(move.toX());
    piece->setY(move.toY());
    setAt(move.toX(), move.toY(), piece);
    setAt(move.fromX(), move.fromY(), nullptr);
    return true;
}

bool ChessBoard::isLegal(const Move& move)
{
    Piece* piece = getAt(move.fromX(), move.fromY());
    if(piece == nullptr)
        return false;
    if(piece->isKing() && !CanMoveKing(move))
        return false;
    else if(!CanMove(move))
        return false;
    // move legal so far
    // check if player's king is in check after move

    ChessBoard chessboard(*(this));

    DirectMove(chessboard, move);

    Color move_color = this->getAt(move.fromX(), move.fromY())->getColor();

    if(chessboard.isCheck(move_color))
    {   
        cout << "check after move - not legal" << endl;
        return false;
    }
    
    return true;
}


void ChessBoard::DirectMove(ChessBoard& chessboard, const Move& move)
{
    Piece* piece = chessboard.getAt(move.fromX(), move.fromY());

    if(piece != nullptr)
        delete chessboard.getAt(move.toX(), move.toY());
    
    
    if(piece->getType() == Type::PAWN)
        piece->setMoved(true);
    
    piece->setX(move.toX());
    piece->setY(move.toY());
    chessboard.setAt(move.toX(), move.toY(), piece);
    chessboard.setAt(move.fromX(), move.fromY(), nullptr);
}

bool ChessBoard::MovePiece(const string& move_str)
{
    if(!validateInput(move_str))
        return false;
    Move move = strToMove(move_str);
    return MovePiece(move);
}
bool ChessBoard::CanAttack(const Move& move)
{
    bool in_vision = false;
    vector<Move> vision = CalculateVision(*(getAt(move.fromX(), move.fromY())));

    for(int i = 0 ; i < vision.size() ; i++)
    {
        if(vision[i].toX() == move.toX() && vision[i].toY() == move.toY())
            in_vision = true;
    }

    if(!in_vision)
        return false;
    
    return true;
}

bool ChessBoard::CanAttack(const Piece& obj, int attackX, int attackY)
{
    bool in_vision = false;
    vector<Move> vision = CalculateVision(obj);

    for(int i = 0 ; i < vision.size() ; i++)
    {
        if(vision[i].toX() == attackX && vision[i].toY() == attackY)
            in_vision = true;
    }

    if(!in_vision)
        return false;
    
    return true;
}


bool ChessBoard::CanMove(const Move& move)
{
    bool in_vision = false;
    vector<Move> vision = CalculateVision(*(getAt(move.fromX(), move.fromY())));
    for(int i = 0 ; i < vision.size() ; i++)
    {
        if(vision[i].toX() == move.toX() && vision[i].toY() == move.toY())
            in_vision = true;
    }

    if(!in_vision)
        return false;

    if(getAt(move.toX(), move.toY()) != nullptr && getAt(move.toX(), move.toY())->getType() == Type::KING)
        return false;
    
    return true;
}


bool ChessBoard::CanMoveKing(const Move& move)
{
    bool in_vision = false;
    vector<Move> vision = CalculateVision(*(getAt(move.fromX(), move.fromY())));

    for(int i = 0 ; i < vision.size() ; i++)
    {
        if(vision[i].toX() == move.toX() && vision[i].toY() == move.toY())
            in_vision = true;
    }

    if(!in_vision)
        return false;

    Color opponent_color = !(getAt(move.fromX(), move.fromY())->getColor());

    if(IsUnderThreatByColor(opponent_color, move.toX(), move.toY()))
        return false;
    
    return true;
}


/*
 *  ChessBoard::CalculateVision     
 *  - params: reference of a single piece obj
 *  - return: vector of possible moves
 * 
 * function:
 *  according the type of object:
 *      call necessary helper move function which returns the move vectors
 *  return the move vector  
 * 
*/
vector<Move> ChessBoard::CalculateVision(const Piece& obj)
{
    if(obj.getType() == Type::ROOK)
        return calcStraight(obj);

    else if(obj.getType() == Type::KNIGHT)
        return calcLShape(obj);

    else if(obj.getType() == Type::BISHOP)
        return calcDiagonal(obj);
//
    else if(obj.getType() == Type::QUEEN)
    {
        vector<Move> _straight, _diagonal;
        _straight = calcStraight(obj);
        _diagonal = calcDiagonal(obj);
        vector<Move> total;
        total.reserve(_straight.size() + _diagonal.size());
        total.insert( total.end(), _straight.begin(), _straight.end() );
        total.insert( total.end(), _diagonal.begin(), _diagonal.end() );
        return total;
    }
    else if(obj.getType()==Type::KING)
        return calcKing(obj);

    else if(obj.getType()==Type::PAWN)
        return calcPawn(obj);

    return vector<Move>();
}

/*
 * ChessBoard::calcStraight
 * ChessBoard::calcDiagonal
 * ChessBoard::calcLShape
 * ChessBoard::calcPawn
 * ChessBoard::calcKing
 * 
 * -params: reference of piece a object
 * -return: vector of moves
 * 
 * function:
 *  get starting point x and y from object
 *  create an empty vector of moves
 *  check if legal moves can be made by with conditions:
 *      both x and y are in legal boundries,
 *      there is no active piece in that location
 *      or there is a enemy color piece in that location
 *      if conditions met:
 *          push them to move vector
 * return the move vector with possible moves
 * 
 * 
*/

/****************************************************************************************************************/

vector<Move> ChessBoard::calcStraight(const Piece& obj)
{
    int startX = obj.getX();
    int startY = obj.getY();

    vector<Move> arr;

    int i = 1;
    // LEFT
    while(inBorder(startX - i))
    {
        if(getAt(startX - i, startY) == nullptr)
            arr.push_back(Move(startX, startY, startX - i , startY));
        
        else if(getAt(startX - i, startY)->getColor() != obj.getColor())
        {
            arr.push_back(Move(startX, startY, startX - i , startY));
            break;
        }
        else
            break;
        i++;
    }
    i = 1;
    // RIGHT
    while(inBorder(startX + i))
    {
        if(getAt(startX + i, startY) == nullptr)
            arr.push_back(Move(startX, startY, startX + i, startY));
        
        else if(getAt(startX + i, startY)->getColor() != obj.getColor())
        {
            arr.push_back(Move(startX, startY, startX + i, startY));
            break;
        }
        else
            break;
        i++;
    }
    i = 1;
    // UP
    while(inBorder(startY - i))
    {
        if(getAt(startX, startY - i) == nullptr)
            arr.push_back(Move(startX, startY, startX, startY - i));

        else if(getAt(startX, startY - i)->getColor() != obj.getColor())
        {
            arr.push_back(Move(startX, startY, startX, startY - i));
            break;
        }
        else
            break;
        i++;
    }
    i = 1;
    // DOWN
        while(inBorder(startY + i))
    {
        if(getAt(startX, startY + i) == nullptr)
            arr.push_back(Move(startX, startY, startX, startY + i));
        
        else if(getAt(startX, startY + i)->getColor() != obj.getColor())
        {
            arr.push_back(Move(startX, startY, startX, startY + i));
            break;
        }
        else
            break;
        i++;
    }
    return arr;
}


vector<Move> ChessBoard::calcDiagonal(const Piece& obj)
{
    int startX = obj.getX();
    int startY = obj.getY();
    
    vector<Move> arr;

    int i = 1;
    // UP-LEFT
    while(inBorder(startX - i, startY - i))
    {
        if(getAt(startX - i, startY - i) == nullptr)
            arr.push_back(Move(startX, startY, startX - i , startY - i));
        
        else if(getAt(startX - i, startY - i)->getColor() != obj.getColor())
        {
            arr.push_back(Move(startX, startY, startX - i , startY - i));
            break;
        }
        else
            break;
        i++;
    }
    i = 1;
    // UP-RIGHT
    while(inBorder(startX + i, startY - i))
    {
        if(getAt(startX + i, startY - i) == nullptr)
            arr.push_back(Move(startX, startY, startX + i, startY - i));
        
        else if(getAt(startX + i, startY - i)->getColor() != obj.getColor())
        {
            arr.push_back(Move(startX, startY, startX + i, startY - i));
            break;
        }
        else
            break;
        i++;
    }
    i = 1;
    // DOWN-LEFT
    while(inBorder(startX - i, startY + i))
    {
        if(getAt(startX - i, startY + i) == nullptr)
            arr.push_back(Move(startX, startY, startX - i, startY + i));
        
        else if(getAt(startX - i, startY + i)->getColor() != obj.getColor())
        {
            arr.push_back(Move(startX, startY, startX - i, startY + i));
            break;
        }
        else
            break;
        i++;
    }
    i = 1;
    // DOWN-RIGHT
        while(inBorder(startX + i, startY + i))
    {
        if(getAt(startX + i, startY + i) == nullptr)
            arr.push_back(Move(startX, startY, startX + i, startY + i));
        
        else if(getAt(startX + i, startY + i)->getColor() != obj.getColor())
        {
            arr.push_back(Move(startX, startY, startX + i, startY + i));
            break;
        }
        else
            break;
        i++;
    }
    return arr;
}


vector<Move> ChessBoard::calcPawn(const Piece& obj)
{   
    int startX = obj.getX();
    int startY = obj.getY();

    vector<Move> arr;

    if(obj.getColor()==Color::WHITE)
    {
        // Forward One
        if(inBorder(startY - 1) && getAt(startX, startY - 1) == nullptr)
            arr.push_back(Move(startX, startY, startX, startY - 1));
        // UPLEFT
        if(inBorder(startX - 1, startY - 1) && getAt(startX - 1, startY - 1) != nullptr && getAt(startX - 1, startY - 1)->getColor() != obj.getColor())
            arr.push_back(Move(startX, startY, startX - 1, startY - 1));
        // UPRIGHT
        if(inBorder(startX + 1, startY - 1) && getAt(startX + 1, startY - 1) != nullptr && getAt(startX + 1, startY - 1)->getColor() != obj.getColor())
            arr.push_back(Move(startX, startY, startX + 1, startY - 1));
        // Forward Two
        if(!obj.hasMoved() && getAt(startX, startY - 2) == nullptr)
            arr.push_back(Move(startX, startY, startX, startY - 2));
    }
    else if(obj.getColor()==Color::BLACK)
    {
        // Down One
        if(inBorder(startY + 1) && getAt(startX, startY + 1) == nullptr)
            arr.push_back(Move(startX, startY, startX, startY + 1));
        // DOWNLEFT
        if(inBorder(startX - 1, startY + 1) && getAt(startX - 1, startY + 1) != nullptr && getAt(startX - 1, startY + 1)->getColor() != obj.getColor())
            arr.push_back(Move(startX, startY, startX - 1, startY + 1));
        // DOWNRIGHT
        if(inBorder(startX + 1, startY + 1) && getAt(startX + 1, startY + 1) != nullptr && getAt(startX + 1, startY + 1)->getColor() != obj.getColor())
            arr.push_back(Move(startX, startY, startX + 1, startY + 1));
        // Down Two
        if(!obj.hasMoved() && getAt(startX, startY + 2) == nullptr)
            arr.push_back(Move(startX, startY, startX, startY + 2));
    }

    return arr;
}


vector<Move> ChessBoard::calcKing(const Piece& obj)
{   
    int startX = obj.getX();
    int startY = obj.getY();

    vector<Move> arr;

    for(int a = -1 ; a <= 1 ; a++)
    {
        for(int b = -1 ; b <= 1 ; b++)
        {
            if(inBorder(startX + a, startY + b))
            {
                if(getAt(startX + a, startY + b) == nullptr)
                    arr.push_back(Move(startX, startY, startX + a, startY + b));
                else if(getAt(startX + a, startY + b) != nullptr && getAt(startX + a, startY + b)->getColor() != obj.getColor())
                    arr.push_back(Move(startX, startY, startX + a, startY + b));
            }
        }
    }
    return arr;
}



vector<Move> ChessBoard::calcLShape(const Piece& obj)
{
    int startX = obj.getX();
    int startY = obj.getY();

    vector<Move> arr;

    // UP2LEFT1
    if(inBorder(startX - 1, startY - 2) && (getAt(startX - 1, startY - 2) == nullptr || getAt(startX - 1, startY - 2)->getColor() != obj.getColor()))
        arr.push_back(Move(startX, startY, startX - 1 , startY - 2));
    // UP1LEFT2
    if(inBorder(startX - 2, startY - 1) && (getAt(startX - 2, startY - 1) == nullptr || getAt(startX - 2, startY - 1)->getColor() != obj.getColor()))
        arr.push_back(Move(startX, startY, startX - 2 , startY - 1));
    // UP2RIGHT1
    if(inBorder(startX + 1, startY - 2) && (getAt(startX + 1, startY - 2) == nullptr || getAt(startX + 1, startY - 2)->getColor() != obj.getColor()))
        arr.push_back(Move(startX, startY, startX + 1 , startY - 2));
    // UP1RIGHT2
    if(inBorder(startX + 2, startY - 1) && ( getAt(startX + 2, startY - 1) == nullptr || getAt(startX + 2, startY - 1)->getColor() != obj.getColor()))
        arr.push_back(Move(startX, startY, startX + 2 , startY - 1));
    // DOWN2LEFT1
    if(inBorder(startX - 1, startY + 2) && (getAt(startX - 1, startY + 2) == nullptr || getAt(startX - 1, startY + 2)->getColor() != obj.getColor()))
        arr.push_back(Move(startX, startY, startX - 1 , startY + 2));
    // DOWN1LEFT2
    if(inBorder(startX - 2, startY + 1) && (getAt(startX - 2, startY + 1) == nullptr || getAt(startX - 2, startY + 1)->getColor() != obj.getColor()))
        arr.push_back(Move(startX, startY, startX - 2 , startY + 1));
    // DOWN2RIGHT1
    if(inBorder(startX + 1, startY + 2) && (getAt(startX + 1, startY + 2) == nullptr || getAt(startX + 1, startY + 2)->getColor() != obj.getColor()))
        arr.push_back(Move(startX, startY, startX + 1 , startY + 2));
    // DOWN1RIGHT2
    if(inBorder(startX + 2, startY + 1) && (getAt(startX + 2, startY + 1) == nullptr || getAt(startX + 2, startY + 1)->getColor() != obj.getColor()))
        arr.push_back(Move(startX, startY, startX + 2 , startY + 1));

    return arr;
}

/****************************************************************************************************************/


bool ChessBoard::inBorder(int x, int y)
{
    if(x < 0 || x > 7 || y < 0 || y > 7)
        return false;
    return true;
}

void ChessBoard::Display()
{
    for(int row = 0 ; row < BOARD_SIZE + 2 ; row++)
    {
        for(int column = 0 ; column < BOARD_SIZE + 2 ; column++)
        {
            if(column==0)
            {   
                if(BOARD_SIZE - row > 0)
                    cout << BOARD_SIZE - row << " ";
                else
                    cout << "  ";
            }
            else if(column==1)
            {
                if(row<BOARD_SIZE)
                    cout << "| ";
                else
                    cout << "  ";
            }
            else if(row==BOARD_SIZE)
                cout << "--";        
            else if(row==BOARD_SIZE+1)
            {
                if(column==2)
                    cout << "a ";
                else if(column==3)
                    cout << "b ";
                else if(column==4)
                    cout << "c ";
                else if(column==5)
                    cout << "d ";
                else if(column==6)
                    cout << "e ";
                else if(column==7)
                    cout << "f ";
                else if(column==8)
                    cout << "g ";
                else if(column==9)
                    cout << "h ";
            }
            else 
            {
                if(gameboard[row][column-2] == nullptr)
                    cout << ". ";
                else
                    cout << *(gameboard[row][column-2]);
            }
            
        }
        cout << endl;
    }
}


void ChessBoard::Clear()
{
    for(int row = 0 ; row < BOARD_SIZE ; row++)
    {
        for(int column = 0 ; column < BOARD_SIZE ; column++)
        {
            if(gameboard[row][column] != nullptr) 
            {
                delete gameboard[row][column];
                gameboard[row][column] = nullptr;
            }
        }
    }
}

ChessBoard::~ChessBoard()
{
    for(int row = 0 ; row < BOARD_SIZE ; row++)
    {
        for(int column = 0 ; column < BOARD_SIZE ; column++)
        {
            if(gameboard[row][column] != nullptr) delete gameboard[row][column];
        }
    }
    gameboard.clear();
    gameboard.shrink_to_fit();
}


vector<Piece*> ChessBoard::GetPieces(const Color& piece_color) const
{
    vector<Piece*> pieces;
    pieces.reserve(BOARD_SIZE * 2);
    for(int row = 0 ; row < BOARD_SIZE ; row++)
    {
        for(int column = 0 ; column < BOARD_SIZE ; column++)
        {
            if(getAt(row, column) != nullptr && getAt(row, column)->getColor() == piece_color)
                pieces.push_back(getAt(row, column));
        }
    }
    return pieces;
}

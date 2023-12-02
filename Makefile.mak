all: all.o
	g++ -std=c++11 all.o -o chessgame

all.o: g++ -std=c++11 -c Piece.cpp ChessBoard.cpp Move.cpp Gameplay.cpp utils.cpp  main.cpp
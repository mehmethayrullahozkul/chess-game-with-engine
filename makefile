CXX = g++
CXXFLAGS = -std=c++11

chessgame: Piece.o ChessBoard.o Move.o Gameplay.o utils.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

Piece.o: Piece.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ChessBoard.o: ChessBoard.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Move.o: Move.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

utils.o: utils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Gameplay.o: Gameplay.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o chessgame

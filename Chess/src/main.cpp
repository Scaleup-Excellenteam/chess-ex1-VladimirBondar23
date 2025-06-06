// Chess 
// Chess 
#include "Chess.h"
#include "Board.h"
#include "Game.h"


int main()
{
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    COLOR turn = WHITE;
    int autoMode, depth;
    std::cout << "Enter search depth: ";
    std::cin >> depth;
    std::cout << "Auto-play mode? (0 = manual, 1 = auto): ";
    std::cin >> autoMode;

    if (autoMode == 1){
        std::cout << "Running 8-move auto-game..." << std::endl;
        for (int threads : {0, 2, 4, 8}) {
            computerGame(board, turn, depth, threads);
        }
    }
    else{
        int numThreads;
        std::cout << "Running manual game..." << std::endl;
        std::cout << "Enter number of threads: ";
        std::cin >> numThreads;
        userGame(board, turn, depth, numThreads);
    }
	return 0;

}
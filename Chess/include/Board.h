#pragma once

#include <vector>
#include "Cell.h"
#include "Piece.h"  // Assuming Piece is the base class for all pieces like Pawn, Rook, etc.

class Board {
public:
    // Constructor and Destructor
    Board();
    ~Board();

    // Function to initialize the chessboard
    void initializeCells();
    bool updateBoard(int start_col, char start_row, int end_col, char end_row, char side);
    // Function to validate a move
    int isMoveValid(Cell start, Cell end, char actionSide);

    // Piece-specific move validation functions
    bool isPawnMoveValid(Cell start, Cell end);
    bool isKingInCheck(char side);
    bool isRookMoveValid(Cell start, Cell end);
    bool isKnightMoveValid(Cell start, Cell end);
    bool isBishopMoveValid(Cell start, Cell end);
    bool isQueenMoveValid(Cell start, Cell end);
    bool isKingMoveValid(Cell start, Cell end);

    // Check if there is a path blockage (for rooks, bishops, queens)
    bool isPathBlocked(Cell start, Cell end);

    // Helper method to create a piece (for initialization purposes)
    Piece* createPiece(char letter, int number, char side);

    // Function to get a cell by its coordinates
    Cell getCell(char letter, int number) const;

private:
    // Board cells, a 2D array or vector, depending on your implementation
    std::vector<Cell> cells;
};


#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Rook.h"
#include "Queen.h"
#include <iostream>
Board::Board() {
    initializeCells();
}

// Destructor
Board::~Board() {
    for (Cell& cell : cells) {
        delete cell.piece;  // Clean up dynamically allocated pieces
    }
}

// Initializes the board by placing the pieces in their initial positions
void Board::initializeCells() {
    char side;

    for (char letter = 'a'; letter <= 'h'; letter++) {
        if (letter == 'a' || letter == 'b') side = 'w';  // White side for columns 'a' and 'b'
        else if (letter == 'g' || letter == 'h') side = 'b';  // Black side for columns 'g' and 'h'

        for (int number = 1; number <= 8; number++) {
            Piece* p = createPiece(letter, number, side);
            cells.push_back(Cell(letter, number, p));

            // Optional: Print for debugging
            if (p != nullptr) {
                std::cout << cells.back().letter << cells.back().number
                    << p->side << p->identifier << '\n';
            }
        }
    }
}

bool Board::updateBoard(int num1, char let1, int num2, char let2, char side)
{
    // Find the start and end cell in the board
    Cell* startCell = nullptr;
    Cell* endCell = nullptr;

    for (Cell& cell : cells) {
        if (cell.letter == let1 && cell.number == num1) {
            startCell = &cell;
        }
        if (cell.letter == let2 && cell.number == num2) {
            endCell = &cell;
        }
    }
    auto startCellPiece =  startCell->piece;
    auto endCellPiece =  endCell->piece;
    endCell->piece = startCell->piece;  // Move the piece to the end cell
    startCell->piece = nullptr;         // Remove the piece from the start cell
    if (isKingInCheck(side)) {
        endCell->piece = endCellPiece;
        startCell->piece = startCellPiece;
        return false;
    }
    return true;

}



// Helper function to create a piece based on the position
Piece* Board::createPiece(char letter, int number, char side) {
    Piece* p = nullptr;

    
        switch (letter) {
        case 'a': case 'h':
            if (number == 1 || number == 8)
                p = new Rook(side);
            else if (number == 2 || number == 7)
                p = new Knight(side);
            else if (number == 3 || number == 6)
                p = new Bishop(side);
            else if (number == 4)
                p = new Queen(side);
            else if (number == 5)
                p = new King(side);
            break;
        case 'b': case 'g':
            p = new Pawn(side);  // Pawns for columns 'b' and 'g'
            break;
        default:
            p = nullptr;  // Empty cells
            break;
        }
    
    return p;
}




// Validate if a move is valid for a given piece
int Board::isMoveValid(Cell start, Cell end, char actionSide) {
    if (start.piece == nullptr) 
        return 11;  
    if (start.piece->side != actionSide)
        return 12;
    if (end.piece != nullptr) {
        if (start.piece->side == end.piece->side)
            return 13;
    }

    Piece* piece = start.piece;

    switch (piece->identifier) {
    case 'p': // Pawn movement
        return isPawnMoveValid(start, end)? 42 : 21;
    case 'r': // Rook movement
        return isRookMoveValid(start, end)? 42 : 21;
    case 'n': // Knight movement
        return isKnightMoveValid(start, end)? 42 : 21;
    case 'b': // Bishop movement
        return isBishopMoveValid(start, end)? 42 : 21;
    case 'q': // Queen movement
        return isQueenMoveValid(start, end)? 42 : 21;
    case 'k': // King movement
        return isKingMoveValid(start, end)? 42 : 21;
    default:
        return 21;
    }
}

// Validate pawn movement
bool Board::isPawnMoveValid(Cell start, Cell end) {
    int direction = (start.piece->side == 'w') ? 1 : -1;  // White moves up, black moves down
    if (start.number == end.number && end.letter == start.letter + direction) {
        return end.piece == nullptr;  // Pawns move one step forward if the square is empty
    }
    if (start.number == end.number && end.letter == start.letter + 2 * direction && (start.letter == 'g' || start.letter == 'b')) {
        return end.piece == nullptr;  // First move of the pawn can move two squares forward if no obstruction
    }
    if (abs(start.number - end.number) == 1 && end.letter == start.letter + direction) {
        return end.piece != nullptr && end.piece->side != start.piece->side;  // Pawn captures diagonally
    }
    return false;
}

bool Board::isKingInCheck(char side) {
    Cell kingCell;

    // 1. Locate the King
    for (const Cell& cell : cells) {
        if (cell.piece != nullptr && cell.piece->identifier == 'k' && cell.piece->side == side) {
            kingCell = cell;
            break;
        }
    }

    // 2. Check if any enemy piece can move to the King’s position
    for (const Cell& cell : cells) {
        if (cell.piece != nullptr && cell.piece->side != side) {
            int result = isMoveValid(cell, kingCell, cell.piece->side);
            if (result == 42) { // 42 means valid move (legal)
                return true; // King is in check
            }
        }
    }

    return false; // King is safe
}




// Validate rook movement
bool Board::isRookMoveValid(Cell start, Cell end) {
    if (start.letter != end.letter && start.number != end.number) {
        return false;  // Rook must move in a straight line
    }
    return !isPathBlocked(start, end);  // Check if the path is blocked by another piece
}

// Validate knight movement
bool Board::isKnightMoveValid(Cell start, Cell end) {
    int dx = abs(start.number - end.number);
    int dy = abs(start.letter - end.letter);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);  // Knight moves in an L shape
}

// Validate bishop movement
bool Board::isBishopMoveValid(Cell start, Cell end) {
    if (abs(start.letter - end.letter) != abs(start.number - end.number)) {
        return false;  // Bishop must move diagonally
    }
    return !isPathBlocked(start, end);  // Check if the path is blocked by another piece
}

// Validate queen movement (combination of rook and bishop)
bool Board::isQueenMoveValid(Cell start, Cell end) {
    return isRookMoveValid(start, end) || isBishopMoveValid(start, end);  // Queen combines rook and bishop moves
}

// Validate king movement
bool Board::isKingMoveValid(Cell start, Cell end) {
    int dx = abs(start.number - end.number);
    int dy = abs(start.letter - end.letter);
    return dx <= 1 && dy <= 1;  // King can move one square in any direction
}

// Check if the path is blocked (needed for rooks, bishops, queens)
bool Board::isPathBlocked(Cell start, Cell end) {
    int dx = end.letter - start.letter;
    int dy = end.number - start.number;

    int xDir = (dx == 0) ? 0 : (dx > 0) ? 1 : -1;
    int yDir = (dy == 0) ? 0 : (dy > 0) ? 1 : -1;

    int x = start.letter + xDir;
    int y = start.number + yDir;

    while (x != end.letter || y != end.number) {
        if (getCell(x, y).piece != nullptr) {
            return true;  // There's a piece blocking the path
        }
        x += xDir;
        y += yDir;
    }
    return false;
}

// Get a cell by its coordinates
Cell Board::getCell(char letter, int number) const {
    for (const Cell& cell : cells) {
        if (cell.letter == letter && cell.number == number) {
            return cell;
        }
    }
    return Cell(0,0,nullptr);  // Return an empty cell if not found (shouldn't happen if the board is valid)
}





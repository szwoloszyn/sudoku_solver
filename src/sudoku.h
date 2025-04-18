#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

#include "field.h"

constexpr std::size_t BOARD_SIZE =  9;

#ifdef UNIT_TEST
    #define TESTABLE public
#else
    #define TESTABLE protected
#endif

bool operator==(const std::vector<Field>& fields, const std::vector<int>& integers);


class Sudoku
{
public:
    Sudoku();
    Sudoku(const std::vector<std::vector<int>>& numBoard);
    void printBoard() const;
    std::vector<Field> getOptions(int row, int col);
TESTABLE:
    Field getField(int row, int col) {
        return this->sudokuBoard.at(row).at(col);
    }
    int getRowNr(int row, int col);
    int getColumnNr(int row, int col);
    int getSquareNr(int row, int col);

    std::vector<Field> getRow(int nr);
    std::vector<Field> getColumn(int nr);
    std::vector<Field> getSquare(int nr);


private:
    std::vector<std::vector<Field>> sudokuBoard;

};

#endif // SUDOKU_H

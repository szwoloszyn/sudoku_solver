#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <map>
#include "field.h"

constexpr std::size_t BOARD_SIZE =  9;

#ifdef UNIT_TEST
    #define TESTABLE public
#else
    #define TESTABLE protected
#endif

bool operator==(const std::vector<Field>& fields, const std::vector<int>& integers);
bool operator==(const std::set<Field>& fields, const std::set<int>& integers);

class Sudoku
{
public:
    Sudoku();
    Sudoku(const std::vector<std::vector<int>>& numBoard);
    void printBoard() const;
    std::set<Field> getOptions(int row, int col) const;
    std::vector<std::set<Field>> getOptionsPerRow(int rowNr) const;
    std::vector<std::set<Field>> getOptionsPerColumn(int colNr) const;
    std::vector<std::set<Field>> getOptionsPerSquare(int squareNr) const;
    bool fillCertainFields();
    bool iterateThroughStructures(); // structures = {rows, columns, squares} method is supposed to fill
    // unconvenient fields where you have more than one option but can exclude rest by set_difference
    static std::map<int, Field> getUniqueValues(const std::vector<std::pair<std::set<Field>, int>>& multiOptions);
    bool solveSudoku();

TESTABLE:
    Field getField(int row, int col) const{
        return this->sudokuBoard.at(row).at(col);
    }
    auto getBoard() const{
        return this->sudokuBoard;
    }
    int getRowNr(int row, int col) const;
    int getColumnNr(int row, int col) const;
    int getSquareNr(int row, int col) const;

    std::vector<Field> getRow(int nr) const;
    std::vector<Field> getColumn(int nr) const;
    std::vector<Field> getSquare(int nr) const;



private:
    std::vector<std::vector<Field>> sudokuBoard;

};

#endif // SUDOKU_H

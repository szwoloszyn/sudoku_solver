#include <iostream>
#include "sudoku.h"

using std::vector;
using std::set;

bool operator==(const std::vector<Field>& fields, const std::vector<int>& integers)
{
    if (fields.size() != integers.size()) {
        return false;
    }
    for (int i = 0; i < fields.size(); ++i) {
        if (fields.at(i) != integers.at(i)) {
            return false;
        }
    }
    return true;
}

bool operator==(const std::set<Field>& fields, const std::set<int>& integers)
{
    if (fields.size() != integers.size()) {
        return false;
    }
    auto itFields = fields.begin();
    auto itIntegers = integers.begin();
    while (itFields != fields.end() and itIntegers != integers.end()) {
        if (*itFields != *itIntegers) {
            return false;
        }
        itFields++;
        itIntegers++;
    }
    return true;
}

Sudoku::Sudoku()
{

}

Sudoku::Sudoku(const std::vector<std::vector<int>>& numBoard)
{
    if (numBoard.size() != 9 or numBoard[0].size() != 9) {
        throw std::out_of_range{"input board's invalid dimensions"};
    }
    this->sudokuBoard = vector<vector<Field>>(BOARD_SIZE, std::vector<Field>(BOARD_SIZE));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            this->sudokuBoard[i][j] = numBoard[i][j];
        }
    }
}

void Sudoku::printBoard() const
{
    for (auto row : this->sudokuBoard) {
        for (auto col : row) {
            if (col.isBlank()) {
                std::cout << "x ";
            }
            else {
                std::cout << col.getFieldValue() << " ";
            }
        }
        std::cout << "\n";
    }
}

int Sudoku::getRowNr(int row, int col) const
{
    return row;
}

int Sudoku::getColumnNr(int row, int col) const
{
    return col;
}

int Sudoku::getSquareNr(int row, int col) const
{
    return 3*(row/3) + (col/3);
}

std::vector<Field> Sudoku::getRow(int nr) const
{
    return this->sudokuBoard.at(nr);
}

std::vector<Field> Sudoku::getColumn(int nr) const
{
    vector<Field> column;
    for (auto row : this->sudokuBoard) {
        column.push_back(row[nr]);
    }
    return column;
}

std::vector<Field> Sudoku::getSquare(int nr) const
{
    vector<Field> square;
    int startCol = 3 * (nr%3);
    int startRow = 3 * (nr/3);
    int col = startCol;
    int row = startRow;
    for (int i = 0; i < 9; ++i) {
        square.push_back(getField(row, col));
        col++;
        if (i%3 == 2) {
            row++;
            col = startCol;
        }
    }
    return square;
}

std::set<Field> Sudoku::getOptions(int row, int col) const
{
    if (this->getField(row, col) != 0) {
        return set<Field>{};
    }
    auto rowFields = getRow( getRowNr(row, col) );
    auto colFields = getColumn( getColumnNr(row, col) );
    auto squareFields = getSquare( getSquareNr(row, col) );

    set<Field>allFields;
    allFields.insert(rowFields.begin(), rowFields.end());
    allFields.insert(colFields.begin(), colFields.end());
    allFields.insert(squareFields.begin(), squareFields.end());
    return getLackingValues(allFields);
}

bool Sudoku::fillCertainFields()
{
    bool sthFilled = false;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            auto possibilities = this->getOptions(row, col);
            if (possibilities.size() == 1) {
                sudokuBoard.at(row).at(col) = *(possibilities.begin());
                sthFilled = true;
            }
        }
    }
    std::cout << "galaz zbiorow!";
    return sthFilled;
}







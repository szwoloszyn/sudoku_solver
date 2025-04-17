#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

#include "field.h"
class Sudoku
{
public:
    Sudoku();
    //Sudoku(std::vect);

private:
    std::vector<std::vector<Field>> sudokuBoard;
};

#endif // SUDOKU_H

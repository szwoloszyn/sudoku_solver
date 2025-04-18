#include <gtest/gtest.h>
#include "../src/sudoku.h"

using std::vector;

class SudokuTest : public ::testing::Test
{
protected:
    Sudoku board;
    Sudoku complexBoard;
    void SetUp() override {
        vector<vector<int>> a(9,std::vector<int>{1,2,3,0,5,0,7,8,9});
        board = Sudoku(a);

        vector<vector<int>> b{
            {7,9, 5, 0, 1, 8, 0, 2, 0},
            {1, 6, 0, 4, 0, 2, 7, 0, 3},
            { 3, 4, 2, 9, 7, 6, 5, 1, 8},
            { 9, 0, 0, 6, 8, 0, 3, 0, 7},
            { 5, 7, 3, 2, 4, 9, 1, 8, 6},
            {8, 1, 6, 5, 3, 7, 9, 4, 2},
            {4, 8, 9, 7, 6, 5, 2, 3, 1},
            {6, 5, 1, 8, 2, 3, 4, 7, 9},
            {2, 3, 7, 1, 9, 4, 8, 6, 5}  // latwe
        };
        complexBoard = Sudoku(b);
    }
};

TEST_F(SudokuTest, getNr_works)
{
    int row = 0;
    int col = 7;
    auto expectedRowNr = 0;
    auto expectedColNr = 7;
    auto expectedSquareNr = 2;

    auto expectedField = Field(8);

    ASSERT_EQ(board.getField(row, col), expectedField);

    ASSERT_EQ(expectedRowNr, this->board.getRowNr(row,col));
    ASSERT_EQ(expectedColNr, this->board.getColumnNr(row,col));
    ASSERT_EQ(expectedSquareNr, this->board.getSquareNr(row,col));
}

TEST_F(SudokuTest, getVectors_works)
{
    int row = 0;
    int col = 7;
    auto expectedRow = std::vector<int>{1,2,3,0,5,0,7,8,9};
    auto expectedCol = std::vector<int>(9, 8);
    auto expectedSquare = std::vector<int>{7,8,9,7,8,9,7,8,9};

    auto sourceRow = this->board.getRow(board.getRowNr(row,col));
    auto sourceCol = this->board.getColumn(board.getColumnNr(row,col));
    auto sourceSquare = this->board.getSquare(board.getSquareNr(row,col));
    ASSERT_EQ(sourceRow, expectedRow);
    ASSERT_EQ(sourceCol, expectedCol);
    ASSERT_EQ(sourceSquare , expectedSquare);
}

TEST_F(SudokuTest, getOptions_works)
{
    // checks whether function returns correct values if called for empty cell
    int row = 3;
    int col = 5;
    vector<Field> expectedOutcome = vector<Field>{1};
    ASSERT_EQ(complexBoard.getOptions(row, col), expectedOutcome);

    // checks whether function returns empty vector if called for fileld cell
    row = 0;
    col = 0;
    ASSERT_EQ(complexBoard.getOptions(row, col), vector<Field>{});
}

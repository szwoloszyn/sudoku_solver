#include <gtest/gtest.h>
#include "../src/sudoku.h"

using std::vector;
using std::set;
using std::pair;
using std::map;

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
    set<Field> expectedOutcome = set<Field>{1};
    ASSERT_EQ(complexBoard.getOptions(row, col), expectedOutcome);

    // checks whether function returns empty vector if called for fileld cell
    row = 0;
    col = 0;
    ASSERT_EQ(complexBoard.getOptions(row, col), set<Field>{});
}

// BUG THIS TEST NOT RUNNING ???
TEST_F(SudokuTest, fillCertainFields_works)
{
    vector<vector<int>> solvedBoard{
        {7,9, 5, 3, 1, 8, 6, 2, 4},
        {1, 6, 8, 4, 5, 2, 7, 9, 3},
        { 3, 4, 2, 9, 7, 6, 5, 1, 8},
        { 9, 2, 4, 6, 8, 1, 3, 5, 7},
        { 5, 7, 3, 2, 4, 9, 1, 8, 6},
        {8, 1, 6, 5, 3, 7, 9, 4, 2},
        {4, 8, 9, 7, 6, 5, 2, 3, 1},
        {6, 5, 1, 8, 2, 3, 4, 7, 9},
        {2, 3, 7, 1, 9, 4, 8, 6, 5}  // solved
    };
    Sudoku expectedBoard{solvedBoard};
    Sudoku testBoard = complexBoard; // shallow copy should do just fine
    auto testFlag = testBoard.fillCertainFields();
    ASSERT_EQ(testBoard.getBoard(), expectedBoard.getBoard());
    ASSERT_TRUE(testFlag);
}


TEST_F(SudokuTest, geOptionsPerStructures_works)
{
    int row = 0;
    vector<set<Field>> expectedRowResult = {
        set<Field>{},  set<Field>{}, set<Field>{},
        set<Field>{3}, set<Field>{}, set<Field>{},
        set<Field>{6}, set<Field>{}, set<Field>{4}
    };

    int col = 2;
    vector<set<Field>> expectedColResult = {
        set<Field>{},  set<Field>{8}, set<Field>{},
        set<Field>{4}, set<Field>{}, set<Field>{},
        set<Field>{}, set<Field>{}, set<Field>{}
    };

    int square = 2;
    vector<set<Field>> expectedSquareResult = {
        set<Field>{6},  set<Field>{}, set<Field>{4},
        set<Field>{}, set<Field>{9}, set<Field>{},
        set<Field>{}, set<Field>{}, set<Field>{}
    };
    ASSERT_EQ(complexBoard.getOptionsPerRow(row), expectedRowResult);
    ASSERT_EQ(complexBoard.getOptionsPerColumn(col), expectedColResult);
    ASSERT_EQ(complexBoard.getOptionsPerSquare(square), expectedSquareResult);
}

TEST_F(SudokuTest, getUniqueValues_works)
{
    vector<pair<set<Field>, int>> input0 = {
        pair<set<Field>, int>{{1,6},1},
        pair<set<Field>, int>{{6,1},2},
        pair<set<Field>, int>{{2,6},7}
    };
    map<int, Field> expected0 = {
        {7, Field{2}}
    };
    ASSERT_EQ(Sudoku::getUniqueValues(input0), expected0);


    vector<pair<set<Field>, int>> input1 = {
        {{1, 2}, 0},
        {{2, 3}, 1},
        {{3, 4}, 2},
        {{4, 5}, 3}
    };

    map<int, Field> expected1 = {
        {0, Field{1}},
        {3, Field{5}}
    };
    ASSERT_EQ(Sudoku::getUniqueValues(input1), expected1);


    vector<pair<set<Field>, int>> input2 = {
        {{1, 2}, 0},
        {{1, 2}, 1},
        {{1, 2}, 2}
    };

    map<int, Field> expected2 = { };
    ASSERT_EQ(Sudoku::getUniqueValues(input2), expected2);


    vector<pair<set<Field>, int>> input3 = {
        {{1}, 0},
        {{1, 2}, 1},
        {{3}, 2},
        {{2}, 3}
    };

    map<int, Field> expected3 = {
        {2, Field{3}}
    };
    ASSERT_EQ(Sudoku::getUniqueValues(input3), expected3);


    vector<pair<set<Field>, int>> input4 = {
        {{1, 2, 3}, 0},
        {{2, 3, 4}, 1},
        {{3, 4, 5}, 2},
        {{4, 5, 6}, 3},
        {{5, 6, 7}, 4}
    };

    map<int, Field> expected4 = {
        {0, Field{1}},
        {4, Field{7}}
    };
    ASSERT_EQ(Sudoku::getUniqueValues(input4), expected4);


    vector<pair<set<Field>, int>> input5 = {
        {{}, 0},
        {{1, 2}, 1},
        {{2, 3}, 2}
    };

    map<int, Field> expected5 = {
        {1, Field{1}},
        {2, Field{3}}
    };
    ASSERT_EQ(Sudoku::getUniqueValues(input5), expected5);
    vector<pair<set<Field>, int>> input6 = {
    };

    map<int, Field> expected6 = {
    };
    ASSERT_EQ(Sudoku::getUniqueValues(input6), expected6);
}

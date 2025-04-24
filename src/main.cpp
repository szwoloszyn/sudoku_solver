#include <iostream>
#include <vector>

#include "sudoku.h"
using namespace std;



int main()
{
    vector<vector<int>> b{
        {7,9, 5, 0, 1, 8, 0, 2, 0},
        {1, 6, 0, 4, 0, 2, 7, 0, 3},
        { 3, 4, 2, 9, 7, 6, 5, 1, 8},
        { 9, 0, 0, 6, 8, 0, 3, 0, 7},
        { 5, 7, 3, 2, 4, 9, 1, 8, 6},
        {8, 1, 6, 0, 3, 7, 9, 4, 2},
        {4, 8, 9, 7, 6, 5, 2, 3, 1},
        {6, 5, 1, 8, 2, 0, 4, 7, 9},
        {2, 3, 7, 1, 9, 4, 8, 6, 5}  // latwe
    };
    Sudoku myBoard(b);
    myBoard.printBoard();
    myBoard.solveSudoku();
    std::cout << "\n=====\n";
    myBoard.printBoard();

    vector<vector<int>> c{
        {7,0, 5, 3, 0, 8, 6, 0, 4},
        {1, 0, 0, 4, 0, 2, 0, 0, 3},
        {0, 0, 2, 0, 0, 0, 5, 0, 0},
        { 0, 0, 4, 6, 0, 1, 3, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 6, 5, 0, 7, 9, 0, 0},
        {0, 0, 9, 0, 0, 0, 2, 0, 0},
        {6, 0, 0, 8, 0, 3, 0, 0, 9},
        {2, 0, 7, 1, 0, 4, 8, 0, 5} // nr1
    };
    Sudoku test1(c);
    std::cout << "\n\n";
    test1.printBoard();
    test1.solveSudoku();
    std::cout << "\n=====\n";
    test1.printBoard();
//    myBoard.fillCertainFields();
//    myBoard.printBoard();

//    std::cout << "\n=====\n";
//    vector<pair<set<Field>, int>> input5 = {
//        {{}, 0},
//        {{1, 2}, 1},
//        {{2, 3}, 2}
//    };
//    auto got = Sudoku::getUniqueValues(input5);
//    for (auto x : got) {
//        std::cout << x.first << " $ " << (int)x.second << "\n";
//    }

}

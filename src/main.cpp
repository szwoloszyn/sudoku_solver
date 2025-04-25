#include <iostream>
#include <vector>
#include <unistd.h> // for std::sleep()
#include "sudoku.h"
using namespace std;



int main()
{
    vector<vector<int>> b{
        {7,9, 5, 0, 1, 8, 0, 2, 0},
        {1, 6, 0, 4, 0, 0, 7, 0, 3},
        { 3, 0, 2, 9, 7, 6, 5, 1, 8},
        { 9, 0, 0, 0, 8, 0, 3, 0, 7},
        { 0, 7, 3, 2, 4, 9, 0, 8, 0},
        {8, 1, 6, 0, 3, 7, 9, 4, 2},
        {0, 8, 9, 7, 6, 5, 2, 3, 1},
        {6, 5, 0, 8, 2, 0, 4, 7, 0},
        {2, 0, 7, 0, 0, 4, 8, 6, 0}  // latwe
    };
    Sudoku myBoard(b);
    myBoard.printBoard();
    while(myBoard.fillCertainFields()) {}
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
    test1.iterateThroughStructures();
    std::cout << "\n=====\n";
    //test1.fillCertainFields();
      test1.printBoard();


      vector<vector<int>> sudokuEasy = {
          {0, 0, 4, 0, 0, 1, 6, 0, 2},
          {5, 0, 0, 4, 0, 9, 0, 3, 0},
          {0, 1, 3, 2, 8, 0, 0, 0, 0},
          {0, 0, 0, 7, 0, 4, 9, 0, 8},
          {4, 2, 9, 8, 1, 5, 7, 6, 3},
          {0, 7, 8, 0, 0, 2, 0, 0, 0},
          {8, 3, 2, 9, 4, 6, 1, 5, 7},
          {0, 4, 0, 0, 2, 0, 0, 9, 0},
          {1, 0, 0, 7, 0, 0, 0, 0, 4}
      };

      std::cout << "\n\n\n";
    Sudoku test2(sudokuEasy);
    test2.printBoard();
    while (test2.fillCertainFields()) {
        test2.printBoard();
        std::cout << "\n-----\n";
        //sleep(1);
    }
    std::cout << "\n";
    test2.printBoard();


    std::vector<std::vector<int>> grid = {
        {0, 8, 4, 5, 3, 1, 6, 7, 2},
        {5, 6, 7, 4, 0, 9, 8, 3, 1},
        {9, 1, 3, 2, 8, 7, 5, 4, 0},
        {3, 5, 1, 7, 6, 4, 9, 2, 8},
        {4, 2, 9, 8, 1, 5, 7, 6, 3},
        {6, 7, 8, 3, 9, 2, 4, 1, 5},
        {8, 3, 2, 9, 4, 6, 1, 5, 7},
        {7, 4, 5, 1, 2, 8, 3, 9, 6},
        {1, 9, 6, 7, 5, 3, 2, 8, 4}
    };
    Sudoku test3(grid);
    // BUG THIS SUDOKU IS FALSE !!!!!
    test3.fillCertainFields();
    cout << "\n";
    test3.printBoard();
//test1.printBoard();
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

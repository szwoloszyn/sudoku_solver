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

    // solvable only with fillCertainFields()
    vector<vector<int>> easyGrid = {
        {1, 0, 0, 4, 8, 9, 0, 0, 6},
        {7, 3, 0, 0, 0, 0, 0, 4, 0},
        {0, 0, 0, 0, 0, 1, 2, 9, 5},
        {0, 0, 7, 1, 2, 0, 6, 0, 0},
        {5, 0, 0, 7, 0, 3, 0, 0, 8},
        {0, 0, 6, 0, 9, 5, 7, 0, 0},
        {9, 1, 4, 6, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 3, 7},
        {8, 0, 0, 5, 1, 2, 0, 0, 4}
    };



    vector<vector<int>> easyGridSolved = {
        {1, 5, 2, 4, 8, 9, 3, 7, 6},
        {7, 3, 9, 2, 5, 6, 8, 4, 1},
        {4, 6, 8, 3, 7, 1, 2, 9, 5},
        {3, 8, 7, 1, 2, 4, 6, 5, 9},
        {5, 9, 1, 7, 6, 3, 4, 2, 8},
        {2, 4, 6, 8, 9, 5, 7, 1, 3},
        {9, 1, 4, 6, 3, 7, 5, 8, 2},
        {6, 2, 5, 9, 4, 8, 1, 3, 7},
        {8, 7, 3, 5, 1, 2, 9, 6, 4}
    };
    Sudoku test1(easyGrid);
    std::cout << "\n\n";
    test1.printBoard();

    std::cout << "\n=====\n";
    while (test1.fillCertainFields()) {}
    if (!test1.isSolved()) {
        std::cout << "INVALID SUDOKU BOARD!!!\n";
    }
    else {
        cout << "ALL GOOD\n";

    }
    test1.printBoard();

    std::cout << "\nINTERMEDIATE: \n\n";
    vector<vector<int>> intermediateGrid = {
        {0, 2, 0, 6, 0, 8, 0, 0, 0},
        {5, 8, 0, 2, 3, 9, 7, 0, 1},
        {0, 0, 0, 0, 4, 0, 0, 0, 0},
        {3, 7, 0, 4, 6, 1, 5, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 0, 4},
        {0, 0, 8, 0, 0, 0, 0, 1, 3},
        {8, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 9, 8, 5, 0, 4, 3, 6},
        {0, 4, 0, 3, 0, 6, 0, 9, 0}
    };

    vector<vector<int>> intermediateGridSolved = {
        {1, 2, 3, 6, 7, 8, 9, 4, 5},
        {5, 8, 4, 2, 3, 9, 7, 6, 1},
        {9, 6, 7, 1, 4, 5, 3, 2, 8},
        {3, 7, 2, 4, 6, 1, 5, 8, 9},
        {6, 9, 1, 5, 8, 3, 2, 7, 4},
        {4, 5, 8, 7, 9, 2, 6, 1, 3},
        {8, 3, 6, 9, 2, 4, 1, 5, 7},
        {2, 1, 9, 8, 5, 7, 4, 3, 6},
        {7, 4, 5, 3, 1, 6, 8, 9, 2}
    };
    Sudoku test2(intermediateGrid);
    while (test2.iterateThroughStructures()) {

        while (test2.fillCertainFields()) {
            if (!test2.isValid()) {
                std::cout << "SUDOKU FAILED! Printing current state: \n";
                test2.printBoard();
                return 0;
            }
        }
    }
    bool flag1 = test2.iterateThroughStructures();
    bool flag2 = test2.fillCertainFields();
    if (!(flag1 or flag2)) {
        std::cout << "rzeczywiscie";
    }
    test2.printBoard();


}

/*
 * option 1: creating multiOptions vector is incorrect
 * option 2: getUniqueValues method is incorrect (to be checked with tests on intermediate grid)
 * option 3: filling (place where if) is incorrect. highly doubtable
 *
 * FIXME CONCLUSION OPTION 2 IS CORRECT - TO BE CONTINUED
*/


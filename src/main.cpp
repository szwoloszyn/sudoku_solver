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
    auto x = myBoard.getOptions(3,2);
    for (auto i : x) {
        std::cout << i.getFieldValue() << " ";
    }
    std::cout << "\n=====\n";
    myBoard.fillCertainFields();
    myBoard.printBoard();

    std::cout << "\n=====\n";
    vector<pair<set<Field>, int>> input = {
        pair<set<Field>, int>{{1,6},1},
        pair<set<Field>, int>{{6,1},2},
        pair<set<Field>, int>{{2,6},7}
    };
    auto got = Sudoku::getUniqueValues(input);
    for (auto x : got) {
        std::cout << x.first << " $ " << (int)x.second << "\n";
    }

}

#include <iostream>
#include "sudoku.h"

using std::vector;
using std::set;
using std::pair;
using std::map;

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

// NOTE: these functions should be deleted later on
std::ostream& operator<<(std::ostream& os, const set<Field>& set) {
    os << "{ ";
    for (auto x : set) {
        os << (int)x << " ";
    }
    os << "} \n";
    return os;
}
void myOwnprintMap(const std::map<int, set<Field>>& m) {
    for (const auto& [key, value] : m) {
        std::cout << key << " : " << value << std::endl;
    }
}

map<int, Field> Sudoku::getUniqueValues(const std::vector<std::pair<std::set<Field>, int> >& multiOptions)
{
    map<int, set<Field>> fieldsIdx;
    map<Field, int> fieldsCount;
    for (const auto& setWithIdx : multiOptions) {
        for (auto iter = setWithIdx.first.begin(); iter != setWithIdx.first.end();) {
            fieldsCount[*(iter)]++;
            if (fieldsCount.at(*(iter)) == 1) {
                fieldsIdx[setWithIdx.second].insert(*(iter));
            }
            else {
                for (auto& idx_field : fieldsIdx ) {
                    idx_field.second.erase(*(iter));
                }

                fieldsIdx[setWithIdx.second].erase(*(iter));
            }
            iter++;
        }
    }
    //myOwnprintMap(fieldsIdx);
    map<int, Field> output;
    for (auto iter = fieldsIdx.begin(); iter != fieldsIdx.end();) {
        if (iter->second.size() > 1 or iter->second.size() == 0) {
            iter = fieldsIdx.erase(iter);
        }
        else if (iter->second.size() == 1) {
            output[iter->first] = *(iter->second.begin());
            iter++;
        }
        else {
            std::cout << "tf going on";
            return map<int, Field>{};
        }
    }
    return output;
}


std::set<Field> Sudoku::getOptions(int row, int col) const
{
    if (!this->getField(row, col).isBlank()) {
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

std::vector<std::set<Field>> Sudoku::getOptionsPerRow(int rowNr) const
{
    vector<set<Field>> options{};
    for (int i = 0; i < 9; ++i) {
        options.push_back(this->getOptions(rowNr, i));
    }
    return options;
}

std::vector<std::set<Field>> Sudoku::getOptionsPerColumn(int colNr) const
{
    vector<set<Field>> options{};
    for (int i = 0; i < 9; ++i) {
        options.push_back(this->getOptions(i, colNr));
    }
    return options;
}

std::vector<std::set<Field>> Sudoku::getOptionsPerSquare(int squareNr) const
{
    vector<set<Field>> options{};
    int startCol = 3 * (squareNr%3);
    int startRow = 3 * (squareNr/3);
    int col = startCol;
    int row = startRow;
    for (int i = 0; i < 9; ++i) {
        options.push_back(this->getOptions(row, col));
        col++;
        if (i%3 == 2) {
            row++;
            col = startCol;
        }
    }
    return options;
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
    return sthFilled;
}

bool Sudoku::iterateThroughStructures()
{
    //std::cout << "#";

    bool sthFilled = false;
    // iterating through rows:
    for (int rowNr = 0; rowNr < 9; ++rowNr) {
        auto rowOptions = getOptionsPerRow(rowNr);
        if (rowOptions.size() != 9) {
            std::cerr << "WTF GOIN ON!!!";
            return false;
        }
        vector<pair<set<Field>, int>> multiOptions;
        for (int colNr = 0; colNr < 9; ++colNr) {
            // checking whether already filled cell
            if (rowOptions.at(colNr).size() == 0) {
                continue;
            }
            // inserting certaing values
            if (rowOptions.at(colNr).size() == 1) {
                sudokuBoard.at(rowNr).at(colNr) = *(rowOptions.at(colNr).begin());
                sthFilled = true;
            }
            else {
                multiOptions.push_back(pair<set<Field>,int>(rowOptions.at(colNr), colNr));
            }
        }
        // analyzing multiOptions, searching for unambiguous Fields' numbers
        auto fieldsToInsert = Sudoku::getUniqueValues(multiOptions);
        for (const auto& element : fieldsToInsert) {
            if (this->sudokuBoard.at(rowNr).at(element.first) != Field{0}) {
                std::cerr << "tfff";
                return false;
            }
            std::cout << "#";
            this->sudokuBoard.at(rowNr).at(element.first) = element.second;
            sthFilled = true;
        }
    }

    //iterating through columns
    for (int colNr = 0; colNr < 9; ++colNr) {
        this->printBoard();
        auto colOptions = getOptionsPerColumn(colNr);
        if (colOptions.size() != 9) {
            std::cerr << "WTF GOIN ON!!!";
            return false;
        }
        vector<pair<set<Field>, int>> multiOptions;
        for (int rowNr = 0; rowNr < 9; ++rowNr) {
            if (colOptions.at(rowNr).size() == 0) {
                continue;
            }
            if (colOptions.at(rowNr).size() == 1) {
                //this->sudokuBoard.at(rowNr).at(colNr) = *(colOptions.at(rowNr).begin());
                sthFilled = true;
            }
            else {
                multiOptions.push_back(pair<set<Field>,int>(colOptions.at(rowNr), rowNr));
            }
        }
        for (auto i : multiOptions) {
            if (i.second == 8) {
                std::cerr << " " << i.first << "\n";
            }
        }
        auto fieldsToInsert = Sudoku::getUniqueValues(multiOptions);
        for (auto i : fieldsToInsert) {
            if (i.first == 8) {
                // ISSUE HERE!!!!
                std::cerr << " this: " << i.second << "\n";
            }
        }
        for (const auto& element : fieldsToInsert) {
            if (this->sudokuBoard.at(element.first).at(colNr) != Field{0}) {
                std::cerr << "tfff";
                return false;
            }
            // BUG THIS IS INSERTING FAKE 2 IN MY SUDOKU (PROBABLY STH WRONG WITH GETUNIQUEVALUES) ://
            if (element.first == 8 and colNr == 0) {
                std::cerr << colOptions.at(8);
                this->printBoard();
                std::cerr << "2";
                exit(1);
            }
            std::cout << "#";
            this->sudokuBoard.at(element.first).at(colNr) = element.second;
            sthFilled = true;
        }
    }

    //TODO iterating through squares
    return sthFilled;
}

bool Sudoku::isFilled() const
{
    for (auto row : sudokuBoard) {
        for (auto cell : row) {
            if (cell == Field{0}) {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::isValid() const
{
    if (isFilled()) {
        for (int i = 0; i < 9; ++i) {
            auto tmpRow = this->getRow(i);
            auto tmpCol = this->getColumn(i);
            auto tmpSquare = this->getSquare(i);
            set<Field> rowFields{tmpRow.begin(), tmpRow.end()};
            set<Field> colFields{tmpCol.begin(), tmpCol.end()};
            set<Field> squareFields{tmpSquare.begin(), tmpSquare.end()};
            auto expectedFields = Field::getAllPossibleValues();
            if (rowFields != expectedFields||colFields != expectedFields||squareFields != expectedFields) {
                return false;
            }
        }
        return true;
    }
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (sudokuBoard.at(row).at(col) != Field{0}) {
                continue;
            }
            auto opts = this->getOptions(row, col);
            if (opts.size() == 0) {
                // nie ma już czego tutaj wstawić -> sudoku musi być błędne
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::isSolved() const
{
    return isFilled() and isValid();
}


bool Sudoku::solveSudoku()
{
    do {
        //while(fillCertainFields()) {
        //}
    }while (iterateThroughStructures());
    return true;
    while(fillCertainFields()) {}
}



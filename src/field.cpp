#include "field.h"
#include <iostream>
#include <algorithm>
using std::vector;
using std::set;

bool foo()
{
    return 1;
}

Field::Field() : blank{true} , value{0}
{

}

Field::Field(int a) : blank{false}
{
    if (a == 0) {
        this->blank = true;
        this->value = 0;
        return;
    }
    this->blank = false;
    if (!(a > 0 and a < 10)) {
        throw std::out_of_range{"sudoku field can only contain values in range from 1 to 9"};
    }
    this->value = a;
}

// NOTE: this function will return 0 when Field is blank
int Field::getFieldValue() const
{
    return this->value;
}

bool Field::isBlank() const
{
    return blank;
}

// NOTE: comparators will always return true (== false) when called on blank field !
bool Field::operator>(const Field &comp) const
{
    return this->value > comp.value;
}

bool Field::operator>(int comp) const
{
    return this->value > comp;
}

bool Field::operator<(const Field &comp) const
{
    return this->value < comp.value;
}

bool Field::operator<(int comp) const
{
    return this->value < comp;
}

bool Field::operator==(const Field &comp) const
{
    return this->value == comp.value;
}

bool Field::operator==(int comp) const
{
    return this->value == comp;
}

Field& Field::operator=(int a)
{
    if (a == 0) {
        this->blank = true;
        this->value = 0;
        return *this;
    }
    this->blank = false;
    if (!(a > 0 and a < 10)) {
        throw std::out_of_range{"sudoku field can only contain values in range from 1 to 9"};
    }
    this->value = a;
    return *this;
}

set<Field> Field::getAllPossibleValues()
{
    return set<Field>{1,2,3,4,5,6,7,8,9};
//    vector<Field> all;
//    for (int i = 1 ; i <= 9 ; ++i) {
//        all.push_back(Field{i});
//    }
//    return all;
}

std::set<Field> getLackingValues(const std::set<Field>& pVals)
{
    auto presentValues{pVals};
    auto allValues = Field::getAllPossibleValues();
    set<Field> absentValues{};
    std::set_difference(allValues.begin(), allValues.end(),
                        presentValues.begin(), presentValues.end(),
                        std::inserter(absentValues, absentValues.begin()));
    return absentValues;
}

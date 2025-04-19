#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <set>
bool foo();

// Field object is going to represent single value in one sudoku box
class Field
{
public:
    Field();
    Field(int a);
    int getFieldValue() const;
    bool isBlank() const;

    bool operator>(const Field& comp) const;
    bool operator>(int comp) const;

    bool operator<(const Field& comp) const;
    bool operator<(int comp) const;

    bool operator==(const Field& comp) const;
    bool operator==(int comp) const;

    operator int() const {
        return this->value;
    }

    Field& operator=(int a);
    static std::set<Field> getAllPossibleValues();
private:
    int value;
    bool blank;
};

std::set<Field> getLackingValues(const std::set<Field>& pVals);

#endif // FIELD_H

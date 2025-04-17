#ifndef FIELD_H
#define FIELD_H

#include <vector>

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

    Field& operator=(int a);
    static std::vector<Field> getAllPossibleValues();
private:
    int value;
    bool blank;
};

std::vector<Field> getLackingValues(const std::vector<Field>& pVals);

#endif // FIELD_H

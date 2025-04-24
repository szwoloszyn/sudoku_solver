#include <gtest/gtest.h>
#include "../src/field.h"

using std::vector;
using std::set;

class FieldTest : public ::testing::Test
{
protected:
    set<Field> allValues;
    Field exampleVal{4};
    void SetUp() override {
        allValues = Field::getAllPossibleValues();
        exampleVal = Field{4};
    }
};

TEST_F(FieldTest, allPosibbleVals_are_correct)
{
    set<Field> all;
    for (int i = 1 ; i <= 9 ; ++i) {
        all.insert(Field{i});
    }
    ASSERT_EQ(all, allValues);

}

TEST_F(FieldTest, comparatorsWork)
{
    // exampleVal = 4
    ASSERT_TRUE(Field{8} > exampleVal);
    ASSERT_TRUE(exampleVal > 3);
    ASSERT_TRUE(Field{2} < exampleVal);
    ASSERT_TRUE(exampleVal < 9);

    ASSERT_TRUE(exampleVal == Field{4});
    ASSERT_TRUE(exampleVal == 4);

    Field anotherExample = 4;
    ASSERT_EQ(exampleVal, anotherExample);
    ASSERT_FALSE(anotherExample.isBlank());
    anotherExample = 0;
    ASSERT_TRUE(anotherExample.isBlank());

    Field lastExample = 0;
    //ASSERT_TRUE(lastExample.isBlank());
    ASSERT_EQ(lastExample.getFieldValue(), 0);
}

TEST_F(FieldTest, lackingValues_are_correct)
{
    set<Field> current{2,6,7,9};
    set<Field> expected{1,3,4,5,8};
    ASSERT_EQ(getLackingValues(current), expected);
}

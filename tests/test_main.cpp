#include <gtest/gtest.h>
#include "../src/field.h"

using std::vector;

TEST(FieldTester, foo_function) {
    EXPECT_EQ(foo(), true);
}

TEST(AnotherOne, always_true) {
    EXPECT_EQ(42,42);
}

class FieldTest : public ::testing::Test
{
protected:
    vector<Field> allValues;
    Field exampleVal{4};
    void SetUp() override {
        allValues = Field::getAllPossibleValues();
        exampleVal = Field{4};
    }
};

TEST_F(FieldTest, allPosibbleVals_are_correct)
{
    vector<Field> all;
    for (int i = 1 ; i <= 9 ; ++i) {
        all.push_back(Field{i});
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
}

TEST_F(FieldTest, lackingValues_are_correct)
{
    vector<Field> current{2,6,7,9};
    vector<Field> expected{1,3,4,5,8};
    ASSERT_EQ(getLackingValues(current), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

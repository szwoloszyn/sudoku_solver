#include <gtest/gtest.h>
#include "../src/field.h"

using std::vector;

TEST(FieldTester, foo_function) {
    EXPECT_EQ(foo(), true);
}

TEST(AnotherOne, always_true) {
    EXPECT_EQ(42,42);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

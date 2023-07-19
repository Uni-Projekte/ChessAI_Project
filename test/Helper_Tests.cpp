#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/helper.h"

TEST(HelperTest, FieldIndexTest) {
    uint8_t fieldIndex = FieldIndex(2,2);
    EXPECT_EQ(fieldIndex, 0b010101);
}

TEST(HelperTest, CreateMoveTest) {
    MOVE move = CreateMove(0,0,2,2,0);
    PrintMove(move);
    EXPECT_EQ(move, 0b000111010101);
}
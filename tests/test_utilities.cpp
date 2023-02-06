#include <gtest/gtest.h>
#include "mt/utilities.hpp"

#include "mt/exceptions.hpp"

TEST(UtilitiesTest, sub2idx_Valid) {
	EXPECT_EQ(mt::sub2idx(0, 0, 0, 2, 2, 2), 0);
	EXPECT_EQ(mt::sub2idx(0, 0, 1, 2, 2, 2), 1);
	EXPECT_EQ(mt::sub2idx(0, 1, 0, 2, 2, 2), 2);
	EXPECT_EQ(mt::sub2idx(1, 0, 0, 2, 2, 2), 4);
}

TEST(UtilitiesTest, sub2idx_Invalid) {
	EXPECT_THROW(mt::sub2idx(-1, 0, 0, 2, 2, 2), mt::IndexError);
	EXPECT_THROW(mt::sub2idx(0, 0, 2, 2, 2, 2), mt::IndexError);
}

TEST(UtilitiesTest, isValidIdx_Valid) {
	EXPECT_TRUE(mt::isValidIdx(0, 10));
	EXPECT_TRUE(mt::isValidIdx(9, 10));
}

TEST(UtilitiesTest, isValidIdx_Invalid) {
	EXPECT_FALSE(mt::isValidIdx(10, 10));
}

TEST(UtilitiesTest, isValidSize_Valid) {
	EXPECT_TRUE(mt::isValidSize(1));
	EXPECT_TRUE(mt::isValidSize(100));
}

TEST(UtilitiesTest, isValidSize_Invalid) {
	EXPECT_FALSE(mt::isValidSize(0));
}

#include <gtest/gtest.h>
#include "mt/utilities.hpp"

#include "mt/exceptions.hpp"

TEST(UtilitiesTest, sub2idx_Valid) {
	EXPECT_EQ(mt::sub2idx(mt::Subscript2d(0, 0), mt::Shape2d(2, 2)), 0);
	EXPECT_EQ(mt::sub2idx(mt::Subscript2d(0, 1), mt::Shape2d(2, 2)), 1);
	EXPECT_EQ(mt::sub2idx(mt::Subscript2d(1, 0), mt::Shape2d(2, 2)), 2);

	EXPECT_EQ(mt::sub2idx(mt::Subscript3d(0, 0, 0), mt::Shape3d(2, 2, 2)), 0);
	EXPECT_EQ(mt::sub2idx(mt::Subscript3d(0, 0, 1), mt::Shape3d(2, 2, 2)), 1);
	EXPECT_EQ(mt::sub2idx(mt::Subscript3d(0, 1, 0), mt::Shape3d(2, 2, 2)), 2);
	EXPECT_EQ(mt::sub2idx(mt::Subscript3d(1, 0, 0), mt::Shape3d(2, 2, 2)), 4);
}

TEST(UtilitiesTest, sub2idx_Invalid) {
	EXPECT_THROW(mt::sub2idx(mt::Subscript2d(0, 2), mt::Shape2d(2, 2)), mt::Exception);
	EXPECT_THROW(mt::sub2idx(mt::Subscript2d(2, 0), mt::Shape2d(2, 2)), mt::Exception);

	EXPECT_THROW(mt::sub2idx(mt::Subscript3d(0, 0, 2), mt::Shape3d(2, 2, 2)), mt::Exception);
	EXPECT_THROW(mt::sub2idx(mt::Subscript3d(0, 2, 0), mt::Shape3d(2, 2, 2)), mt::Exception);
	EXPECT_THROW(mt::sub2idx(mt::Subscript3d(2, 0, 0), mt::Shape3d(2, 2, 2)), mt::Exception);
}

TEST(UtilitiesTest, idx2sub_Valid) {
	EXPECT_EQ(mt::idx2sub(0, mt::Shape2d(2, 2)), mt::Subscript2d(0, 0));
	EXPECT_EQ(mt::idx2sub(1, mt::Shape2d(2, 2)), mt::Subscript2d(0, 1));
	EXPECT_EQ(mt::idx2sub(2, mt::Shape2d(2, 2)), mt::Subscript2d(1, 0));

	EXPECT_EQ(mt::idx2sub(0, mt::Shape3d(2, 2, 2)), mt::Subscript3d(0, 0, 0));
	EXPECT_EQ(mt::idx2sub(1, mt::Shape3d(2, 2, 2)), mt::Subscript3d(0, 0, 1));
	EXPECT_EQ(mt::idx2sub(2, mt::Shape3d(2, 2, 2)), mt::Subscript3d(0, 1, 0));
	EXPECT_EQ(mt::idx2sub(4, mt::Shape3d(2, 2, 2)), mt::Subscript3d(1, 0, 0));
}

TEST(UtilitiesTest, idx2sub_Invalid) {
	EXPECT_THROW(mt::idx2sub(4, mt::Shape2d(2, 2)), mt::Exception);
	EXPECT_THROW(mt::idx2sub(8, mt::Shape3d(2, 2, 2)), mt::Exception);
}

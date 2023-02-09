#include <gtest/gtest.h>
#include "mt/exceptions.hpp"

TEST(ExceptionTest, ExceptionMessage) {
	const std::string message = "Test exception message";
	mt::Exception e(message);
	EXPECT_STREQ(e.what(), message.c_str());
}

TEST(ShapeMismatchErrorTest, ShapeMismatchErrorMessage) {
	mt::ShapeMismatchError e1(10, 20, 30);
	EXPECT_STREQ(e1.what(), "Invalid shape: (10,20,30).");
	
	mt::ShapeMismatchError e2(10, 20, 30, 10, 20, 31);
	EXPECT_STREQ(e2.what(), "Mismatching shapes: (10,20,30) != (10,20,31).");

	mt::ShapeMismatchError e3(300, 10, 20, 30);
	EXPECT_STREQ(e3.what(), "Size does not match shape: 300 != 10*20*30.");

	mt::ShapeMismatchError e4(300, 10);
	EXPECT_STREQ(e4.what(), "Mismatching sizes: 300 != 10.");
}

TEST(IndexErrorTest, IndexErrorMessage) {
	mt::IndexError e1(11, 10);
	EXPECT_STREQ(e1.what(), "Index out of bounds: tried to access element 11 in object with size 10.");

	mt::IndexError e2(10, 19, 20, 10, 20, 30);
	EXPECT_STREQ(e2.what(), "Subscript out of bounds: tried to access element (10,19,20) in object with shape (10,20,30).");
}

TEST(DivideByZeroErrorTest, DivideByZeroErrorMessage) {
	mt::DivideByZeroError e;
	EXPECT_STREQ(e.what(), "Can't divide by zero.");
}

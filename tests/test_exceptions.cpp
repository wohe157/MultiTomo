#include <gtest/gtest.h>
#include "mt/exceptions.hpp"

TEST(ExceptionTest, ExceptionMessage) {
	const std::string message = "Test exception message";
	mt::Exception e(message);
	EXPECT_STREQ(e.what(), message.c_str());
}

#include <gtest/gtest.h>
#include "mt/data.hpp"

#include "mt/definitions.hpp"
#include "mt/exceptions.hpp"

TEST(DataTest, DefaultConstructor) {
    mt::Data data(10);
    EXPECT_EQ(data.size(), 10);
    for (mt::Size i = 0; i < data.size(); ++i) {
        EXPECT_FLOAT_EQ(data.get(i), 0.0f);
    }
}

TEST(DataTest, ValueConstructor) {
    mt::Data data(5, 1.23f);
    EXPECT_EQ(data.size(), 5);
    for (mt::Size i = 0; i < data.size(); ++i) {
        EXPECT_FLOAT_EQ(data.get(i), 1.23f);
    }
}

TEST(DataTest, CopyConstructor) {
    mt::Data original(5, 1.23f);
    mt::Data copy(original);
    EXPECT_EQ(original.size(), copy.size());
    for (mt::Size i = 0; i < original.size(); ++i) {
        EXPECT_FLOAT_EQ(original.get(i), copy.get(i));
    }
}

TEST(DataTest, Assignment_Valid) {
    mt::Data data1(10, 1.23f);
    mt::Data data2(10, 0.0f);
    data2 = data1;
    EXPECT_EQ(data1.size(), data2.size());
    for (mt::Size i = 0; i < data1.size(); ++i) {
        EXPECT_FLOAT_EQ(data1.get(i), data2.get(i));
    }
}

TEST(DataTest, Assignment_Invalid) {
    mt::Data data1(5, 1.23f);
    mt::Data data2(10, 0.0f);
    EXPECT_THROW(data2 = data1, mt::Exception);
}

TEST(DataTest, SetAndGet) {
    mt::Data data(3);
    data.set(0, 1.23f);
    data.set(1, 2.34f);
    data.set(2, 3.45f);
    EXPECT_FLOAT_EQ(data.get(0), 1.23f);
    EXPECT_FLOAT_EQ(data.get(1), 2.34f);
    EXPECT_FLOAT_EQ(data.get(2), 3.45f);
}

TEST(DataTest, SetAndGet_OutOfBounds)
{
    mt::Data data(3);
    EXPECT_THROW(data.get(3), mt::Exception);
    EXPECT_THROW(data.set(3, 1.23f), mt::Exception);
}

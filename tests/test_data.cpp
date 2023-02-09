#include <gtest/gtest.h>
#include "mt/data.hpp"

#include "mt/exceptions.hpp"

namespace {
    constexpr MT_SIZE rows = 2, cols = 3, slices = 2;
    constexpr MT_FLOAT value = 2.0f;
    const std::vector<MT_FLOAT> data = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f };
}

class DataTest : public ::testing::Test {
protected:
    mt::Data f_Data1, f_Data2;

    // This can't go to the SetUp method because
    // mt::Data doesn't have a default constructor
    DataTest() 
        : f_Data1(rows, cols, slices, data)
        , f_Data2(rows, cols, slices, 1.0f)
    {
    }
};

TEST_F(DataTest, ZeroConstructor) {
    mt::Data d(rows, cols, slices);
    EXPECT_EQ(d.rows(), rows);
    EXPECT_EQ(d.cols(), cols);
    EXPECT_EQ(d.slices(), slices);
    for (MT_SIZE i = 0; i < d.size(); i++)
        EXPECT_EQ(d.get(i), 0.0f);
}

TEST_F(DataTest, ValueConstructor) {
    mt::Data d(rows, cols, slices, value);
    EXPECT_EQ(d.rows(), rows);
    EXPECT_EQ(d.cols(), cols);
    EXPECT_EQ(d.slices(), slices);
    for (MT_SIZE i = 0; i < d.size(); i++)
        EXPECT_EQ(d.get(i), value);
}

TEST_F(DataTest, DataConstructor) {
    mt::Data d(rows, cols, slices, data);
    EXPECT_EQ(d.rows(), rows);
    EXPECT_EQ(d.cols(), cols);
    EXPECT_EQ(d.slices(), slices);
    for (MT_SIZE i = 0; i < d.size(); i++)
        EXPECT_EQ(d.get(i), data.at(i));
}

TEST_F(DataTest, CopyConstructor) {
    mt::Data d1(rows, cols, slices, data);
    mt::Data d2(d1);
    EXPECT_EQ(d2.rows(), rows);
    EXPECT_EQ(d2.cols(), cols);
    EXPECT_EQ(d2.slices(), slices);
    for (MT_SIZE i = 0; i < rows * cols * slices; i++)
        EXPECT_EQ(d2.get(i), data.at(i));
}

TEST_F(DataTest, AssignmentOperator) {
    mt::Data f_Data2 = f_Data1;
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data2.get(i), f_Data1.get(i));
}

TEST_F(DataTest, RowsMethod) {
    EXPECT_EQ(f_Data1.rows(), rows);
}

TEST_F(DataTest, ColsMethod) {
    EXPECT_EQ(f_Data1.cols(), cols);
}

TEST_F(DataTest, SlicesMethod) {
    EXPECT_EQ(f_Data1.slices(), slices);
}

TEST_F(DataTest, SizeMethod) {
    EXPECT_EQ(f_Data1.size(), rows * cols * slices);
}

TEST_F(DataTest, TestGetAndSetWithSingleIndex) {
    f_Data1.set(3, 42.0f);
    ASSERT_EQ(f_Data1.get(3), 42.0f);
}

TEST_F(DataTest, TestGetAndSetWithSubscript) {
    f_Data1.set(1, 2, 0, 42.0f);
    ASSERT_EQ(f_Data1.get(1, 2, 0), 42.0f);
}

TEST_F(DataTest, TestGetWithInvalidSingleIndex) {
    ASSERT_THROW(f_Data1.get(f_Data1.size()), mt::IndexError);
}

TEST_F(DataTest, TestGetWithInvalidSubscript) {
    ASSERT_THROW(f_Data1.get(f_Data1.rows(), f_Data1.cols(), f_Data1.slices()), mt::IndexError);
}

TEST_F(DataTest, TestSetWithInvalidSingleIndex) {
    ASSERT_THROW(f_Data2.set(f_Data2.size(), 42.0f), mt::IndexError);
}

TEST_F(DataTest, TestSetWithInvalidSubscript) {
    ASSERT_THROW(f_Data2.set(f_Data2.rows(), f_Data2.cols(), f_Data2.slices(), 42.0f), mt::IndexError);
}

TEST_F(DataTest, AdditionOperatorWithScalar) {
    f_Data1 += 1.0;
    mt::Data expected = mt::Data(2, 3, 2, { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f });
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data1.get(i), expected.get(i));
}

TEST_F(DataTest, AdditionOperatorWithData) {
    f_Data1 += f_Data2;
    mt::Data expected = mt::Data(2, 3, 2, { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f });
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data1.get(i), expected.get(i));
}

TEST_F(DataTest, AdditionOperatorThrows) {
    EXPECT_THROW(f_Data1 += mt::Data(2, 3, 1), mt::ShapeMismatchError);
}

TEST_F(DataTest, SubtractionOperatorWithScalar) {
    f_Data1 -= 1.0;
    mt::Data expected = mt::Data(2, 3, 2, { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f });
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data1.get(i), expected.get(i));
}

TEST_F(DataTest, SubtractionOperatorWithData) {
    f_Data1 -= f_Data2;
    mt::Data expected = mt::Data(2, 3, 2, { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f });
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data1.get(i), expected.get(i));
}

TEST_F(DataTest, SubtractionOperatorThrows) {
    EXPECT_THROW(f_Data1 -= mt::Data(2, 3, 1), mt::ShapeMismatchError);
}

TEST_F(DataTest, MultiplicationOperatorWithScalar) {
    f_Data1 *= 2.0;
    mt::Data expected = mt::Data(2, 3, 2, { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f });
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data1.get(i), expected.get(i));
}

TEST_F(DataTest, MultiplicationOperatorWithData) {
    f_Data1 *= mt::Data(2, 3, 2, { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f });;
    mt::Data expected = mt::Data(2, 3, 2, { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 12.0f });
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data1.get(i), expected.get(i));
}

TEST_F(DataTest, MultiplicationOperatorThrows) {
    EXPECT_THROW(f_Data1 *= mt::Data(2, 3, 1), mt::ShapeMismatchError);
}

TEST_F(DataTest, DivisionOperatorWithScalar) {
    f_Data1 /= 2.0;
    mt::Data expected = mt::Data(2, 3, 2, { 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f });
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data1.get(i), expected.get(i));
}

TEST_F(DataTest, DivisionOperatorWithData) {
    f_Data1 /= mt::Data(2, 3, 2, { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f });;
    mt::Data expected = mt::Data(2, 3, 2, { 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 12.0f });
    for (MT_SIZE i = 0; i < f_Data2.size(); i++)
        EXPECT_EQ(f_Data1.get(i), expected.get(i));
}

TEST_F(DataTest, DivisionOperatorThrows) {
    EXPECT_THROW(f_Data1 /= mt::Data(2, 3, 1, 1.0f), mt::ShapeMismatchError);
    EXPECT_THROW(f_Data1 /= mt::Data(2, 3, 2, 0.0f), mt::DivideByZeroError);
}

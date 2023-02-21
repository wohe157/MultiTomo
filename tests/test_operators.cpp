// MultiTomo
// Copyright (C) 2023  Wouter Heyvaert
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
#include <gtest/gtest.h>
#include "mt/operators.hpp"

#include "mt/definitions.hpp"
#include "mt/exceptions.hpp"
#include "mt/data.hpp"

TEST(OperatorTest, Constructor) {
	mt::Operator op({ 2, 3 });

	EXPECT_EQ(op.rows(), 2);
	EXPECT_EQ(op.cols(), 3);
	EXPECT_EQ(op.shape(), mt::Shape2d(2, 3));

	for (mt::Size i = 0; i < 2; i++) {
		for (mt::Size j = 0; j < 3; j++) {
			EXPECT_FLOAT_EQ(op.get({ i, j }), 0.0f);
		}
	}
}

TEST(OperatorTest, GetAndSet) {
	mt::Operator op({ 2, 3 });
	op.set({ 0, 0 }, 1.0f);
	op.set({ 1, 1 }, 1.5f);
	op.set({ 0, 1 }, 2.0f);

	EXPECT_EQ(op.get({ 0, 0 }), 1.0f);
	EXPECT_EQ(op.get({ 0, 1 }), 2.0f);
	EXPECT_EQ(op.get({ 0, 2 }), 0.0f);
	EXPECT_EQ(op.get({ 1, 0 }), 0.0f);
	EXPECT_EQ(op.get({ 1, 1 }), 1.5f);
	EXPECT_EQ(op.get({ 1, 2 }), 0.0f);
}

TEST(OperatorTest, GetAndSet_OutOfBounds) {
	mt::Operator op({ 2, 3 });

	EXPECT_THROW(op.set({ 2, 0 }, 0.0f), mt::Exception);
	EXPECT_THROW(op.set({ 0, 3 }, 0.0f), mt::Exception);

	EXPECT_THROW(op.get({ 2, 0 }), mt::Exception);
	EXPECT_THROW(op.get({ 0, 3 }), mt::Exception);
}

TEST(OperatorTest, Transpose) {
	mt::Operator op({ 2, 3 });
	op.set({ 0, 0 }, 1.0f);
	op.set({ 1, 1 }, 1.5f);
	op.set({ 0, 1 }, 2.0f);

	mt::Operator opt = op.transpose();

	EXPECT_EQ(op.shape(), mt::Shape2d(2, 3));
	EXPECT_EQ(opt.shape(), mt::Shape2d(3, 2));

	EXPECT_EQ(opt.get({ 0, 0 }), 1.0f);
	EXPECT_EQ(opt.get({ 1, 0 }), 2.0f);
	EXPECT_EQ(opt.get({ 2, 0 }), 0.0f);
	EXPECT_EQ(opt.get({ 0, 1 }), 0.0f);
	EXPECT_EQ(opt.get({ 1, 1 }), 1.5f);
	EXPECT_EQ(opt.get({ 2, 1 }), 0.0f);
}

TEST(OperatorTest, MultiplyWithData) {
	mt::Operator op({ 2, 3 });
	op.set({ 0, 0 }, 1.0f);
	op.set({ 0, 1 }, 2.0f);
	op.set({ 1, 1 }, 1.5f);
	op.set({ 1, 2 }, 1.0f);

	mt::Data d(3, 1.0f);
	d.set(2, 2.0f);

	mt::Data result = op * d;
	EXPECT_EQ(result.size(), 2);
	EXPECT_EQ(result.get(0), 3.0f);
	EXPECT_EQ(result.get(1), 3.5f);
}

TEST(OperatorTest, MultiplyWithData_Invalid) {
	mt::Operator op({ 2, 3 });
	mt::Data d1(2);
	mt::Data d2(5);

	EXPECT_THROW(op * d1, mt::Exception);
	EXPECT_THROW(op * d2, mt::Exception);
}

TEST(OperatorTest, MultiplyWithOperator) {
	mt::Operator op1({ 2, 3 });
	op1.set({ 0, 0 }, 1.0f);
	op1.set({ 0, 1 }, 2.0f);
	op1.set({ 1, 1 }, 1.5f);
	op1.set({ 1, 2 }, 1.0f);

	mt::Operator op2({ 3, 4 });
	op2.set({ 0, 0 }, 1.0f);
	op2.set({ 0, 1 }, 2.0f);
	op2.set({ 1, 0 }, 2.0f);

	mt::Operator op3 = op1 * op2;
	EXPECT_EQ(op3.shape(), mt::Shape2d(2, 4));
	EXPECT_EQ(op3.get({ 0, 0 }), 5.0f);
	EXPECT_EQ(op3.get({ 0, 1 }), 2.0f);
	EXPECT_EQ(op3.get({ 0, 2 }), 0.0f);
	EXPECT_EQ(op3.get({ 1, 0 }), 3.0f);
	EXPECT_EQ(op3.get({ 1, 1 }), 0.0f);
	EXPECT_EQ(op3.get({ 1, 2 }), 0.0f);
}

TEST(OperatorTest, MultiplyWithOperator_Invalid) {
	mt::Operator op1({ 2, 3 });
	mt::Operator op2({ 2, 2 });

	EXPECT_THROW(op1 * op2, mt::Exception);
}

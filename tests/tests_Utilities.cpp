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
#include "catch.hpp"
#include "multitomo.hpp"

TEST_CASE("Linear index can be calculated from a valid 2D subscript", "[sub2idx]")
{
	REQUIRE(mt::sub2idx(0, 0, 2, 3) == 0);
	REQUIRE(mt::sub2idx(0, 1, 2, 3) == 1);
	REQUIRE(mt::sub2idx(0, 2, 2, 3) == 2);
	REQUIRE(mt::sub2idx(1, 0, 2, 3) == 3);
	REQUIRE(mt::sub2idx(1, 1, 2, 3) == 4);
	REQUIRE(mt::sub2idx(1, 2, 2, 3) == 5);
}

TEST_CASE("Linear index can be calculated from a valid 3D subscript", "[sub2idx]")
{
	REQUIRE(mt::sub2idx(0, 0, 0, 2, 3, 2) == 0);
	REQUIRE(mt::sub2idx(0, 0, 1, 2, 3, 2) == 1);
	REQUIRE(mt::sub2idx(0, 1, 0, 2, 3, 2) == 2);
	REQUIRE(mt::sub2idx(1, 0, 0, 2, 3, 2) == 6);
	REQUIRE(mt::sub2idx(1, 2, 1, 2, 3, 2) == 11);
}

TEST_CASE("sub2idx throws if the shape contains one or more zeroes", "[sub2idx]")
{
	REQUIRE_THROWS(mt::sub2idx(0, 0, 0, 3));
	REQUIRE_THROWS(mt::sub2idx(0, 0, 2, 0));
	REQUIRE_THROWS(mt::sub2idx(0, 0, 0, 0, 3, 2));
	REQUIRE_THROWS(mt::sub2idx(0, 0, 0, 2, 0, 2));
	REQUIRE_THROWS(mt::sub2idx(0, 0, 0, 2, 3, 0));
}

TEST_CASE("sub2idx throws if one of the subscripts if out of bounds", "[sub2idx]")
{
	REQUIRE_THROWS(mt::sub2idx(0, 3, 2, 3));
	REQUIRE_THROWS(mt::sub2idx(2, 0, 2, 3));
	REQUIRE_THROWS(mt::sub2idx(0, 0, 2, 2, 3, 2));
	REQUIRE_THROWS(mt::sub2idx(0, 3, 0, 2, 3, 2));
	REQUIRE_THROWS(mt::sub2idx(2, 0, 0, 2, 3, 2));
}

TEST_CASE("validateShapeNonzero throws when one or more values are zero", "[validateShapeNonzero]")
{
	REQUIRE_NOTHROW(mt::validateShapeNonzero(1, 1));
	REQUIRE_NOTHROW(mt::validateShapeNonzero(1, 1, 1));

	REQUIRE_THROWS(mt::validateShapeNonzero(1, 0));
	REQUIRE_THROWS(mt::validateShapeNonzero(0, 1));
	REQUIRE_THROWS(mt::validateShapeNonzero(1, 1, 0));
	REQUIRE_THROWS(mt::validateShapeNonzero(1, 0, 1));
	REQUIRE_THROWS(mt::validateShapeNonzero(0, 1, 1));
}

TEST_CASE("validateSubscriptInBounds throws when one or more subscripts are too large", "[validateSubscriptInBounds]")
{
	REQUIRE_NOTHROW(mt::validateSubscriptInBounds(1, 1, 2, 2));
	REQUIRE_NOTHROW(mt::validateSubscriptInBounds(1, 1, 1, 2, 2, 2));

	REQUIRE_THROWS(mt::validateSubscriptInBounds(1, 2, 2, 2));
	REQUIRE_THROWS(mt::validateSubscriptInBounds(2, 1, 2, 2));
	REQUIRE_THROWS(mt::validateSubscriptInBounds(1, 1, 2, 2, 2, 2));
	REQUIRE_THROWS(mt::validateSubscriptInBounds(1, 2, 1, 2, 2, 2));
	REQUIRE_THROWS(mt::validateSubscriptInBounds(2, 1, 1, 2, 2, 2));
}

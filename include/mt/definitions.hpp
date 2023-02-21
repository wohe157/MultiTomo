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
#include "mt/pch.hpp"
#ifndef MT_DEFINITIONS_HPP
#define MT_DEFINITIONS_HPP

namespace mt
{

	typedef float Float;
	typedef size_t Size;

	struct Shape2d
	{
		Size rows;
		Size cols;

		bool operator==(const Shape2d& rhs) const;
	};

	struct Shape3d
	{
		Size rows;
		Size cols;
		Size slices;

		bool operator==(const Shape3d& rhs) const;
	};

	struct Subscript2d
	{
		Size i;
		Size j;

		bool operator==(const Subscript2d& rhs) const;
	};

	struct Subscript3d
	{
		Size i;
		Size j;
		Size k;

		bool operator==(const Subscript3d& rhs) const;
	};

} // namespace mt

#endif // MT_DEFINITIONS_HPP

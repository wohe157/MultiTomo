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
#ifndef MT_UTILITIES_HPP
#define MT_UTILITIES_HPP

#include "mt/definitions.hpp"

namespace mt
{

	Size sub2idx(const Subscript2d sub, const Shape2d shape);
	Size sub2idx(const Subscript3d sub, const Shape3d shape);

	Subscript2d idx2sub(const Size idx, const Shape2d shape);
	Subscript3d idx2sub(const Size idx, const Shape3d shape);

} // namespace mt

#endif // MT_UTILITIES_HPP

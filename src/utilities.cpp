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
#include "mt/utilities.hpp"

#include "mt/exceptions.hpp"

mt::Size mt::sub2idx(const mt::Subscript2d sub, const mt::Shape2d shape)
{
	if (sub.i >= shape.rows || sub.j >= shape.cols)
		throw mt::Exception(std::format("Subscript ({},{}) is out of bounds ({},{}).", sub.i, sub.j, shape.rows, shape.cols));

	return sub.i * shape.cols + sub.j;
}

mt::Size mt::sub2idx(const mt::Subscript3d sub, const mt::Shape3d shape)
{
	if (sub.i >= shape.rows || sub.j >= shape.cols || sub.k >= shape.slices)
		throw mt::Exception(std::format("Subscript ({},{},{}) is out of bounds ({},{},{}).", sub.i, sub.j, sub.k, shape.rows, shape.cols, shape.slices));

	return sub.i * shape.cols * shape.slices + sub.j * shape.slices + sub.k;
}

mt::Subscript2d mt::idx2sub(const mt::Size idx, const mt::Shape2d shape)
{
	if (idx >= (shape.rows * shape.cols))
		throw mt::Exception(std::format("Index ({}) is out of bounds ({},{}).", idx, shape.rows, shape.cols));

	mt::Size j = idx % shape.cols;
	mt::Size i = (idx - j) / shape.cols;
	return { i, j };
}

mt::Subscript3d mt::idx2sub(const mt::Size idx, const mt::Shape3d shape)
{
	if (idx >= (shape.rows * shape.cols * shape.slices))
		throw mt::Exception(std::format("Index ({}) is out of bounds ({},{},{}).", idx, shape.rows, shape.cols, shape.slices));

	mt::Size k = idx % shape.slices;
	mt::Size j = ((idx - k) / shape.slices) % shape.cols;
	mt::Size i = ((idx - k) / shape.slices - j) / shape.cols;
	return { i, j, k };
}

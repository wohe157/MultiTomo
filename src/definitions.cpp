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
#include "mt/definitions.hpp"

bool mt::Shape2d::operator==(const Shape2d& rhs) const
{
    return rows == rhs.rows && cols == rhs.cols;
}

bool mt::Shape3d::operator==(const Shape3d& rhs) const
{
    return rows == rhs.rows && cols == rhs.cols && slices == rhs.slices;
}

bool mt::Subscript2d::operator==(const Subscript2d& rhs) const
{
    return i == rhs.i && j == rhs.j;
}

bool mt::Subscript3d::operator==(const Subscript3d& rhs) const
{
    return i == rhs.i && j == rhs.j && k == rhs.k;
}

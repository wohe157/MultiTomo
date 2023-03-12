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
#include "multitomo.hpp"

#include <stdexcept>

namespace mt
{

    Uint sub2idx(const Uint i, const Uint j, const Uint ni, const Uint nj)
    {
        validateShapeNonzero(ni, nj);
        validateSubscriptInBounds(i, j, ni, nj);

        return i * nj + j;
    }

    Uint sub2idx(const Uint i, const Uint j, const Uint k, const Uint ni, const Uint nj, const Uint nk)
    {
        validateShapeNonzero(ni, nj, nk);
        validateSubscriptInBounds(i, j, k, ni, nj, nk);

        return i * nj * nk + j * nk + k;
    }

    void validateShapeNonzero(const Uint ni, const Uint nj)
    {
        if (ni < 1 || nj < 1)
            throw std::runtime_error("Shape cannot contain values less than 1.");
    }

    void validateShapeNonzero(const Uint ni, const Uint nj, const Uint nk)
    {
        if (ni < 1 || nj < 1 || nk < 1)
            throw std::runtime_error("Shape cannot contain values less than 1.");
    }

    void validateSubscriptInBounds(const Uint i, const Uint j, const Uint ni, const Uint nj)
    {
        if (i >= ni || j >= nj)
            throw std::runtime_error("Subscript is out of bounds.");
    }

    void validateSubscriptInBounds(const Uint i, const Uint j, const Uint k, const Uint ni, const Uint nj, const Uint nk)
    {
        if (i >= ni || j >= nj || k >= nk)
            throw std::runtime_error("Subscript is out of bounds.");
    }

} // namespace mt

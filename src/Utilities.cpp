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

#include <cassert>

mt::Uint mt::sub2idx(const mt::Uint i, const mt::Uint j, const mt::Uint ni, const mt::Uint nj)
{
    assert(i < ni);
    assert(j < nj);
    return i * nj + j;
}

mt::Uint mt::sub2idx(const mt::Uint i, const mt::Uint j, const mt::Uint k, const mt::Uint ni, const mt::Uint nj, const mt::Uint nk)
{
    assert(i < ni);
    assert(j < nj);
    assert(k < nk);
    return i * nj * nk + j * nk + k;
}

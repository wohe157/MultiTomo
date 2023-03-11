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

#include <array>
#include <cassert>

std::array<mt::Float, 3> mt::VolumeGeometry::Position(const mt::Uint ix, const mt::Uint iy, const mt::Uint iz) const
{
    assert(ix < Nx); // these automatically check that Nx, Ny, and Nz are greater than 0
    assert(iy < Ny);
    assert(iz < Nz);
    return {
        Cx + Dx * ((mt::Float)ix - (mt::Float)(Nx-1)/2.0f),
        Cy + Dy * ((mt::Float)iy - (mt::Float)(Ny-1)/2.0f),
        Cz + Dz * ((mt::Float)iz - (mt::Float)(Nz-1)/2.0f)
    };
}

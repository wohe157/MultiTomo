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
#include <stdexcept>

namespace mt
{

    VolumeGeometry::VolumeGeometry(
        const Uint nx, const Uint ny, const Uint nz,
        const Float dx, const Float dy, const Float dz,
        const Float cx, const Float cy, const Float cz
    )
        : Nx(nx), Ny(ny), Nz(nz), Dx(dx), Dy(dy), Dz(dz), Cx(cx), Cy(cy), Cz(cz)
    {
        validateShapeNonzero(Nx, Ny, Nz);
    }

    std::array<Float, 3> VolumeGeometry::Position(const Uint ix, const Uint iy, const Uint iz) const
    {
        validateShapeNonzero(Nx, Ny, Nz);
        validateSubscriptInBounds(ix, iy, iz, Nx, Ny, Nz);

        return {
            Cx + Dx * ((Float)ix - (Float)(Nx - 1) / 2.0f),
            Cy + Dy * ((Float)iy - (Float)(Ny - 1) / 2.0f),
            Cz + Dz * ((Float)iz - (Float)(Nz - 1) / 2.0f)
        };
    }

} // namespace mt

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
#include <cmath>
#include <cassert>
#include <stdexcept>

namespace mt
{

    DetectorGeometry::DetectorGeometry(
        const Uint nx, const Uint ny,
        const Float dx, const Float dy,
        const Float cx, const Float cy, const Float cz,
        const std::variant<ParallelBeamCfg, ConeBeamCfg, VectorBeamCfg> beam_cfg
    )
        : Nx(nx), Ny(ny), Dx(dx), Dy(dy), Cx(cx), Cy(cy), Cz(cz), BeamCfg(beam_cfg)
    {
        validateShapeNonzero(nx, ny);
    }


    std::array<Float, 3> DetectorGeometry::Position(const Uint ix, const Uint iy) const
    {
        validateShapeNonzero(Nx, Ny);
        validateSubscriptInBounds(ix, iy, Nx, Ny);

        return {
            Cx + Dx * ((Float)ix - (Float)(Nx - 1) / 2.0f),
            Cy + Dy * ((Float)iy - (Float)(Ny - 1) / 2.0f),
            Cz
        };
    }

    inline std::array<Float, 3> DetectorGeometry::Ray(const Uint ix, const Uint iy) const
    {
        validateShapeNonzero(Nx, Ny);
        validateSubscriptInBounds(ix, iy, Nx, Ny);

        if (std::get_if<ParallelBeamCfg>(&BeamCfg)) {
            return { 0.0f, 0.0f, 1.0f };
        }
        else if (const ConeBeamCfg* cone_beam_cfg = std::get_if<ConeBeamCfg>(&BeamCfg)) {
            std::array<Float, 3> pos = Position(ix, iy);
            Float vx = pos[0] - cone_beam_cfg->Sx;
            Float vy = pos[1] - cone_beam_cfg->Sy;
            Float vz = pos[2] - cone_beam_cfg->Sz;
            Float norm = std::sqrt(vx * vx + vy * vy + vz * vz);
            return { vx / norm, vy / norm, vz / norm };
        }
        else if (const VectorBeamCfg* vector_beam_cfg = std::get_if<VectorBeamCfg>(&BeamCfg)) {
            Uint idx = sub2idx(iy, ix, Ny, Nx);
            Float vx = vector_beam_cfg->Vx.at(idx); // By using "at()", we implicitly check that there are enough elements in the vectors
            Float vy = vector_beam_cfg->Vy.at(idx);
            Float vz = vector_beam_cfg->Vz.at(idx);
            Float norm = std::sqrt(vx * vx + vy * vy + vz * vz);
            return { vx / norm, vy / norm, vz / norm };
        }
        else {
            throw std::runtime_error("Invalid beam type.");
        }
    }

} // namespace mt

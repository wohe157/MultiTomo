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

std::array<mt::Float, 3> mt::DetectorGeometry::Position(const mt::Uint ix, const mt::Uint iy) const
{
    assert(ix < Nx);
    assert(iy < Ny);

    return {
        Cx + Dx * ((mt::Float)ix - (mt::Float)(Nx-1) / 2.0f),
        Cy + Dy * ((mt::Float)iy - (mt::Float)(Ny-1) / 2.0f),
        Cz
    };
}

inline std::array<mt::Float, 3> mt::DetectorGeometry::Ray(const mt::Uint ix, const mt::Uint iy) const
{
    assert(ix < Nx);
    assert(iy < Ny);

    if (std::get_if<mt::ParallelBeamCfg>(&BeamCfg)) {
        return { 0.0f, 0.0f, 1.0f };
    }
    else if (const mt::ConeBeamCfg* cone_beam_cfg = std::get_if<mt::ConeBeamCfg>(&BeamCfg)) {
        std::array<mt::Float, 3> pos = Position(ix, iy);
        mt::Float vx = pos[0] - cone_beam_cfg->Sx;
        mt::Float vy = pos[1] - cone_beam_cfg->Sy;
        mt::Float vz = pos[2] - cone_beam_cfg->Sz;
        mt::Float norm = std::sqrt(vx * vx + vy * vy + vz * vz);
        return { vx / norm, vy / norm, vz / norm };
    }
    else if (const mt::VectorBeamCfg* vector_beam_cfg = std::get_if<mt::VectorBeamCfg>(&BeamCfg)) {
        mt::Uint idx = mt::sub2idx(iy, ix, Ny, Nx);
        mt::Float vx = vector_beam_cfg->Vx.at(idx); // By using "at()", we implicitly check that there are enough elements in the vectors
        mt::Float vy = vector_beam_cfg->Vy.at(idx);
        mt::Float vz = vector_beam_cfg->Vz.at(idx);
        mt::Float norm = std::sqrt(vx * vx + vy * vy + vz * vz);
        return { vx / norm, vy / norm, vz / norm };
    }
    else {
        throw std::runtime_error("Invalid beam type.");
    }
}

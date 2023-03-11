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
#ifndef MULTITOMO_MULTITOMO_HPP
#define MULTITOMO_MULTITOMO_HPP

#include <array>
#include <vector>
#include <variant>

namespace mt
{
    // These using statements are used such that the exact types can easily be
    // changed later on if necessary. E.g., Float can either be defined as float
    // or as double depending on the best choice for optimization.
    using Uint = unsigned int;
    using Float = float;

    struct ParallelBeamCfg
    {
    };

    struct ConeBeamCfg
    {
        // Position of the source w.r.t. the detectorcenter. A typical cone
        // beam detector is represented by Sx=0, Sy=0, Sz<0.
        Float Sx, Sy, Sz;
    };

    struct VectorBeamCfg
    {
        // x-, y-, and z-components of the vectors indicating the normals of the
        // beams for each detector pixel. A beam orthogonal to the detector (as
        // for a parallel beam geometry) is given by Vx=0, Vy=0, Vz=1. The
        // vector elements are stored in linear arrays of type std::vector using
        // row-major indexing (see also mt::sub2idx). Here, the rows of the
        // detector are along the y-axis and the columns are along the x-axis.
        // In other words, the vector elements for pixel (ix,iy) are stored in
        // the index retrieved by mt::sub2idx(iy, ix, ny, nx).
        std::vector<Float> Vx, Vy, Vz;
    };

    // ====================================================================== //
    //                             VolumeGeometry                             //
    // ====================================================================== //
    struct VolumeGeometry
    {
        Uint Nx, Ny, Nz;    // Number of voxels
        Float Dx, Dy, Dz;   // Voxel spacings
        Float Cx, Cy, Cz;   // Center of the volume

        // Returns the number of voxels in the volume
        Uint Size() const { return Nx * Ny * Nz; };

        // Returns the (x,y,z) position of a given voxel
        std::array<Float, 3> Position(const Uint ix, const Uint iy, const Uint iz) const;
    };

    // ====================================================================== //
    //                            DetectorGeometry                            //
    // ====================================================================== //
    struct DetectorGeometry
    {
        Uint Nx, Ny;        // Number of pixels
        Float Dx, Dy;       // Pixel spacings
        Float Cx, Cy, Cz;   // Center of the detector (Cz specifies offset along the normal of the detector plane)
        std::variant<ParallelBeamCfg, ConeBeamCfg, VectorBeamCfg> BeamCfg;

        // Returns the number of pixels in the detector
        Uint Size() const { return Nx * Ny; }

        // Returns the (x,y,z) position of a given pixel in the detector
        std::array<Float, 3> Position(const Uint ix, const Uint iy) const;

        // Returns the (x,y,z) normal vector of the ray through a given pixel
        std::array<Float, 3> Ray(const Uint ix, const Uint iy) const;
    };

    // ====================================================================== //
    //                              DetectorPath                              //
    // ====================================================================== //
    struct DetectorPath
    {
        std::vector<Float> Px, Py, Pz;  // Position at each step
        std::vector<Float> Azimuth;     // Azimuthal angle w.r.t. y-axis in radians of the detector viewing direction at each step
        std::vector<Float> Elevation;   // Elevation angle w.r.t. xy-plane in radians of the detector viewing direction at each step
        std::vector<Float> Tilt;        // Tilt angle in radians of the detector around its viewing direction at each step

        // TODO method to return transformation matrix
        //      How to represent matrix?
        //      Probably best to use boost.Geometry
    };

    // ====================================================================== //
    //                               Utilities                                //
    // ====================================================================== //
    Uint sub2idx(const Uint i, const Uint j, const Uint ni, const Uint nj);
    Uint sub2idx(const Uint i, const Uint j, const Uint k, const Uint ni, const Uint nj, const Uint nk);

} // namespace mt

#endif //MULTITOMO_MULTITOMO_HPP

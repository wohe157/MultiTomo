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
#include "catch.hpp"
#include "multitomo.hpp"

TEST_CASE("VolumeGeometry can be constructed", "[VolumeGeometry]")
{
	mt::VolumeGeometry vol(2, 2, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	REQUIRE(vol.Nx == 2);
	REQUIRE(vol.Ny == 2);
	REQUIRE(vol.Nz == 2);
	REQUIRE(vol.Dx == 1.0f);
	REQUIRE(vol.Dy == 1.0f);
	REQUIRE(vol.Dz == 1.0f);
	REQUIRE(vol.Cx == 0.0f);
	REQUIRE(vol.Cy == 0.0f);
	REQUIRE(vol.Cz == 0.0f);
}

TEST_CASE("VolumeGeometry cannot be constructed with invalid shape", "[VolumeGeometry]")
{
	REQUIRE_THROWS(mt::VolumeGeometry(2, 2, 0, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	REQUIRE_THROWS(mt::VolumeGeometry(2, 0, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	REQUIRE_THROWS(mt::VolumeGeometry(0, 2, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f));
}

TEST_CASE("VolumeGeometry's size can be calculated", "[VolumeGeometry]")
{
	mt::VolumeGeometry vol1(2, 2, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	REQUIRE(vol1.Size() == 8);

	mt::VolumeGeometry vol2(1, 2, 3, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	REQUIRE(vol2.Size() == 6);
}

TEST_CASE("Voxel positions in VolumeGeometry can be calculated", "[VolumeGeometry]")
{
	mt::VolumeGeometry vol1(2, 2, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	auto pos1a = vol1.Position(0, 0, 0);
	REQUIRE(pos1a[0] == -0.5f);
	REQUIRE(pos1a[1] == -0.5f);
	REQUIRE(pos1a[2] == -0.5f);

	auto pos1b = vol1.Position(0, 1, 1);
	REQUIRE(pos1b[0] == -0.5f);
	REQUIRE(pos1b[1] ==  0.5f);
	REQUIRE(pos1b[2] ==  0.5f);

	REQUIRE_THROWS(vol1.Position(0, 0, 2));

	mt::VolumeGeometry vol2(1, 2, 3, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f);

	auto pos2a = vol2.Position(0, 0, 0);
	REQUIRE(pos2a[0] ==  0.0f);
	REQUIRE(pos2a[1] ==  0.5f);
	REQUIRE(pos2a[2] == -0.5f);

	auto pos2b = vol2.Position(0, 1, 1);
	REQUIRE(pos2b[0] == 0.0f);
	REQUIRE(pos2b[1] == 1.5f);
	REQUIRE(pos2b[2] == 0.0f);
}

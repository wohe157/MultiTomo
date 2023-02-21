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
#include "mt/pch.hpp"
#ifndef MT_DATA_HPP
#define MT_DATA_HPP

#include "mt/definitions.hpp"

namespace mt
{

	class Data
	{
	private:
		const Size m_Size;
		std::vector<Float> m_Data;

	public:
		Data(const Size size, const Float value = 0.0f);
		Data(const Data& other);

		const Data& operator=(const Data& other);

		inline Size size() const { return m_Size; }

		Float get(const Size idx) const;

		const Data& set(const Size idx, const Float value);
	};

} // namespace mt

#endif // MT_DATA_HPP

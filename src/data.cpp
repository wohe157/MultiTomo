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
#include "mt/data.hpp"

#include "mt/exceptions.hpp"

mt::Data::Data(const mt::Size size, const mt::Float value)
	: m_Size(size), m_Data(size, value)
{
}

mt::Data::Data(const mt::Data& other)
	: m_Size(other.m_Size), m_Data(other.m_Data)
{
}

const mt::Data& mt::Data::operator=(const mt::Data& other)
{
	if (other.m_Size != m_Size)
		throw mt::Exception(std::format("Mismatching sizes: {} != {}.", other.m_Size, m_Size));

	m_Data = other.m_Data;

	return *this;
}

mt::Float mt::Data::get(const mt::Size idx) const
{
	if (idx >= m_Size)
		throw mt::Exception(std::format("Index out of range: {} >= {}.", idx, m_Size));

	return m_Data.at(idx);
}

const mt::Data& mt::Data::set(const mt::Size idx, const mt::Float value)
{
	if (idx >= m_Size)
		throw mt::Exception(std::format("Index out of range: {} >= {}.", idx, m_Size));

	m_Data.at(idx) = value;

	return *this;
}

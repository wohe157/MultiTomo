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
#include "mt/exceptions.hpp"

mt::Exception::Exception(const std::string& msg)
	: m_Message(msg)
{
}

mt::Exception::Exception(std::string&& msg)
	: m_Message(std::move(msg))
{
}

mt::Exception::~Exception() throw()
{
}

const char* mt::Exception::what() const throw()
{
	return m_Message.c_str();
}

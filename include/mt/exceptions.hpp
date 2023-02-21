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
#ifndef MT_EXCEPTIONS_HPP
#define MT_EXCEPTIONS_HPP

namespace mt {

	class Exception : public std::exception
	{
	private:
		const std::string m_Message;

	public:
		Exception(const std::string& msg);
		Exception(std::string&& msg);
	
		virtual ~Exception() throw();

		const char* what() const throw();
	};

} // namespace mt

#endif // MT_EXCEPTIONS_HPP

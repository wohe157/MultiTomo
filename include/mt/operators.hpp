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
#ifndef MT_OPERATORS_HPP
#define MT_OPERATORS_HPP

#include "mt/definitions.hpp"
#include "mt/data.hpp"

namespace mt
{
	// Values are stored according to the compressed sparse row (CSR) method
	class Operator
	{
	private:
		const Shape2d m_Shape;
		std::vector<Size> m_RowOffset; // element i is the start position of the elements in row i
		std::vector<Size> m_ColIdx; // holds the column indices for each nonzero element
		std::vector<Float> m_Values; // holds the nonzero values in the sparse matrix

	public:
		Operator(const Shape2d shape);

		inline Size rows() const { return m_Shape.rows; }

		inline Size cols() const { return m_Shape.cols; }

		inline Shape2d shape() const { return m_Shape; }

		Float get(const Subscript2d sub) const;

		const Operator& set(const Subscript2d sub, const Float value);

		const Operator transpose() const;

		Data operator*(const Data& rhs) const;
		Operator operator*(const Operator& rhs) const;

	private:
		const Operator& _remove(const Size idx, const mt::Subscript2d sub);

		const Operator& _insert(const Size idx, const mt::Subscript2d sub, const Float value);
	};

} // namespace mt

#endif // MT_OPERATORS_HPP

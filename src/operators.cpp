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
#include "mt/operators.hpp"

#include "mt/exceptions.hpp"

mt::Operator::Operator(const mt::Shape2d shape)
	: m_Shape(shape), m_RowOffset(shape.rows + 1, 0), m_ColIdx(), m_Values()
{
}

mt::Float mt::Operator::get(const mt::Subscript2d sub) const
{
	if (sub.i >= rows() || sub.j >= cols())
		throw mt::Exception(std::format("Subscript ({},{}) is out of bounds ({},{}).", sub.i, sub.j, rows(), cols()));

	for (mt::Size idx = m_RowOffset.at(sub.i); idx < m_RowOffset.at(sub.i + 1); idx++) {
		if (m_ColIdx.at(idx) == sub.j) {
			return m_Values.at(idx);
		}
	}
	
	return 0.0f;
}

const mt::Operator& mt::Operator::set(const mt::Subscript2d sub, const mt::Float value)
{
	if (sub.i >= rows() || sub.j >= cols())
		throw mt::Exception(std::format("Subscript ({},{}) is out of bounds ({},{}).", sub.i, sub.j, rows(), cols()));

	// Check if the element at sub was already nonzero, and if that is the case,
	// replace it by value or remove it from the list if value == 0.
	mt::Size idx = m_RowOffset.at(sub.i);
	for (; idx < m_RowOffset.at(sub.i + 1); idx++) {
		if (m_ColIdx.at(idx) != sub.j)
			continue;

		if (value == 0.0f)
			_remove(idx, sub);
		else
			m_Values.at(idx) = value;

		return *this;
	}

	// Insert the element at idx if it is not 0.
	if (value != 0.0f)
		_insert(idx, sub, value);

	return *this;
}

const mt::Operator mt::Operator::transpose() const
{
	mt::Operator result({ cols(), rows() });
	result.m_ColIdx.reserve(m_ColIdx.size());
	result.m_Values.reserve(m_Values.size());

	std::vector<mt::Size> nextElementOffset(m_RowOffset);
	for (mt::Size i = 0; i < cols(); i++) {
		// Each row of the new operator is being built subsequently: the loop
		// below goes over all rows in the original operator and checks if it
		// contains a value at the column with index `i` (which will be the new
		// row). To do this efficiently, the variable `nextElementOffset` keeps
		// track of the offset of the next nonzero element in each row of the
		// original operator. This is done such that we don't need to loop from
		// the beginning of each row every time again.
		for (mt::Size j = 0; j < rows(); j++) {
			mt::Size offset = nextElementOffset.at(j);
			if (offset < m_RowOffset.at(j + 1) && i == m_ColIdx.at(offset)) {
				result.set({ i, j }, m_Values.at(offset));
				nextElementOffset.at(j)++;
			}
		}
	}

	return result;
}

mt::Data mt::Operator::operator*(const mt::Data& rhs) const
{
	if (cols() != rhs.size())
		throw mt::Exception(std::format("Incompatible shape for matrix multiplication: ({},{})*({},1).", rows(), cols(), rhs.size()));

	mt::Data result(rows(), 0.0f);
	for (mt::Size i = 0; i < rows(); i++) {
		mt::Float value = 0.0f;
		for (mt::Size ii = m_RowOffset.at(i); ii < m_RowOffset.at(i + 1); ii++)
			value += m_Values.at(ii) * rhs.get(m_ColIdx.at(ii));
		result.set(i, value);
	}

	return result;
}

mt::Operator mt::Operator::operator*(const mt::Operator& rhs) const
{
	if (cols() != rhs.rows())
		throw mt::Exception(std::format("Incompatible shape for matrix multiplication: ({},{})*({},{}).", rows(), cols(), rhs.rows(), rhs.cols()));

	mt::Operator result({ rows(), rhs.cols() });
	for (mt::Size i = 0; i < rows(); i++) {
		for (mt::Size j = 0; j < rhs.cols(); j++) {
			mt::Float value = 0.0f;
			for (mt::Size ii = m_RowOffset.at(i); ii < m_RowOffset.at(i + 1); ii++)
				value += m_Values.at(ii) * rhs.get({ m_ColIdx.at(ii), j });
			result.set({ i, j }, value);
		}
	}

	return result;
}

const mt::Operator& mt::Operator::_remove(const mt::Size idx, const mt::Subscript2d sub)
{
	m_Values.erase(m_Values.begin() + idx);
	m_ColIdx.erase(m_ColIdx.begin() + idx);

	for (mt::Size i = sub.i + 1; i < m_RowOffset.size(); i++)
		m_RowOffset.at(i) -= 1;

	return *this;
}

const mt::Operator& mt::Operator::_insert(const mt::Size idx, const mt::Subscript2d sub, const mt::Float value)
{
	m_Values.insert(m_Values.begin() + idx, value);
	m_ColIdx.insert(m_ColIdx.begin() + idx, sub.j);

	for (mt::Size i = sub.i + 1; i < m_RowOffset.size(); i++)
		m_RowOffset.at(i) += 1;

	return *this;
}

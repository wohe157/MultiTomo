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

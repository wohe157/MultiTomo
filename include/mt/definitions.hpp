#include "mt/pch.hpp"
#ifndef MT_DEFINITIONS_HPP
#define MT_DEFINITIONS_HPP

namespace mt
{

	typedef float Float;
	typedef size_t Size;

	struct Shape2d
	{
		Size rows;
		Size cols;

		bool operator==(const Shape2d& rhs) const;
	};

	struct Shape3d
	{
		Size rows;
		Size cols;
		Size slices;

		bool operator==(const Shape3d& rhs) const;
	};

	struct Subscript2d
	{
		Size i;
		Size j;

		bool operator==(const Subscript2d& rhs) const;
	};

	struct Subscript3d
	{
		Size i;
		Size j;
		Size k;

		bool operator==(const Subscript3d& rhs) const;
	};

} // namespace mt

#endif // MT_DEFINITIONS_HPP

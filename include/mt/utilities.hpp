#include "mt/pch.hpp"
#ifndef MT_UTILITIES_HPP
#define MT_UTILITIES_HPP

#include "mt/definitions.hpp"

namespace mt
{

	Size sub2idx(const Subscript2d sub, const Shape2d shape);
	Size sub2idx(const Subscript3d sub, const Shape3d shape);

	Subscript2d idx2sub(const Size idx, const Shape2d shape);
	Subscript3d idx2sub(const Size idx, const Shape3d shape);

} // namespace mt

#endif // MT_UTILITIES_HPP

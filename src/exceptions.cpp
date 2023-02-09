#include "mt/exceptions.hpp"

mt::ShapeMismatchError::ShapeMismatchError(const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices)
	: mt::Exception(std::format("Invalid shape: ({},{},{}).", rows, cols, slices))
{
}

mt::ShapeMismatchError::ShapeMismatchError(const MT_SIZE rows1, const MT_SIZE cols1, const MT_SIZE slices1, const MT_SIZE rows2, const MT_SIZE cols2, const MT_SIZE slices2)
	: Exception(std::format("Mismatching shapes: ({},{},{}) != ({},{},{}).", rows1, cols1, slices1, rows2, cols2, slices2))
{
}

mt::ShapeMismatchError::ShapeMismatchError(const MT_SIZE size, const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices)
	: Exception(std::format("Size does not match shape: {} != {}*{}*{}.", size, rows, cols, slices))
{
}

mt::ShapeMismatchError::ShapeMismatchError(const MT_SIZE size1, const MT_SIZE size2)
	: Exception(std::format("Mismatching sizes: {} != {}.", size1, size2))
{
}

mt::IndexError::IndexError(const MT_SIZE idx, const MT_SIZE size)
	: mt::Exception(std::format("Index out of bounds: tried to access element {} in object with size {}.", idx, size))
{
}

mt::IndexError::IndexError(const MT_SIZE row, const MT_SIZE col, const MT_SIZE slice, const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices)
	: mt::Exception(std::format("Subscript out of bounds: tried to access element ({},{},{}) in object with shape ({},{},{}).", row, col, slice, rows, cols, slices))
{
}

mt::DivideByZeroError::DivideByZeroError()
	: mt::Exception("Can't divide by zero.")
{
}

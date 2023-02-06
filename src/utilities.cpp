#include "mt/utilities.hpp"

#include "mt/exceptions.hpp"

MT_SIZE mt::sub2idx(const MT_SIZE row, const MT_SIZE col, const MT_SIZE slice, const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices)
{
	if (!mt::isValidIdx(row, rows) || !mt::isValidIdx(col, cols) || !mt::isValidIdx(slice, slices))
		throw mt::IndexError(row, col, slice, rows, cols, slices);

	// row-major indexing
	return row * cols * slices + col * slices + slice;
}

bool mt::isValidIdx(const MT_SIZE idx, const MT_SIZE size)
{
	return idx < size && idx >= 0;
}

bool mt::isValidSize(const MT_SIZE size)
{
	return size > 0;
}

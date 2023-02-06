#pragma once

#include "mt/definitions.hpp"

namespace mt
{

MT_SIZE sub2idx(const MT_SIZE row, const MT_SIZE col, const MT_SIZE slice, const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices);

bool isValidIdx(const MT_SIZE idx, const MT_SIZE size);

bool isValidSize(const MT_SIZE size);

} // namespace mt

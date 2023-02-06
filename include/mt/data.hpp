#pragma once

#include <array>
#include <vector>

#include "mt/definitions.hpp"

namespace mt {

class Data
{
private:
	const MT_SIZE m_Rows;
	const MT_SIZE m_Cols;
	const MT_SIZE m_Slices;
	std::vector<MT_FLOAT> m_Data;

public:
	Data(const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices);
	Data(const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices, MT_FLOAT value);
	Data(const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices, std::vector<MT_FLOAT> data);
	Data(const Data& other);
	
	const Data& operator=(const Data& other);

	inline MT_SIZE rows() const { return m_Rows; }

	inline MT_SIZE cols() const { return m_Cols; }

	inline MT_SIZE slices() const { return m_Slices; }

	inline MT_SIZE size() const { return m_Rows * m_Cols * m_Slices; }
	
	MT_FLOAT get(const MT_SIZE idx) const;
	MT_FLOAT get(const MT_SIZE row, const MT_SIZE col, const MT_SIZE slice) const;

	void set(const MT_SIZE idx, const MT_FLOAT value);
	void set(const MT_SIZE row, const MT_SIZE col, const MT_SIZE slice, const MT_FLOAT value);
};

} // namespace mt

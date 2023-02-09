#include "mt/data.hpp"

#include <stdexcept>
#include <format>
#include <algorithm>

#include "mt/exceptions.hpp"
#include "mt/utilities.hpp"

mt::Data::Data(const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices)
	: m_Rows(rows), m_Cols(cols), m_Slices(slices), m_Data(std::vector<MT_FLOAT>(rows*cols*slices, 0.0f))
{
	if (!mt::isValidSize(size()))
		throw mt::ShapeMismatchError(rows, cols, slices);
}

mt::Data::Data(const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices, MT_FLOAT value)
	: m_Rows(rows), m_Cols(cols), m_Slices(slices), m_Data(std::vector<MT_FLOAT>(rows* cols* slices, value))
{
	if (!mt::isValidSize(size()))
		throw mt::ShapeMismatchError(rows, cols, slices);
}

mt::Data::Data(const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices, std::vector<MT_FLOAT> data)
	: m_Rows(rows), m_Cols(cols), m_Slices(slices), m_Data(std::vector<MT_FLOAT>(data))
{
	if (!mt::isValidSize(size()))
		throw mt::ShapeMismatchError(rows, cols, slices);
	if (size() != data.size())
		throw mt::ShapeMismatchError(data.size(), rows, cols, slices);
}

mt::Data::Data(const Data& other)
	: m_Rows(other.m_Rows), m_Cols(other.m_Cols), m_Slices(other.m_Slices), m_Data(other.m_Data)
{
}

const mt::Data& mt::Data::operator=(const Data& other)
{
	if (m_Rows != other.m_Rows || m_Cols != other.m_Cols || m_Slices != other.m_Slices)
		throw mt::ShapeMismatchError(other.m_Rows, other.m_Cols, other.m_Slices, m_Rows, m_Cols, m_Slices);
	
	m_Data = other.m_Data;
	return *this;
}

MT_FLOAT mt::Data::get(const MT_SIZE idx) const
{
	if (!mt::isValidIdx(idx, size()))
		throw mt::IndexError(idx, size());

	return m_Data.at(idx);
}

MT_FLOAT mt::Data::get(const MT_SIZE row, const MT_SIZE col, const MT_SIZE slice) const
{
	if (!mt::isValidIdx(row, m_Rows) || !mt::isValidIdx(col, m_Cols) || !mt::isValidIdx(slice, m_Slices))
		throw mt::IndexError(row, col, slice, m_Rows, m_Cols, m_Slices);

	return m_Data.at(mt::sub2idx(row, col, slice, m_Rows, m_Cols, m_Slices));
}

void mt::Data::set(const MT_SIZE idx, const MT_FLOAT value)
{
	if (!mt::isValidIdx(idx, size()))
		throw mt::IndexError(idx, size());

	m_Data.at(idx) = value;
}

void mt::Data::set(const MT_SIZE row, const MT_SIZE col, const MT_SIZE slice, const MT_FLOAT value)
{
	if (!mt::isValidIdx(row, m_Rows) || !mt::isValidIdx(col, m_Cols) || !mt::isValidIdx(slice, m_Slices))
		throw mt::IndexError(row, col, slice, m_Rows, m_Cols, m_Slices);

	m_Data.at(mt::sub2idx(row, col, slice, m_Rows, m_Cols, m_Slices)) = value;
}

void mt::Data::operator+=(const MT_FLOAT value)
{
	transform([value](const MT_FLOAT x) { return x + value; });
}


void mt::Data::operator+=(const Data& other)
{
	if (m_Rows != other.m_Rows || m_Cols != other.m_Cols || m_Slices != other.m_Slices)
		throw mt::ShapeMismatchError(other.m_Rows, other.m_Cols, other.m_Slices, m_Rows, m_Cols, m_Slices);

	transform(other, [](const MT_FLOAT x1, const MT_FLOAT x2) { return x1 + x2; });
}

void mt::Data::operator-=(const MT_FLOAT value)
{
	transform([value](const MT_FLOAT x) { return x - value; });
}


void mt::Data::operator-=(const Data& other)
{
	if (m_Rows != other.m_Rows || m_Cols != other.m_Cols || m_Slices != other.m_Slices)
		throw mt::ShapeMismatchError(other.m_Rows, other.m_Cols, other.m_Slices, m_Rows, m_Cols, m_Slices);

	transform(other, [](const MT_FLOAT x1, const MT_FLOAT x2) { return x1 - x2; });
}

void mt::Data::operator*=(const MT_FLOAT value)
{
	transform([value](const MT_FLOAT x) { return x * value; });
}


void mt::Data::operator*=(const Data& other)
{
	if (m_Rows != other.m_Rows || m_Cols != other.m_Cols || m_Slices != other.m_Slices)
		throw mt::ShapeMismatchError(other.m_Rows, other.m_Cols, other.m_Slices, m_Rows, m_Cols, m_Slices);

	transform(other, [](const MT_FLOAT x1, const MT_FLOAT x2) { return x1 * x2; });
}

void mt::Data::operator/=(const MT_FLOAT value)
{
	if (value == 0)
		throw mt::DivideByZeroError();

	transform([value](const MT_FLOAT x) { return x / value; });
}


void mt::Data::operator/=(const Data& other)
{
	if (m_Rows != other.m_Rows || m_Cols != other.m_Cols || m_Slices != other.m_Slices)
		throw mt::ShapeMismatchError(other.m_Rows, other.m_Cols, other.m_Slices, m_Rows, m_Cols, m_Slices);
	for (const MT_FLOAT value : other.m_Data) {
		if (value == 0)
			throw mt::DivideByZeroError();
	}

	transform(other, [](const MT_FLOAT x1, const MT_FLOAT x2) { return x1 / x2; });
}

void mt::Data::transform(std::function<MT_FLOAT(const MT_FLOAT)> operation)
{
	std::transform(m_Data.begin(), m_Data.end(), m_Data.begin(), operation);
}

void mt::Data::transform(const Data& other, std::function<MT_FLOAT(const MT_FLOAT, const MT_FLOAT)> operation)
{
	std::transform(m_Data.begin(), m_Data.end(), other.m_Data.begin(), m_Data.begin(), operation);
}

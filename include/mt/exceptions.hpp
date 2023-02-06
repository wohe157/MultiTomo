#pragma once

#include <string>
#include <format>
#include <exception>

#include "mt/definitions.hpp"

namespace mt {

class Exception : public std::exception
{
private:
	const std::string m_Message;

public:
	Exception(const std::string& msg) : m_Message(msg) {}
	Exception(std::string&& msg) : m_Message(std::move(msg)) {}
	
	virtual ~Exception() throw() {}

	const char* what() const throw() { return m_Message.c_str(); }
};

class ShapeMismatchError : public Exception
{
public:
	ShapeMismatchError(const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices);

	ShapeMismatchError(const MT_SIZE rows1, const MT_SIZE cols1, const MT_SIZE slices1, const MT_SIZE rows2, const MT_SIZE cols2, const MT_SIZE slices2);

	ShapeMismatchError(const MT_SIZE size, const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices);

	ShapeMismatchError(const MT_SIZE size1, const MT_SIZE size2);
};

class IndexError : public Exception
{
public:
	IndexError(const MT_SIZE idx, const MT_SIZE size);

	IndexError(const MT_SIZE row, const MT_SIZE col, const MT_SIZE slice, const MT_SIZE rows, const MT_SIZE cols, const MT_SIZE slices);
};

} // namespace mt

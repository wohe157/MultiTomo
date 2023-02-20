#include "mt/exceptions.hpp"

mt::Exception::Exception(const std::string& msg)
	: m_Message(msg)
{
}

mt::Exception::Exception(std::string&& msg)
	: m_Message(std::move(msg))
{
}

mt::Exception::~Exception() throw()
{
}

const char* mt::Exception::what() const throw()
{
	return m_Message.c_str();
}

#include "mt/pch.hpp"
#ifndef MT_EXCEPTIONS_HPP
#define MT_EXCEPTIONS_HPP

namespace mt {

	class Exception : public std::exception
	{
	private:
		const std::string m_Message;

	public:
		Exception(const std::string& msg);
		Exception(std::string&& msg);
	
		virtual ~Exception() throw();

		const char* what() const throw();
	};

} // namespace mt

#endif // MT_EXCEPTIONS_HPP

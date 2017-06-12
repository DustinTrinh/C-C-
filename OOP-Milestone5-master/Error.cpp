#define _CRT_SECURE_NO_WARNINGS 

#include "Error.h"

namespace ict{
	Error::Error()
	{
		m_message = nullptr;
	}
	Error::Error(const char* errorMessage)
	{
		m_message = nullptr;
		message(errorMessage);
	}
	 Error::~Error()
	{
		delete[] m_message;
	}
	void Error::clear()
	{
		delete[] m_message;
		m_message = nullptr;
	}
	void Error::operator=(const char* errorMessage)
	{
		clear();
		
		m_message = new char[strlen(errorMessage) + 1];
		strcpy(m_message, errorMessage);
	}
	bool Error::isClear()const
	{
		if (m_message == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Error::message(const char* value)
	{
		clear();
		m_message = new char[strlen(value) + 1];
		strcpy(m_message, value);
	}
	Error::operator const char*() const
	{
		return m_message;
	}
	Error::operator bool()const
	{
		if (m_message == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	std::ostream & operator<<(std::ostream & os, const Error & error)
	{
		if (error.isClear() == false)
		{
			os << error.operator const char* ();
		}
		else
		{

		}
		return os;
	}
}
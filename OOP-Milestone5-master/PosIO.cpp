#include "PosIO.h"
#include <iostream>
#include <fstream>
#include <cstring>
namespace ict
{

	std::fstream & PosIO::save(std::fstream & file) const
	{
		return file;
	}

	std::fstream & PosIO::load(std::fstream & file)
	{
		return file;
	}

	std::ostream & PosIO::write(std::ostream & os, bool linear) const
	{
		return os;
	}

	std::istream & PosIO::read(std::istream & is)
	{
		return is;
	}

}

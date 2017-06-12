#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>
#include "Perishable.h"
#include "NonPerishable.h"


namespace ict
{

	char Perishable::signature() const
	{
		return 'P';
	}

	std::fstream& ict::Perishable::save(std::fstream& file)const
	{
		NonPerishable::save(file);
		file << ",";
		file << m_expiry;
		file << "\n";
		return file;
	}
	std::fstream& ict::Perishable::load(std::fstream& file)
	{
		int _year;
		int _month;
		int _day;
		NonPerishable::load(file);

	//	file.ignore(1);

		file >> _year;
		file.ignore(1);

		file >> _month;
		file.ignore(1);

		file >> _day;
		file.ignore(1);

		Date temp(_year, _month, _day);
		m_expiry = temp;

		return file;
	}
	std::ostream& ict::Perishable::write(std::ostream& os, bool linear)const
	{
		NonPerishable::write(os, linear);

		if (ok() == true && linear == false)
		{
			os << "Expiry Date: " << m_expiry ;
			os << "\n";
		}
		return os;
	}
	std::istream& ict::Perishable::read(std::istream& istr)
	{
		std::cout << "Perishable ";
		NonPerishable::read(istr);

		if (istr.fail() == false)
		{
			std::cout << "Expiry date (YYYY/MM/DD): ";
			m_expiry.dateOnly(true);
			istr >> m_expiry;
			
			if (m_expiry.errCode() > 0)
			{
				istr.setstate(istr.failbit);

				if (m_expiry.errCode() == 1)
				{
					error("Invalid Date Entry");
				
				
				}
				else if (m_expiry.errCode() == 2)
				{
					error("Invalid Year in Date Entry");
					
				
				}
				else if (m_expiry.errCode() == 3)
				{
					error("Invalid Month in Date Entry");
					
				
				}
				else if (m_expiry.errCode() == 4)
				{
					error("Invalid Day in Date Entry");
					
				}
				
			}
			
		}
		return istr;
	}
	

}

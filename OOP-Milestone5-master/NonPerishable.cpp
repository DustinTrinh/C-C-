#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include "NonPerishable.h"

#include <iostream>
#include <iomanip>

namespace ict
{
	bool NonPerishable::ok() const
	{
		return m_err.isClear();
	}
	void NonPerishable::error(const char *message)
	{
		m_err.message(message);
	}
	char NonPerishable::signature()const
	{
		return 'N';
	}

	std::fstream& NonPerishable::save(std::fstream& file)const
	{
		
		file << signature() <<","<< sku()<< "," << name() << "," << price() << "," << taxed() << "," << quantity();
		if (signature() == 'N')
		{
			file << "\n";
		}
		return file;
	}
	
	std::fstream& NonPerishable::load(std::fstream& file)
	{
		char holdsku[30];
		char holdname[30];
		double holdprice;
		bool holdtaxed;
		int holdquantity;
		
		file.getline(holdsku, 30, ',');
		Item::sku(holdsku);

		file.getline(holdname, 30, ',');
		Item::name(holdname);

		file >> holdprice;
		file.ignore(1);
		Item::price(holdprice);

		file >> holdtaxed;
		file.ignore(1);
		Item::taxed(holdtaxed);

		file >> holdquantity;
		Item::quantity(holdquantity);
		file.ignore(1);

		return file;

	}
	std::ostream& NonPerishable::write(std::ostream& ostr, bool linear)const
	{
		if (ok() == false)
		{
			ostr << m_err;
			return ostr;
		}
		else if (ok() == true)
		{
			if (linear == true)
			{
				ostr << std::setw(MAX_SKU_LEN) << std::left << sku() << "|" << std::setw(20) 
					<< std::setfill(' ') << name() << "|" << std::setw(7) << std::right << price() << "| " 
					<< (taxed() == true ? 'T' : ' ') << signature() << "|" << std::right << std::setw(4) << quantity() << "|" 
					<< std::setw(9) << std::right << std::fixed << std::setprecision(2) << cost()*quantity() << "|";
			}
			else
			{
				if (taxed() == true)
				{
					ostr << "Name:\n";
					ostr << name() << std::endl;
					ostr << "Sku: " << sku() << std::endl;
					ostr << "Price: " << price() << std::endl;
					ostr << "Price after tax: " << cost() << std::endl;
					ostr << "Quantity: " << quantity() << std::endl;
					ostr << "Total Cost: " <<cost() * quantity() << std::endl;
				}
				else
				{
					ostr << "Name:\n";
					ostr << name() << std::endl;
					ostr << "Sku: " << sku() << std::endl;
					ostr << "Price: " << price() << std::endl;
					ostr << "Price after tax: " <<"N/A"<< std::endl;
					ostr << "Quantity: " << quantity() << std::endl;
					ostr << "Total Cost: " << cost() * quantity()<< std::endl;
				}
				
			}
		}
		return ostr;
	}
	
	std::istream& NonPerishable::read(std::istream& is)
	{

		

		if (is.fail() == true)
		{
			return is;
		}
		else
		{
			char holdsku[30];
			char holdname[30];
			double holdprice;
			char holdtaxed;
			int holdquantity;

			std::cout << "Item Entry:\n";
			std::cout << "Sku: ";
			is >> holdsku;
			if (is.fail() == true)
			{
				return is;
			
			}
			std::cout << "Name:\n";
			is >> holdname;
			if (is.fail() == true)
			{
				return is;
				
			}
			std::cout << "Price: ";
			is >> holdprice;
			if (is.fail() == true)
			{
				error("Invalid Price Entry");
				return is;
				
			}

			std::cout << "Taxed: ";
			is >> holdtaxed;
			if (holdtaxed != 'y' && holdtaxed != 'n' )
			{
				is.setstate(is.failbit);
				error("Invalid Taxed Entry, (y)es or (n)o");
				return is;
				
			}
			std::cout << "Quantity: ";
			is >> holdquantity;
			if (is.fail() == true)
			{
				error("Invalid Quantity Entry");
				return is;
			
			}

			sku(holdsku);
			name(holdname);
			price(holdprice);
			taxed(holdtaxed);
			quantity(holdquantity);
			m_err.clear();
	}
		
		return is;
	}
}

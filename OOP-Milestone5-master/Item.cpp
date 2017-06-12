#include "Item.h"
#define _CRT_SECURE_NO_WARNINGS  
// Lib includes
#include <iostream>
#include <string>

// inlcude Item and POS header files
#include "POS.h"
#include "Item.h"

using namespace std;
namespace ict {

	Item::Item()
	{
		strcpy(m_sku, "");
		m_name = nullptr;
		m_price = 0;
		m_taxed = false;
		m_quantity = 0;
	}

	Item::Item(char sku[], char * name, double price, bool tax)
	{
		strcpy(m_sku, sku);
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
		m_price = price;
		m_taxed = tax;

	}

	Item::~Item()
	{
		delete[] m_name;
	}

	Item::Item(const Item & I)
	{
		strcpy(m_sku, I.m_sku);
		m_price = I.m_price;
		m_quantity = I.m_quantity;
		m_taxed = I.m_taxed;

		if (I.m_name != nullptr)
		{
			m_name = new char[strlen(I.m_name) + 1];
			strcpy(m_name, I.m_name);

		}
		else
		{
			m_name = nullptr;
		}

	}

	Item & Item::operator=(const Item & I)
	{
		if (this != &I && I.isEmpty() != true)
		{
			strcpy(m_sku, I.m_sku);
			m_price = I.m_price;
			m_quantity = I.m_quantity;
			m_taxed = I.m_taxed;

			delete[] m_name;
			if (I.m_name != nullptr)
			{
				int namelength = 0;
				namelength = strlen(I.m_name);
				m_name = new char[ namelength + 1];
				strcpy(m_name, I.m_name);
			}
			else
			{
				strcpy(m_name, "");
			}
		}
		return *this;

	}

	void Item::sku(char sku[])
	{
		strcpy(m_sku, sku);
	}

	void Item::price(double price)
	{
		m_price = price;
	}

	void Item::name(char * name)
	{
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}

	void Item::taxed(bool tax)
	{
		m_taxed = tax;
	}

	void Item::quantity(int quantity)
	{
		m_quantity = quantity;
	}

	const char* Item::sku() const
	{
		return m_sku;
	}

	double Item::price() const
	{
		return m_price;
	}

	char * Item::name() const
	{
		return m_name;
	}

	bool Item::taxed() const
	{
		return m_taxed;
	}

	int Item::quantity() const
	{
		return m_quantity;
	}

	double Item::cost() const
	{
		if (m_taxed)
			return  m_price + (m_price * TAX);
		else
			return m_price;
	}

	bool Item::isEmpty() const
	{
		if (m_name == nullptr ||
			m_price == 0.0 ||
			m_quantity == 0 ||
			strcmp(m_sku, "") == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Item::operator==(const char sku[]) const
	{
		if (!strcmp(m_sku, sku))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int Item::operator+=(const int i)
	{
		m_quantity = m_quantity + i;
		return m_quantity;
	}

	int Item::operator-=(const int i)
	{
		m_quantity -= i;
		return m_quantity;
	}

	double operator+=(double & d, const Item & I)
	{
		d += I.price() * I.quantity();
		return d;

	}

	std::ostream & operator<<(std::ostream & os, const Item & d)
	{
		d.write(os, true);
		return os;
	}

	std::istream & operator >> (std::istream & is, Item & d)
	{
		d.read(is);
		return is;
	}

}
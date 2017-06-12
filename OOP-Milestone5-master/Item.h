#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__
// inlcude PosIO and POS header files
#include "POS.h"
#include "PosIO.h"

namespace ict{
  // class Item
	class Item : public PosIO
	{
	private:
		char m_sku[MAX_SKU_LEN + 1];
		char *m_name;
		double m_price;
		bool m_taxed;
		int m_quantity;

	public:
		Item();
		Item(char sku[], char *name, double price, bool tax);
		Item(const Item &other);
		Item& operator=(const Item & I);
		virtual ~Item();

		void sku(char sku[]);
		void price(double price);
		void name(char *name);
		void taxed(bool tax);
		void quantity(int quantity);

		const char *sku() const;
		double price() const;
		char *name() const;
		bool taxed() const;
		int quantity() const;
		double cost() const;

		bool isEmpty()const;

		int operator+=(const int i);
		bool operator==(const char sku[])const;
		int operator-=(const int i);

	};

  // end class Item
  // operator += 
  double operator+=(double& d, const Item& I);
  // operator << and operator >>
  std::istream & operator >> (std::istream & is, Item & d);
  std::ostream & operator<<(std::ostream & os, const Item & d);
 
}


#endif
#ifndef POSAPP_H
#define POSAPP_H
#include "Item.h"
#include <iostream>
#include <string.h>

namespace ict
{
	class PosApp
	{
	private:
		char m_filename[128];
		char m_billfname[128];
		Item* m_items[MAX_NO_ITEMS];
		int m_noOfItems;
		int menu(); // done
		
		void deallocateItems(); // done
		void loadRecs(); // done
		void saveRecs(); //done
		int searchItems(const char* sku)const; // done
		void updateQty(); // done
		void addItem(bool isPerishable); //done
		void listItems()const; // done
		void truncateBillFile(); //done
		void showBill(); //done
		void addToBill(Item& I);
		void POS(); //done

	public:
		void run(); //done
		PosApp(const char* filename, const char* billfname);//done
		
	};
}


#endif

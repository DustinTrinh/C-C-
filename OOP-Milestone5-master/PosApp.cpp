#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "PosApp.h"
#include "NonPerishable.h"
#include "Perishable.h"
#include "Item.h"
#include <fstream>
#include "PosIO.h"
#include <iomanip>

namespace ict
{
	PosApp::PosApp(const char* filename, const char* billfname)
	{
		m_noOfItems = 0;
		strncpy(m_filename, filename, 128);
		strncpy(m_billfname, billfname, 128);
		loadRecs();
	}
	int PosApp::menu()
	{
		int input = 0;
		std::cout << "The Sene-Store" << std::endl;
		std::cout << "1- List items" << std::endl;
		std::cout << "2- Add Perishable item" << std::endl;
		std::cout << "3- Add Non-Perishable item" << std::endl;
		std::cout << "4- Update item quantity" << std::endl;
		std::cout << "5- Show Item" << std::endl;
		std::cout << "6- POS" << std::endl;
		std::cout << "0- exit program" << std::endl;
		std::cout << "> ";
		std::cin >> input;
		std::cout << "\n";
		if (input >= 0 && input < 7)
		{
			return input;
		}
		else
		{
			return -1;
		}

	}
	void PosApp::deallocateItems()
	{
		for (int i = 0; i < m_noOfItems; i++)
		{
			delete m_items[i];
		}
		m_noOfItems = 0;
	}

	int PosApp::searchItems(const char* sku)const
	{

		for (int i = 0; i < m_noOfItems; i++)
		{
			if (*m_items[i] == sku)
			{
				return i;
			}
		}

		return -1;

	}
	void PosApp::updateQty()
	{
		char skuinput[5];
		int quantity;
		std::cout << "Please enter the SKU: ";
		std::cin >> skuinput;
		int index = searchItems(skuinput);
		if (index == -1)
		{
			std::cout << "Not found!";
		}
		else
		{
			m_items[index]->write(std::cout, false);
			std::cout << "\nPlease enter the number of purchased items: ";
			std::cin >> quantity;
			*m_items[index] += quantity;

			saveRecs();
		
			std::cout << "Updated!";

		}

	}
	void PosApp::loadRecs()
	{
		deallocateItems();
		m_noOfItems = 0;
		std::fstream file(m_filename, std::ios::in);
		if ((file.rdstate() & std::fstream::failbit) != 0)
		{
			file.clear();
			file.close();

			std::fstream file(m_filename, std::ios::out);
			file.close();
		}
		else
		{
			char signature;
			while (!file.get(signature).fail())
			{
				file.ignore(1);
				if (signature == 'P')
				{
					m_items[m_noOfItems] = new Perishable;
					m_items[m_noOfItems]->load(file);
					m_noOfItems += 1;
				}
				else if (signature == 'N')
				{
					m_items[m_noOfItems] = new NonPerishable;
					m_items[m_noOfItems]->load(file);
					m_noOfItems += 1;
				}

			}

			file.close();

		}

		
	}
	void PosApp::saveRecs()
	{
		std::fstream file(m_filename, std::ios::out);

		for (int i = 0; i < m_noOfItems; i++)
		{
			if (m_items[i]->quantity() > 0)
				m_items[i]->save(file);
		}

		file.close();
		loadRecs();
	}

	void PosApp::listItems() const
	{
		double sum = 0;
		std::cout << " Row | SKU   | Item Name          | Price |TX |Qty |   Total |\n";
		std::cout << "-----|-------|--------------------|-------|---|----|---------|\n";
		for (int i = 0; i < m_noOfItems; i++)
		{
			std::cout <<std::setw(4) << std::setfill(' ')<< i + 1 << " |"; 
			m_items[i]->write(std::cout, true);
			std::cout << "\n";
			sum += m_items[i]->cost()*m_items[i]->quantity();
		}
		std::cout << "-----^-------^--------------------^-------^---^----^---------^\n";
		std::cout << "                               Total Asset: $ |       " << sum <<"|\n";
		std::cout << "-----^-------^--------------------^-------^---^----^---------^\n";

	}
	void PosApp::truncateBillFile()
	{

		std::fstream(m_billfname, std::ios::out);
		std::fstream(m_billfname, std::ios::trunc);
	}

	void PosApp::addItem(bool isPerishable)
	{
		if (isPerishable == true)
		{
			Perishable *hold = new Perishable;

			hold->read(std::cin);
			if (std::cin.fail() == true)
			{
				std::cout << hold;
			}
			else
			{
				m_items[m_noOfItems] = hold;
				m_noOfItems++;
				std::cout << "Item added\n" << std::endl;
			}
		}
		else
		{
			NonPerishable *hold = new NonPerishable;

			hold->read(std::cin);
			if (std::cin.fail() == true)
			{
				std::cout << hold;
			}
			else
			{
				m_items[m_noOfItems] = hold;
				m_noOfItems++;
				std::cout << "Item added." << std::endl;
			}
		}
	}
	void PosApp::showBill()
	{

		std::fstream myFile(m_billfname, std::ios::in);
		if (myFile.failbit != 0)
		{
			char signature;
			double cost = 0;
			Date showtime;
			std::cout << "v--------------------------------------------------------v\n";
			std::cout << "| " << showtime << "                                      |\n";
			std::cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |\n";
			std::cout << "|--------|--------------------|-------|---|----|---------|\n";
			while (!myFile.get(signature).fail())
			{
				myFile.ignore(1);

				if (signature == 'P')
				{
					Perishable *hold = new Perishable;
					hold->load(myFile);
					std::cout << "| ";
					hold->write(std::cout, true);
					std::cout << "\n";
					cost += hold->cost();
					
				}
				else if (signature == 'N')
				{
					NonPerishable *hold = new NonPerishable;
					hold->load(myFile);
					std::cout << "| ";
					hold->write(std::cout, true);
					std::cout << "\n";
					cost += hold->cost();
					
				}
			}
			std::cout << "^--------^--------------------^-------^---^----^---------^\n";
			std::cout << "|                               Total: $  |         " << cost << "|\n";
			std::cout << "^-----------------------------------------^--------------^\n";
		}

		else
		{
			myFile.clear();
			myFile.close();

			std::fstream myFile(m_filename, std::ios::out);
			myFile.close();
		}
	
	}
	void PosApp::run()
	{
		

		int checkinput;

		do
		{
			
			checkinput = menu();
			
		switch (checkinput)
		{
			if (isdigit(checkinput) == false)
			{
				std::cout << "===Invalid Selection, try again===\n" << std::endl;
				break;
			}
		case 1:
			listItems();
			std::cout << "\n";
			break;
		case 2:
			addItem(true);
			std::cout << "\n";
			break;
		case 3:
			addItem(false);
			std::cout << "\n";
			break;
		case 4:
			updateQty();
			std::cout << "\n";
			break;
		case 5:
			
			char sku[10];
			std::cout << "Please enter the SKU: ";
			std::cin >> sku;
			int index;
			index = searchItems(sku);
			if (index == -1)
			{
				std::cout << "Not found!\n";
				break;
			}
			else
			{
				std::cout << "v-----------------------------------v\n";
				m_items[index]->write(std::cout, false);
				std::cout << "^-----------------------------------^\n";
				break;
			}
		case 6:
			POS();
			break;
		case 0:
			std::cout << "Goodbye!\n";
			break;
		default:
			std::cout << "===Invalid Selection, try again===\n" << std::endl;
			break;
		}
		} while (checkinput != 0);
	
	}
	void PosApp::POS()
	{
		getchar();
		char inputsku[MAX_SKU_LEN];
		int index = -1;
		truncateBillFile();
		while (true)
		{
			std::cout << "Sku: ";
				std::cin.getline(inputsku, MAX_SKU_LEN);
			if (strcmp(inputsku, "") == 0)
			{
				break;
			}
			index = searchItems(inputsku);
			if (index != -1)
			{
				std::cout << "v------------------->\n"
						  << "| " << m_items[index]->name() << "\n"
						  << "^------------------->\n";
				addToBill(*m_items[index]);
			}
			else
			{
				std::cout << "Not found!\n";
			}
		}
		
		showBill();
	}

	void PosApp::addToBill(Item& I)
	{
		int hold = I.quantity();

		std::fstream myFile(m_billfname, std::ios::out | std::ios::app);
		I.quantity(1);
		I.save(myFile);
		I.quantity(hold-1);
		saveRecs();
		loadRecs();
	}

	

	/*
	ouputs:
	-------------------------------------
	update:
	Please enter the SKU: 1313
	Name:
	Paper Tissue
	Sku: 1313
	Price: 1.22
	Price after tax: 1.38
	Quantity: 194
	Total Cost: 267.45

	Please enter the number of purchased items: 12
	Updated!

	------------------------------
	Please enter the SKU: 3434
	Not found!

	-------------------------------------
	add item:
	Perishable Item Entry:
	Sku: 5656
	Name:
	Honey
	Price: 12.99
	Taxed: y
	Quantity: 12
	Expiry date (YYYY/MM/DD): 1200/10/12
	Invalid Year in Date Entry

	Perishable Item Entry:
	Sku: 5656
	Name:
	Honey
	Price: 12.99
	Taxed: y
	Quantity: 12
	Expiry date (YYYY/MM/DD): 2017/5/15
	Item added.

	--------------------------------------------
	list item:
	 Row | SKU    | Item Name          | Price |TX |Qty |   Total |
	-----|--------|--------------------|-------|---|----|---------|
	   1 | 1234   |Milk                |   3.99|  P|   2|     7.98|
	   2 | 3456   |Paper Cups          |   5.99| TN|  38|   257.21|
	   3 | 4567   |Butter              |   4.56| TP|   9|    46.38|
	   4 | 1212   |Salted Butter       |   5.99|  P| 111|   664.89|
	   5 | 1313   |Paper Tissue        |   1.22| TN| 206|   283.99|
	   6 | 5656   |Honey               |  12.99| TP|  12|   176.14|
	-----^--------^--------------------^-------^---^----^---------^
								   Total Asset: $  |       1436.59|
	-----------------------------------------------^--------------^


	--------------------------------------
	printbill:
	v--------------------------------------------------------v
	| 2017/04/02, 12:42                                      |
	| SKU    | Item Name          | Price |TX |Qty |   Total |
	|--------|--------------------|-------|---|----|---------|
	| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
	| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
	| 5656   |Honey               |  12.99| TP|   1|    14.68|
	^--------^--------------------^-------^---^----^---------^
	|                               Total: $  |         22.05|
	^-----------------------------------------^--------------^

	-------------------------------------------------------
	POS:
	Sku: 1212
	v------------------->
	| Salted Butter
	^------------------->
	Sku: 1212
	v------------------->
	| Salted Butter
	^------------------->
	Sku: 1313
	v------------------->
	| Paper Tissue
	^------------------->
	Sku: 1234
	v------------------->
	| Milk
	^------------------->
	Sku: 7654
	Not found!
	Sku: 5656
	v------------------->
	| Honey
	^------------------->
	Sku:
	v--------------------------------------------------------v
	| 2017/04/02, 12:58                                      |
	| SKU    | Item Name          | Price |TX |Qty |   Total |
	|--------|--------------------|-------|---|----|---------|
	| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
	| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
	| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
	| 1234   |Milk                |   3.99|  P|   1|     3.99|
	| 5656   |Honey               |  12.99| TP|   1|    14.68|
	^--------^--------------------^-------^---^----^---------^
	|                               Total: $  |         32.03|
	^-----------------------------------------^--------------^

	------------------------------------------------------
	run:
	The Sene-Store
	1- List items
	2- Add Perishable item
	3- Add Non-Perishable item
	4- Update item quantity
	5- Show Item
	6- POS
	0- exit program
	> 5

	Please enter the SKU: 5656
	v-----------------------------------v
	Name:
	Honey
	Sku: 5656
	Price: 12.99
	Price after tax: 14.68
	Quantity: 10
	Total Cost: 146.79
	Expiry date: 2017/05/15
	^-----------------------------------^

	The Sene-Store
	1- List items
	2- Add Perishable item
	3- Add Non-Perishable item
	4- Update item quantity
	5- Show Item
	6- POS
	0- exit program
	> 5

	Please enter the SKU: 12345
	Not found!

	The Sene-Store
	1- List items
	2- Add Perishable item
	3- Add Non-Perishable item
	4- Update item quantity
	5- Show Item
	6- POS
	0- exit program
	> five

	===Invalid Selection, try again===

	The Sene-Store
	1- List items
	2- Add Perishable item
	3- Add Non-Perishable item
	4- Update item quantity
	5- Show Item
	6- POS
	0- exit program
	> 0

	Goodbye!

	*/
}
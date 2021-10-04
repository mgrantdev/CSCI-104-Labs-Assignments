#include "inventory.h"
#include <iostream>

Inventory::Inventory()
{
	// nothing to do here
}

/* Add an item to the inventory with the given name and amount. */
void Inventory::addItem(std::string name, int amount)
{
	// TODO
	for (iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->name == name)
		{
			it->amount += amount;
		    return;
		}
	}
	// iterator end = this->end();
	// *(end+1) = Item(name, amount);
	Item item (name, amount);
	this->push_back(item);
}

/* Remove all items with this name from the inventory. */
void Inventory::removeItem(std::string name)
{
	// TODO
	iterator it = this->begin();
	// while (it != this->end())
	// {
	// 	if (it->name == name)
	// 	{
	// 		it = this->erase(it);
	// 	}
	// 	else ++it;
	// }
	for (; it != this->end(); ++it)
	{
		if (it->name == name)
		{
			it = this->erase(it);
			--it;
		}
	}
}

/* Return the number of items with this name from the inventory. */
int Inventory::getNumItems(std::string name)
{
	// TODO
	for (iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->name == name) return it->amount;
	}
	return 0;
}

/* Print all the items in this format:
	key value
	key value
	key value
*/
void Inventory::printAllItems()
{
	// TODO
	for (iterator it = this->begin(); it != this->end(); ++it)
	{
		std::cout << it->name << " " << it->amount << std::endl;
	}
}
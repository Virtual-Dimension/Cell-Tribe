#pragma once
#include "Item.h"
#include <vector>
class Item;

class ItemManager {
protected:
	size_t maxSize;
	std::vector < Item* > items;
public:
	ItemManager();
	ItemManager(const size_t&);
	~ItemManager();
	Item* getItem(const size_t&);
	Item* operator [] (const size_t&);
	int pushItem(Item*);
};
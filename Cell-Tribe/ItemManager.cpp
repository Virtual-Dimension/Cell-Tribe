#include "ItemManager.h"

ItemManager::ItemManager() : maxSize(0), items() {}

ItemManager::ItemManager(const size_t& maxsize) : maxSize(maxsize), items() {}

ItemManager::~ItemManager() { for (auto p : items) delete p; }

Item* ItemManager::getItem(const size_t& id) { return items[id]; }

Item* ItemManager::operator [] (const size_t& id) { return getItem(id); }

int ItemManager::pushItem(Item* item) {
	if (maxSize && items.size() >= maxSize) return ITEMMANAGER_FULL;
	items.push_back(item);
	return OPERATOR_SUCCESS;
}

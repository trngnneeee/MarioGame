#include "HiddenBoxItemFactory.h"

HiddenBoxItemFactory::HiddenBoxItemFactory()
{
	prototypes["Mushroom"] = new PowerUpMushroom();
	prototypes["Star"] = new InvicibleStar();
}

HiddenBoxItemFactory::~HiddenBoxItemFactory()
{
	for (auto& pair : prototypes) {
		delete pair.second;
	}
}

HiddenBoxItem* HiddenBoxItemFactory::createItem(const std::string& itemType) const
{
	if (prototypes.find(itemType) != prototypes.end()) {
		return prototypes.at(itemType)->clone(); 
	}
	return nullptr; 

}

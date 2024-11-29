#pragma once
#include "HiddenBoxItem.h"
#include "PowerUpMushroom.h"
#include "InvicibleStar.h"
#include <unordered_map>
#include <string>

class HiddenBoxItemFactory
{
private:
	std::unordered_map<std::string, HiddenBoxItem*> prototypes;
public:
    // Constructors
    HiddenBoxItemFactory();
    // Destructors
    ~HiddenBoxItemFactory();
    // Functions
    HiddenBoxItem* createItem(const std::string& itemType) const;
};


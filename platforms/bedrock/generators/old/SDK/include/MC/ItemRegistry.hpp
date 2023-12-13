#pragma once
#include "../Global.h"
#include "WeakPtr.hpp"

class ItemRegistry {
public:
	// ?getItem@ItemRegistry@@SA?AV?$WeakPtr@VItem@@@@F@Z
	MCAPI static class WeakPtr<class Item> getItem(short);
	// ?getItemCount@ItemRegistry@@SAHXZ
	MCAPI static int getItemCount();
};

#include "pch.h"

#include <fstream>
#include <string>

#include <MC/BaseGameVersion.hpp>
#include <MC/SemVersion.hpp>
#include <MC/ItemRegistry.hpp>
#include <MC/Item.hpp>
#include <MC/Types.hpp>
#include "get_file.hpp"


TInstanceHook(void, "?registerItem@ItemRegistry@@SAXV?$SharedPtr@VItem@@@@@Z", ItemRegistry, void* itemV) {
	// I could not work out how to get the data from the shared pointer
	original(this, itemV);
	WeakPtr<Item> itemPtr = this->getItem(this->getItemCount());
	Item* item = itemPtr.get();
	if (item != NULL) {
		//MCAPI bool allowOffhand() const;
		*getFile("generated/item/data/min_version.txt") << item->getRequiredBaseGameVersion().asSemVersion().asString() << std::endl;
		//MCAPI enum CreativeItemCategory getCreativeCategory() const;
		//MCAPI float destroySpeedBonus(class ItemStackBase const&) const;
		//MCAPI int getFrameCount() const;
		* getFile("generated/item/data/id.txt") << item->getId() << std::endl;
		//MCAPI class HashedString const& getFullNameHash() const;
		//MCAPI class HashedString const& getRawNameHash() const;
		//MCAPI bool isElytra() const;
		//MCAPI bool isExplodable() const;
		//MCAPI bool isFireResistant() const;
		//MCAPI bool isNameTag() const;
		//MCAPI bool isSeed() const;
		//MCAPI class ItemDescriptor buildDescriptor(short, class CompoundTag const*) const;
		//MCAPI bool shouldDespawn() const;
		//MCAPI static std::string const ICON_DESCRIPTION_PREFIX;
		//MCAPI static std::string const TAG_DAMAGE;
		//MCAPI std::string const& getCreativeGroup() const;
		* getFile("generated/item/data/name.txt") << item->getFullItemName() << std::endl;
		//MCAPI std::string const& getNamespace() const;
		//MCAPI std::string const& getRawNameId() const;
		//MCAPI std::string getSerializedName() const;
		//MCAPI static struct NewBlockID toBlockId(short);
		//MCAPI std::vector<struct CommandName> getCommandNames() const;
		//MCAPI class WeakPtr<class BlockLegacy> const& getLegacyBlock() const;
	}
}

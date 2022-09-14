#include "pch.h"

#include <fstream>
#include <string>
#include <memory>
#include <iostream>

#include <MC/Minecraft.hpp>
#include <MC/Level.hpp>
#include <MC/BlockPalette.hpp>
#include <MC/Block.hpp>
#include <MC/BlockLegacy.hpp>
#include <MC/IDataOutput.hpp>
#include <MC/HashedString.hpp>
#include <MC/BaseGameVersion.hpp>
#include <MC/Brightness.hpp>

#include <MC/NbtIo.hpp>
#include <MC/CompoundTag.hpp>

#include "get_file.hpp"


std::string write_compound(const CompoundTag *tag) {
    void* vtbl = dlsym("??_7StringByteOutput@@6B@");
    string result = "";
    void* iDataOutput[2] = { vtbl, &result };
    NbtIo::write(tag, (IDataOutput&)iDataOutput);
    return result;
}

void block_state(const Block &block) {
    const CompoundTag* tag = &block.getSerializationId();
    std::string out = write_compound(tag);
    getFile("generated/block/states.bin", true)->write(out.c_str(), out.size());
}

void block_map_colour(const Block& block) {
    auto colour = block.getLegacyBlock().getMapColor();
    *getFile("generated/block/map_colour.txt") << colour.r << "," << colour.g << "," << colour.b << "," << colour.a << std::endl;
}

void block_min_version(const Block& block) {
    const BlockLegacy &legacy_block = block.getLegacyBlock();
    const BaseGameVersion &min_version = legacy_block.getRequiredBaseGameVersion();
    const SemVersion& sem_version = min_version.asSemVersion();
    *getFile("generated/block/min_game_version.txt") << sem_version.asString() << std::endl;
}

void block_light(const Block& block) {
    Brightness light = block.getLight();
    const unsigned char* light_value = (unsigned char*) &light;
    const int light_value_int = *light_value;
    *getFile("generated/block/light.txt") << light_value_int << std::endl;
}

void block_light_emission(const Block& block) {
    Brightness light = block.getLightEmission();
    const unsigned char* light_value = (unsigned char*)&light;
    const int light_value_int = *light_value;
    *getFile("generated/block/light_emission.txt") << light_value_int << std::endl;
}


void generate_block_data(Minecraft* minecraft) {
    Level* level = minecraft->getLevel();
    BlockPalette* block_palette = &level->getBlockPalette();

    unsigned int palette_len = (*(unsigned int*)(block_palette + 0x78) - *(unsigned int*)(block_palette + 0x70)) / 8;
    // handle error state
    for (unsigned int block_id = 0; block_id < palette_len; block_id++) {
        const Block &block = block_palette->getBlock(block_id);
        const BlockLegacy& legacy_block = block.getLegacyBlock();
        
        // Block state info
        *getFile("generated/block/name.txt") << block.getName().getString() << std::endl;
        block_state(block);
        *getFile("generated/block/variant.txt") << block.getVariant() << std::endl;
        *getFile("generated/block/runtime_id.txt") << block.getRuntimeId() << std::endl;

        // Block attributes

        //bool breaksFallingBlocks(class BaseGameVersion) const;
        //bool breaksFallingBlocks(class Block const&, class BaseGameVersion) const;
        //bool canBeBrokenFromFalling() const;
        //bool canBeDestroyedByWaterSpread() const;
        //bool canBeOriginalSurface() const;
        //bool canBeSilkTouched() const;
        //bool canBeUsedInCommands(class BaseGameVersion const&) const;
        //bool canConnect(class Block const&, unsigned char, class Block const&) const;
        //bool canContainLiquid() const;
        //bool canDamperVibrations() const;
        //bool canHaveExtraData() const;
        //bool canHurtAndBreakItem() const;
        //bool canInstatick() const;
        //bool canOccludeVibrations() const;
        //bool canProvideFullSupport(class Block const&, unsigned char) const;
        //bool canProvideFullSupport(unsigned char) const;
        //bool canProvideMultifaceSupport(class Block const&, unsigned char) const;
        //bool canProvideMultifaceSupport(unsigned char) const;
        //bool canProvideSupport(class Block const&, unsigned char, enum BlockSupportType) const;
        //bool canProvideSupport(unsigned char, enum BlockSupportType) const;
        //bool canSpawnOn() const;
        //bool causesFreezeEffect() const;
        //bool const hasRuntimeId() const;
        //bool getAllowsRunes() const;
        //bool hasBlockEntity() const;
        //bool hasComparatorSignal() const;
        //bool hasProperty(enum BlockProperty) const;
        //bool hasPropertyNoLock(enum BlockProperty) const;
        //bool hasState(class HashedString const&) const;
        //bool hasState(class ItemState const&) const;
        //bool hasTag(class HashedString const&) const;
        //bool hasTag(unsigned __int64 const&) const;
        //bool hasVariableLighting() const;
        //bool ignoreEntitiesOnPistonMove() const;
        //bool ignoreEntitiesOnPistonMove(class Block const&) const;
        //bool isAir() const;
        //bool isAuxValueRelevantForPicking() const;
        //bool isBounceBlock() const;
        //bool isButtonBlock() const;
        //bool isCandleCakeBlock() const;
        *getFile("generated/block/is_container.txt") << block.isContainerBlock() << std::endl;
        //bool isCraftingBlock() const;
        //bool isCropBlock() const;
        //bool isDoorBlock() const;
        //bool isDoubleSlabBlock() const;
        //bool isEmpty() const;
        //bool isFenceBlock() const;
        //bool isFenceGateBlock() const;
        //bool isFilteredOut(enum BlockRenderLayer) const;
        //bool isHeavy() const;
        //bool isHurtableBlock() const;
        * getFile("generated/block/interactive.txt") << block.isInteractiveBlock() << std::endl;
        //bool isLeverBlock() const;
        * getFile("generated/block/motion_blocking.txt") << block.isMotionBlockingBlock() << std::endl;
        //bool isMultifaceBlock() const;
        //bool isPreservingMediumWhenPlaced(class Block const&) const;
        //bool isPreservingMediumWhenPlaced(class BlockLegacy const*) const;
        //bool isRailBlock() const;
        //bool isSignalSource() const;
        //bool isSlabBlock() const;
        * getFile("generated/block/solid.txt") << block.isSolid() << std::endl;
        //bool isSolidBlockingBlock() const;
        //bool isSolidBlockingBlockAndNotSignalSource() const;
        //bool isStairBlock() const;
        //bool isStandingSign() const;
        //bool isStemBlock() const;
        //bool isStrippable(class Block const&) const;
        //bool isThinFenceBlock() const;
        * getFile("generated/block/unbreakable.txt") << block.isUnbreakable() << std::endl;
        //bool isValidAuxValue(int) const;
        //bool isVanilla() const;
        //bool isWallBlock() const;
        *getFile("generated/block/water_blocking.txt") << block.isWaterBlocking() << std::endl;
        //bool liquidCanFlowIntoFromDirection(unsigned char, class std::function<class Block const& (class BlockPos const&)> const&, class BlockPos const&) const;
        //bool matchesStates(class BlockLegacy const&) const;
        *getFile("generated/block/may_pick.txt") << block.mayPick() << std::endl;
        //bool pushesOutItems() const;
        //bool pushesUpFallingBlocks() const;
        //bool shouldRandomTick() const;
        //bool waterSpreadCausesSpawn() const;
        //class AABB const& getUIShape(class Block const&, class AABB&) const;
        //class AABB const& getVisualShape(class Block const&, class AABB&, bool) const;
        //class AABB const& getVisualShape(class AABB&, bool) const;
        block_min_version(block);
        //class Block const& getDefaultState() const;
        //class Block const& getRenderBlock() const;
        //class Block const& getStrippedBlock(class Block const&) const;
        //class Block const* tryGetInfested(class Block const&) const;
        //class Block const* tryGetStateFromLegacyData(unsigned short) const;
        //class Block const* tryGetUninfested(class Block const&) const;
        //class Block const* tryLegacyUpgrade(unsigned short) const;
        //class Block const& copyState(class Block const&, class ItemState const&) const;
        //class Block const& keepState(class ItemState const&) const;
        //class BlockLegacy& init();
        //class BlockLegacy& overrideBlockProperties(enum BlockProperty);
        //class BlockStateGroup* getBlockStateGroup();
        //class CopperBehavior const* tryGetCopperBehavior() const;
        //class EntityContext& getEntityForModification() const;
        //class EntityContext const& getEntity() const;
        //class EntityContext const& getEntityNoCheck() const;
        //class HashedString const& getRawNameHash() const;
        //class ItemInstance getResourceItem(class Randomize&, class Block const&, int) const;
        //class ItemInstance getSilkTouchItemInstance() const;
        //class ItemInstance getSilkTouchItemInstance(class Block const&) const;
        //class ItemState const* getBlockState(class HashedString const&) const;
        //class Material const& getMaterial() const;
        //class Vec3 randomlyModifyPosition(class BlockPos const&) const;
        //class Vec3 randomlyModifyPosition(class BlockPos const&, int&) const;
        //class WeakPtr<class BlockLegacy> createWeakPtr() const;
        //class gsl::basic_string_span<char const, -1> getCreativeGroup() const;
        block_map_colour(block);
        *getFile("generated/block/block_entity.txt") << block.getBlockEntityType() << std::endl;
        //enum BlockRenderLayer getRenderLayer() const;
        //enum CreativeItemCategory getCreativeCategory() const;
        //enum Flip getFaceFlip(unsigned char, class Block const&) const;
        //float calcGroundFriction(struct IMobMovementProxy const&, class BlockPos const&) const;
        *getFile("generated/block/destroy_speed.txt") << block.getDestroySpeed() << std::endl;
        *getFile("generated/block/friction.txt") << block.getFriction() << std::endl;
        //float getShadeBrightness(class Block const&) const;
        //float getThickness() const;
        *getFile("generated/block/translucency.txt") << block.getTranslucency() << std::endl;
        //int getBurnOdds() const;
        //int getColor() const;
        //int getColor(class Block const&) const;
        //int getExperienceDrop(class Random&) const;
        //int getExtraRenderLayers() const;
        //int getFlameOdds() const;
        //int getIconYOffset() const;
        //int getResourceCount(class Randomize&, class Block const&, int) const;
        //int getResourceCount(class Randomize&, int) const;
        //short getBlockItemId() const;
        //static float const SIZE_OFFSET;
        //static std::string const BLOCK_DESCRIPTION_PREFIX;
        //static struct BlockLegacy::NameInfo extractBlockNameInfo(std::string const&);
        //std::string _getHardCodedJSON() const;
        //std::string buildDescriptionId() const;
        //std::string buildDescriptionId(class Block const&) const;
        //std::string buildDescriptionName() const;
        //std::string buildDescriptionName(class Block const&) const;
        //std::string const& getDescriptionId() const;
        //std::string const& getNamespace() const;
        //std::string const& getRawNameId() const;
        //std::string getDescriptionId() const;
        //std::vector<struct CommandName> getCommandNames() const;
        //struct Brightness getEmissiveBrightness(class Block const&) const;
        block_light(block);
        block_light_emission(block);
        //struct Brightness getLightEmission(class Block const&) const;
        //unsigned char getMappedFace(unsigned char, class Block const&) const;
        //void cacheComponentData();
        //void forEachBlockPermutation(class std::function<bool(class Block const&)>) const;
        //void forEachItemStateInstance(class std::function<bool(class ItemStateInstance const&)>) const;
        //void getDebugText(std::vector<std::string>&, class BlockPos const&) const;
    }
}

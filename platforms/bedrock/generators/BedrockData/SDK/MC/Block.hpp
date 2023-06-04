#pragma once
#include <limits>
#include "MC/nbt/CompoundTag.hpp"


namespace MinecraftAPI {
	class Block {
		// 1.11.0.23
		// ?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ
		//class BlockLegacy const& Block::getLegacyBlock(void)const

		//1.16.0.2
		// ?getDefaultState@Block@@QEBAAEBV1@XZ
		//class Block const& Block::getDefaultState(void)const

		//1.16.100.4
		// ?getDescriptionId@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
		//std::string Block::getDescriptionId(void)const 
		// ?getDestroySpeed@Block@@QEBAMXZ
		//float Block::getDestroySpeed(void)const 
		typedef float (*_getFrictionT)(const Block*);
		static _getFrictionT _getFriction;
		// ?getFullName@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
		//std::string Block::getFullName(void)const 
		// ?getLight@Block@@QEBA?AUBrightness@@XZ
		//struct Brightness Block::getLight(void)const 
		// ?getLightEmission@Block@@QEBA?AUBrightness@@XZ
		//struct Brightness Block::getLightEmission(void)const 
		// ?getMapColor@Block@@QEBA?AVColor@@AEAVBlockSource@@AEBVBlockPos@@@Z
		//class Color Block::getMapColor(class BlockSource &,class BlockPos const &)const 

		//1.16.210.5
		typedef CompoundTag const& (*_getSerializationIdT)(const Block*);
		static _getSerializationIdT _getSerializationId;

		typedef bool (*_isContainerBlockT)(const Block*);
		static _isContainerBlockT _isContainerBlock;

		typedef enum BlockActorType(*_getBlockEntityTypeT)(const Block*);
		static _getBlockEntityTypeT _getBlockEntityType;

		typedef int (*_getVariantT)(const Block*);
		static _getVariantT _getVariant;


	public:
		static void* vftable;

		float getFriction() const {
			if (_getFriction) {
				return _getFriction(this);
			}
			return std::numeric_limits<float>::quiet_NaN();
		}

		const CompoundTag* getSerializationId() const {
			if (_getSerializationId) {
				return &_getSerializationId(this);
			}
			return nullptr;
		};

		int isContainerBlock() const {
			if (_isContainerBlock) {
				return _isContainerBlock(this);
			}
			return -1;
		};

		int getBlockEntityType() const {
			if (_getBlockEntityType) {
				return _getBlockEntityType(this);
			}
			return -1;
		}

		int getVariant() const {
			if (_getVariant) {
				return _getVariant(this);
			}
			return -1;
		}
	};
}


/*
001.009.000.015_added.hpp
	static std::string const Block::BLOCK_DESCRIPTION_PREFIX
	void Block::buildSerializationId(void)
	enum AnvilDamage Block::getBlockState<enum AnvilDamage>(class BlockState const &)const 
	enum BlockColor Block::getBlockState<enum BlockColor>(class BlockState const &)const 
	enum CauldronLiquidType Block::getBlockState<enum CauldronLiquidType>(class BlockState const &)const 
	enum ChemistryTableType Block::getBlockState<enum ChemistryTableType>(class BlockState const &)const 
	enum DoublePlantType Block::getBlockState<enum DoublePlantType>(class BlockState const &)const 
	enum MonsterEggBlock::HostBlockType Block::getBlockState<enum MonsterEggBlock::HostBlockType>(class BlockState const &)const 
	enum OldLeafBlock::LeafType Block::getBlockState<enum OldLeafBlock::LeafType>(class BlockState const &)const 
	enum PortalAxis Block::getBlockState<enum PortalAxis>(class BlockState const &)const 
	enum SaplingType Block::getBlockState<enum SaplingType>(class BlockState const &)const 
	enum TallGrassType Block::getBlockState<enum TallGrassType>(class BlockState const &)const 
	enum TorchFacing Block::getBlockState<enum TorchFacing>(class BlockState const &)const 
	bool Block::getBlockState<bool>(class BlockState const &)const 
	int Block::getBlockState<int>(class BlockState const &)const 
	signed char Block::getBlockState<signed char>(class BlockState const &)const 
	virtual enum BlockRenderLayer Block::getRenderLayer(void)const 
	bool Block::hasBlockState(class BlockState const &)const 
	bool Block::isSolidBlockingBlock(void)const 
	bool Block::isSolidBlockingBlockAndNotSignalSource(void)const 
	class Block const & Block::keepBlockState(class BlockState const &)const 
	bool Block::liquidCanFlowIntoFromDirection(signed char,class std::function<class Block const & (class BlockPos const &)>,class BlockPos const &)const 
	class Block const * Block::setBlockState<enum AnvilDamage>(class BlockState const &,enum AnvilDamage)const 
	class Block const * Block::setBlockState<enum BlockColor>(class BlockState const &,enum BlockColor)const 
	class Block const * Block::setBlockState<enum Direction::Type>(class BlockState const &,enum Direction::Type)const 
	class Block const * Block::setBlockState<enum DirtBlock::DirtType>(class BlockState const &,enum DirtBlock::DirtType)const 
	class Block const * Block::setBlockState<enum Facing::Name>(class BlockState const &,enum Facing::Name)const 
	class Block const * Block::setBlockState<enum FenceBlockType>(class BlockState const &,enum FenceBlockType)const 
	class Block const * Block::setBlockState<enum FlowerBlock::ROSES>(class BlockState const &,enum FlowerBlock::ROSES)const 
	class Block const * Block::setBlockState<enum ItemColor>(class BlockState const &,enum ItemColor)const 
	class Block const * Block::setBlockState<enum ItemFrameBlock::ItemFrameDirection>(class BlockState const &,enum ItemFrameBlock::ItemFrameDirection)const 
	class Block const * Block::setBlockState<enum LeafSize>(class BlockState const &,enum LeafSize)const 
	class Block const * Block::setBlockState<enum MonsterEggBlock::HostBlockType>(class BlockState const &,enum MonsterEggBlock::HostBlockType)const 
	class Block const * Block::setBlockState<enum MultiTextureBlock::Type>(class BlockState const &,enum MultiTextureBlock::Type)const 
	class Block const * Block::setBlockState<enum OldLogBlock::LogType>(class BlockState const &,enum OldLogBlock::LogType)const 
	class Block const * Block::setBlockState<enum PrismarineBlock::PrismarineType>(class BlockState const &,enum PrismarineBlock::PrismarineType)const 
	class Block const * Block::setBlockState<enum QuartzBlockBlock::Type>(class BlockState const &,enum QuartzBlockBlock::Type)const 
	class Block const * Block::setBlockState<enum SandStoneBlock::SandstoneType>(class BlockState const &,enum SandStoneBlock::SandstoneType)const 
	class Block const * Block::setBlockState<enum SaplingType>(class BlockState const &,enum SaplingType)const 
	class Block const * Block::setBlockState<enum SeaGrass::Type>(class BlockState const &,enum SeaGrass::Type)const 
	class Block const * Block::setBlockState<enum SpongeBlock::SpongeType>(class BlockState const &,enum SpongeBlock::SpongeType)const 
	class Block const * Block::setBlockState<enum StalkThickness>(class BlockState const &,enum StalkThickness)const 
	class Block const * Block::setBlockState<enum StoneBlockType>(class BlockState const &,enum StoneBlockType)const 
	class Block const * Block::setBlockState<enum StoneSlabBlock2::StoneSlabType>(class BlockState const &,enum StoneSlabBlock2::StoneSlabType)const 
	class Block const * Block::setBlockState<enum StoneSlabBlock3::StoneSlabType>(class BlockState const &,enum StoneSlabBlock3::StoneSlabType)const 
	class Block const * Block::setBlockState<enum StoneSlabBlock4::StoneSlabType>(class BlockState const &,enum StoneSlabBlock4::StoneSlabType)const 
	class Block const * Block::setBlockState<enum StoneSlabBlock::StoneSlabType>(class BlockState const &,enum StoneSlabBlock::StoneSlabType)const 
	class Block const * Block::setBlockState<enum TallGrassType>(class BlockState const &,enum TallGrassType)const 
	class Block const * Block::setBlockState<enum TorchFacing>(class BlockState const &,enum TorchFacing)const 
	class Block const * Block::setBlockState<enum TrapDoorBlock::TrapDoorDir>(class BlockState const &,enum TrapDoorBlock::TrapDoorDir)const 
	class Block const * Block::setBlockState<enum WoodBlockType>(class BlockState const &,enum WoodBlockType)const 
	class Block const * Block::setBlockState<bool>(class BlockState const &,bool)const 
	class Block const * Block::setBlockState<int>(class BlockState const &,int)const 
	class Block const * Block::setBlockState<signed char>(class BlockState const &,signed char)const 
	class Block const * Block::setBlockState<unsigned char>(class BlockState const &,unsigned char)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,float,int)const 
	std::string Block::toDebugString(void)const 

001.010.000.007_added.hpp
	void Block::buildSerializationId(unsigned int)
	enum AttachmentType Block::getBlockState<enum AttachmentType>(class BlockState const &)const 
	enum ChiselType Block::getBlockState<enum ChiselType>(class BlockState const &)const 
	enum CoralColor Block::getBlockState<enum CoralColor>(class BlockState const &)const 
	enum Direction::Type Block::getBlockState<enum Direction::Type>(class BlockState const &)const 
	enum DirtType Block::getBlockState<enum DirtType>(class BlockState const &)const 
	enum FlowerType Block::getBlockState<enum FlowerType>(class BlockState const &)const 
	enum MonsterEggStoneType Block::getBlockState<enum MonsterEggStoneType>(class BlockState const &)const 
	enum NewLeafType Block::getBlockState<enum NewLeafType>(class BlockState const &)const 
	enum NewLogType Block::getBlockState<enum NewLogType>(class BlockState const &)const 
	enum OldLeafType Block::getBlockState<enum OldLeafType>(class BlockState const &)const 
	enum PrismarineBlockType Block::getBlockState<enum PrismarineBlockType>(class BlockState const &)const 
	enum SandType Block::getBlockState<enum SandType>(class BlockState const &)const 
	enum SeaGrassType Block::getBlockState<enum SeaGrassType>(class BlockState const &)const 
	enum SpongeType Block::getBlockState<enum SpongeType>(class BlockState const &)const 
	enum StoneBrickType Block::getBlockState<enum StoneBrickType>(class BlockState const &)const 
	enum StoneSlabType2 Block::getBlockState<enum StoneSlabType2>(class BlockState const &)const 
	enum StoneSlabType3 Block::getBlockState<enum StoneSlabType3>(class BlockState const &)const 
	enum StoneSlabType4 Block::getBlockState<enum StoneSlabType4>(class BlockState const &)const 
	enum StoneSlabType Block::getBlockState<enum StoneSlabType>(class BlockState const &)const 
	enum StoneType Block::getBlockState<enum StoneType>(class BlockState const &)const 
	enum WallBlockType Block::getBlockState<enum WallBlockType>(class BlockState const &)const 
	enum WoodType Block::getBlockState<enum WoodType>(class BlockState const &)const 
	unsigned char Block::getBlockState<unsigned char>(class BlockState const &)const 
	bool Block::liquidCanFlowIntoFromDirection(unsigned char,class std::function<class Block const & (class BlockPos const &)>,class BlockPos const &)const 
	class Block const * Block::setBlockState<enum AttachmentType>(class BlockState const &,enum AttachmentType)const 
	class Block const * Block::setBlockState<enum ChiselType>(class BlockState const &,enum ChiselType)const 
	class Block const * Block::setBlockState<enum CoralColor>(class BlockState const &,enum CoralColor)const 
	class Block const * Block::setBlockState<enum DirtType>(class BlockState const &,enum DirtType)const 
	class Block const * Block::setBlockState<enum DoublePlantType>(class BlockState const &,enum DoublePlantType)const 
	class Block const * Block::setBlockState<enum FlowerType>(class BlockState const &,enum FlowerType)const 
	class Block const * Block::setBlockState<enum MonsterEggStoneType>(class BlockState const &,enum MonsterEggStoneType)const 
	class Block const * Block::setBlockState<enum MushroomOuterType>(class BlockState const &,enum MushroomOuterType)const 
	class Block const * Block::setBlockState<enum NewLeafType>(class BlockState const &,enum NewLeafType)const 
	class Block const * Block::setBlockState<enum NewLogType>(class BlockState const &,enum NewLogType)const 
	class Block const * Block::setBlockState<enum OldLogType>(class BlockState const &,enum OldLogType)const 
	class Block const * Block::setBlockState<enum PrismarineBlockType>(class BlockState const &,enum PrismarineBlockType)const 
	class Block const * Block::setBlockState<enum SandStoneType>(class BlockState const &,enum SandStoneType)const 
	class Block const * Block::setBlockState<enum SeaGrassType>(class BlockState const &,enum SeaGrassType)const 
	class Block const * Block::setBlockState<enum SpongeType>(class BlockState const &,enum SpongeType)const 
	class Block const * Block::setBlockState<enum StoneBrickType>(class BlockState const &,enum StoneBrickType)const 
	class Block const * Block::setBlockState<enum StoneSlabType2>(class BlockState const &,enum StoneSlabType2)const 
	class Block const * Block::setBlockState<enum StoneSlabType3>(class BlockState const &,enum StoneSlabType3)const 
	class Block const * Block::setBlockState<enum StoneSlabType4>(class BlockState const &,enum StoneSlabType4)const 
	class Block const * Block::setBlockState<enum StoneSlabType>(class BlockState const &,enum StoneSlabType)const 
	class Block const * Block::setBlockState<enum StoneType>(class BlockState const &,enum StoneType)const 
	class Block const * Block::setBlockState<enum WallBlockType>(class BlockState const &,enum WallBlockType)const 
	class Block const * Block::setBlockState<enum WoodType>(class BlockState const &,enum WoodType)const 

001.010.000.007_removed.hpp
	void Block::buildSerializationId(void)
	enum MonsterEggBlock::HostBlockType Block::getBlockState<enum MonsterEggBlock::HostBlockType>(class BlockState const &)const 
	enum OldLeafBlock::LeafType Block::getBlockState<enum OldLeafBlock::LeafType>(class BlockState const &)const 
	signed char Block::getBlockState<signed char>(class BlockState const &)const 
	bool Block::hasBlockState(class BlockState const &)const 
	bool Block::liquidCanFlowIntoFromDirection(signed char,class std::function<class Block const & (class BlockPos const &)>,class BlockPos const &)const 
	class Block const * Block::setBlockState<enum DirtBlock::DirtType>(class BlockState const &,enum DirtBlock::DirtType)const 
	class Block const * Block::setBlockState<enum FenceBlockType>(class BlockState const &,enum FenceBlockType)const 
	class Block const * Block::setBlockState<enum FlowerBlock::ROSES>(class BlockState const &,enum FlowerBlock::ROSES)const 
	class Block const * Block::setBlockState<enum MonsterEggBlock::HostBlockType>(class BlockState const &,enum MonsterEggBlock::HostBlockType)const 
	class Block const * Block::setBlockState<enum MultiTextureBlock::Type>(class BlockState const &,enum MultiTextureBlock::Type)const 
	class Block const * Block::setBlockState<enum OldLogBlock::LogType>(class BlockState const &,enum OldLogBlock::LogType)const 
	class Block const * Block::setBlockState<enum PrismarineBlock::PrismarineType>(class BlockState const &,enum PrismarineBlock::PrismarineType)const 
	class Block const * Block::setBlockState<enum QuartzBlockBlock::Type>(class BlockState const &,enum QuartzBlockBlock::Type)const 
	class Block const * Block::setBlockState<enum SandStoneBlock::SandstoneType>(class BlockState const &,enum SandStoneBlock::SandstoneType)const 
	class Block const * Block::setBlockState<enum SeaGrass::Type>(class BlockState const &,enum SeaGrass::Type)const 
	class Block const * Block::setBlockState<enum SpongeBlock::SpongeType>(class BlockState const &,enum SpongeBlock::SpongeType)const 
	class Block const * Block::setBlockState<enum StoneBlockType>(class BlockState const &,enum StoneBlockType)const 
	class Block const * Block::setBlockState<enum StoneSlabBlock2::StoneSlabType>(class BlockState const &,enum StoneSlabBlock2::StoneSlabType)const 
	class Block const * Block::setBlockState<enum StoneSlabBlock3::StoneSlabType>(class BlockState const &,enum StoneSlabBlock3::StoneSlabType)const 
	class Block const * Block::setBlockState<enum StoneSlabBlock4::StoneSlabType>(class BlockState const &,enum StoneSlabBlock4::StoneSlabType)const 
	class Block const * Block::setBlockState<enum StoneSlabBlock::StoneSlabType>(class BlockState const &,enum StoneSlabBlock::StoneSlabType)const 
	class Block const * Block::setBlockState<enum WoodBlockType>(class BlockState const &,enum WoodBlockType)const 
	class Block const * Block::setBlockState<signed char>(class BlockState const &,signed char)const 

001.011.000.023_added.hpp
	enum SweetBerryBushBlock::BerryStage Block::getBlockState<enum SweetBerryBushBlock::BerryStage>(class BlockState const &)const 
	class BlockLegacy const & Block::getLegacyBlock(void)const 
	bool Block::hasBlockState(class BlockState const &)const 
	class Block const * Block::setBlockState<enum SweetBerryBushBlock::BerryStage>(class BlockState const &,enum SweetBerryBushBlock::BerryStage)const 

001.011.004.002_added.hpp
	float Block::getThickness(void)const 

001.012.000.028_added.hpp
	class Block const & Block::copyState(class Block const &,class ItemState const &)const 
	enum BlockColor Block::getState<enum BlockColor>(class ItemState const &)const 
	enum CauldronLiquidType Block::getState<enum CauldronLiquidType>(class ItemState const &)const 
	enum ChemistryTableType Block::getState<enum ChemistryTableType>(class ItemState const &)const 
	enum CoralColor Block::getState<enum CoralColor>(class ItemState const &)const 
	enum Direction::Type Block::getState<enum Direction::Type>(class ItemState const &)const 
	enum DirtType Block::getState<enum DirtType>(class ItemState const &)const 
	enum DoublePlantType Block::getState<enum DoublePlantType>(class ItemState const &)const 
	enum FlowerType Block::getState<enum FlowerType>(class ItemState const &)const 
	enum MonsterEggStoneType Block::getState<enum MonsterEggStoneType>(class ItemState const &)const 
	enum OldLeafType Block::getState<enum OldLeafType>(class ItemState const &)const 
	enum PortalAxis Block::getState<enum PortalAxis>(class ItemState const &)const 
	enum SandType Block::getState<enum SandType>(class ItemState const &)const 
	enum SaplingType Block::getState<enum SaplingType>(class ItemState const &)const 
	enum SeaGrassType Block::getState<enum SeaGrassType>(class ItemState const &)const 
	enum SpongeType Block::getState<enum SpongeType>(class ItemState const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(class ItemState const &)const 
	enum StoneSlabType2 Block::getState<enum StoneSlabType2>(class ItemState const &)const 
	enum StoneSlabType3 Block::getState<enum StoneSlabType3>(class ItemState const &)const 
	enum StoneSlabType4 Block::getState<enum StoneSlabType4>(class ItemState const &)const 
	enum StoneSlabType Block::getState<enum StoneSlabType>(class ItemState const &)const 
	enum StoneType Block::getState<enum StoneType>(class ItemState const &)const 
	enum SweetBerryBushBlock::BerryStage Block::getState<enum SweetBerryBushBlock::BerryStage>(class ItemState const &)const 
	enum TallGrassType Block::getState<enum TallGrassType>(class ItemState const &)const 
	enum TorchFacing Block::getState<enum TorchFacing>(class ItemState const &)const 
	enum WoodType Block::getState<enum WoodType>(class ItemState const &)const 
	bool Block::getState<bool>(class ItemState const &)const 
	int Block::getState<int>(class ItemState const &)const 
	unsigned char Block::getState<unsigned char>(class ItemState const &)const 
	bool Block::hasState(class ItemState const &)const 
	class Block const & Block::keepState(class ItemState const &)const 
	class Block const * Block::setState<enum AnvilDamage>(class ItemState const &,enum AnvilDamage)const 
	class Block const * Block::setState<enum AttachmentType>(class ItemState const &,enum AttachmentType)const 
	class Block const * Block::setState<enum BlockColor>(class ItemState const &,enum BlockColor)const 
	class Block const * Block::setState<enum ChiselType>(class ItemState const &,enum ChiselType)const 
	class Block const * Block::setState<enum CoralColor>(class ItemState const &,enum CoralColor)const 
	class Block const * Block::setState<enum Direction::Type>(class ItemState const &,enum Direction::Type)const 
	class Block const * Block::setState<enum DoublePlantType>(class ItemState const &,enum DoublePlantType)const 
	class Block const * Block::setState<enum Facing::Name>(class ItemState const &,enum Facing::Name)const 
	class Block const * Block::setState<enum FlowerType>(class ItemState const &,enum FlowerType)const 
	class Block const * Block::setState<enum ItemColor>(class ItemState const &,enum ItemColor)const 
	class Block const * Block::setState<enum ItemFrameBlock::ItemFrameDirection>(class ItemState const &,enum ItemFrameBlock::ItemFrameDirection)const 
	class Block const * Block::setState<enum LeafSize>(class ItemState const &,enum LeafSize)const 
	class Block const * Block::setState<enum MonsterEggStoneType>(class ItemState const &,enum MonsterEggStoneType)const 
	class Block const * Block::setState<enum MushroomOuterType>(class ItemState const &,enum MushroomOuterType)const 
	class Block const * Block::setState<enum NewLeafType>(class ItemState const &,enum NewLeafType)const 
	class Block const * Block::setState<enum NewLogType>(class ItemState const &,enum NewLogType)const 
	class Block const * Block::setState<enum OldLogType>(class ItemState const &,enum OldLogType)const 
	class Block const * Block::setState<enum PortalAxis>(class ItemState const &,enum PortalAxis)const 
	class Block const * Block::setState<enum PrismarineBlockType>(class ItemState const &,enum PrismarineBlockType)const 
	class Block const * Block::setState<enum SandStoneType>(class ItemState const &,enum SandStoneType)const 
	class Block const * Block::setState<enum SaplingType>(class ItemState const &,enum SaplingType)const 
	class Block const * Block::setState<enum SeaGrassType>(class ItemState const &,enum SeaGrassType)const 
	class Block const * Block::setState<enum SpongeType>(class ItemState const &,enum SpongeType)const 
	class Block const * Block::setState<enum StalkThickness>(class ItemState const &,enum StalkThickness)const 
	class Block const * Block::setState<enum StoneBrickType>(class ItemState const &,enum StoneBrickType)const 
	class Block const * Block::setState<enum StoneSlabType2>(class ItemState const &,enum StoneSlabType2)const 
	class Block const * Block::setState<enum StoneSlabType3>(class ItemState const &,enum StoneSlabType3)const 
	class Block const * Block::setState<enum StoneSlabType4>(class ItemState const &,enum StoneSlabType4)const 
	class Block const * Block::setState<enum StoneSlabType>(class ItemState const &,enum StoneSlabType)const 
	class Block const * Block::setState<enum StoneType>(class ItemState const &,enum StoneType)const 
	class Block const * Block::setState<enum SweetBerryBushBlock::BerryStage>(class ItemState const &,enum SweetBerryBushBlock::BerryStage)const 
	class Block const * Block::setState<enum TallGrassType>(class ItemState const &,enum TallGrassType)const 
	class Block const * Block::setState<enum TorchFacing>(class ItemState const &,enum TorchFacing)const 
	class Block const * Block::setState<enum TrapDoorBlock::TrapDoorDir>(class ItemState const &,enum TrapDoorBlock::TrapDoorDir)const 
	class Block const * Block::setState<enum WallBlockType>(class ItemState const &,enum WallBlockType)const 
	class Block const * Block::setState<enum WoodType>(class ItemState const &,enum WoodType)const 
	class Block const * Block::setState<bool>(class ItemState const &,bool)const 
	class Block const * Block::setState<int>(class ItemState const &,int)const 
	class Block const * Block::setState<unsigned char>(class ItemState const &,unsigned char)const 
	class Block const * Block::setState<unsigned short>(class ItemState const &,unsigned short)const 

001.012.000.028_removed.hpp
	enum AnvilDamage Block::getBlockState<enum AnvilDamage>(class BlockState const &)const 
	enum AttachmentType Block::getBlockState<enum AttachmentType>(class BlockState const &)const 
	enum BlockColor Block::getBlockState<enum BlockColor>(class BlockState const &)const 
	enum CauldronLiquidType Block::getBlockState<enum CauldronLiquidType>(class BlockState const &)const 
	enum ChemistryTableType Block::getBlockState<enum ChemistryTableType>(class BlockState const &)const 
	enum ChiselType Block::getBlockState<enum ChiselType>(class BlockState const &)const 
	enum CoralColor Block::getBlockState<enum CoralColor>(class BlockState const &)const 
	enum Direction::Type Block::getBlockState<enum Direction::Type>(class BlockState const &)const 
	enum DirtType Block::getBlockState<enum DirtType>(class BlockState const &)const 
	enum DoublePlantType Block::getBlockState<enum DoublePlantType>(class BlockState const &)const 
	enum FlowerType Block::getBlockState<enum FlowerType>(class BlockState const &)const 
	enum MonsterEggStoneType Block::getBlockState<enum MonsterEggStoneType>(class BlockState const &)const 
	enum NewLeafType Block::getBlockState<enum NewLeafType>(class BlockState const &)const 
	enum NewLogType Block::getBlockState<enum NewLogType>(class BlockState const &)const 
	enum OldLeafType Block::getBlockState<enum OldLeafType>(class BlockState const &)const 
	enum PortalAxis Block::getBlockState<enum PortalAxis>(class BlockState const &)const 
	enum PrismarineBlockType Block::getBlockState<enum PrismarineBlockType>(class BlockState const &)const 
	enum SandType Block::getBlockState<enum SandType>(class BlockState const &)const 
	enum SaplingType Block::getBlockState<enum SaplingType>(class BlockState const &)const 
	enum SeaGrassType Block::getBlockState<enum SeaGrassType>(class BlockState const &)const 
	enum SpongeType Block::getBlockState<enum SpongeType>(class BlockState const &)const 
	enum StoneBrickType Block::getBlockState<enum StoneBrickType>(class BlockState const &)const 
	enum StoneSlabType2 Block::getBlockState<enum StoneSlabType2>(class BlockState const &)const 
	enum StoneSlabType3 Block::getBlockState<enum StoneSlabType3>(class BlockState const &)const 
	enum StoneSlabType4 Block::getBlockState<enum StoneSlabType4>(class BlockState const &)const 
	enum StoneSlabType Block::getBlockState<enum StoneSlabType>(class BlockState const &)const 
	enum StoneType Block::getBlockState<enum StoneType>(class BlockState const &)const 
	enum SweetBerryBushBlock::BerryStage Block::getBlockState<enum SweetBerryBushBlock::BerryStage>(class BlockState const &)const 
	enum TallGrassType Block::getBlockState<enum TallGrassType>(class BlockState const &)const 
	enum TorchFacing Block::getBlockState<enum TorchFacing>(class BlockState const &)const 
	enum WallBlockType Block::getBlockState<enum WallBlockType>(class BlockState const &)const 
	enum WoodType Block::getBlockState<enum WoodType>(class BlockState const &)const 
	bool Block::getBlockState<bool>(class BlockState const &)const 
	int Block::getBlockState<int>(class BlockState const &)const 
	unsigned char Block::getBlockState<unsigned char>(class BlockState const &)const 
	float Block::getThickness(void)const 
	bool Block::hasBlockState(class BlockState const &)const 
	class Block const & Block::keepBlockState(class BlockState const &)const 
	class Block const * Block::setBlockState<enum AnvilDamage>(class BlockState const &,enum AnvilDamage)const 
	class Block const * Block::setBlockState<enum AttachmentType>(class BlockState const &,enum AttachmentType)const 
	class Block const * Block::setBlockState<enum BlockColor>(class BlockState const &,enum BlockColor)const 
	class Block const * Block::setBlockState<enum ChiselType>(class BlockState const &,enum ChiselType)const 
	class Block const * Block::setBlockState<enum CoralColor>(class BlockState const &,enum CoralColor)const 
	class Block const * Block::setBlockState<enum Direction::Type>(class BlockState const &,enum Direction::Type)const 
	class Block const * Block::setBlockState<enum DirtType>(class BlockState const &,enum DirtType)const 
	class Block const * Block::setBlockState<enum DoublePlantType>(class BlockState const &,enum DoublePlantType)const 
	class Block const * Block::setBlockState<enum Facing::Name>(class BlockState const &,enum Facing::Name)const 
	class Block const * Block::setBlockState<enum FlowerType>(class BlockState const &,enum FlowerType)const 
	class Block const * Block::setBlockState<enum ItemColor>(class BlockState const &,enum ItemColor)const 
	class Block const * Block::setBlockState<enum ItemFrameBlock::ItemFrameDirection>(class BlockState const &,enum ItemFrameBlock::ItemFrameDirection)const 
	class Block const * Block::setBlockState<enum LeafSize>(class BlockState const &,enum LeafSize)const 
	class Block const * Block::setBlockState<enum MonsterEggStoneType>(class BlockState const &,enum MonsterEggStoneType)const 
	class Block const * Block::setBlockState<enum MushroomOuterType>(class BlockState const &,enum MushroomOuterType)const 
	class Block const * Block::setBlockState<enum NewLeafType>(class BlockState const &,enum NewLeafType)const 
	class Block const * Block::setBlockState<enum NewLogType>(class BlockState const &,enum NewLogType)const 
	class Block const * Block::setBlockState<enum OldLogType>(class BlockState const &,enum OldLogType)const 
	class Block const * Block::setBlockState<enum PrismarineBlockType>(class BlockState const &,enum PrismarineBlockType)const 
	class Block const * Block::setBlockState<enum SandStoneType>(class BlockState const &,enum SandStoneType)const 
	class Block const * Block::setBlockState<enum SaplingType>(class BlockState const &,enum SaplingType)const 
	class Block const * Block::setBlockState<enum SeaGrassType>(class BlockState const &,enum SeaGrassType)const 
	class Block const * Block::setBlockState<enum SpongeType>(class BlockState const &,enum SpongeType)const 
	class Block const * Block::setBlockState<enum StalkThickness>(class BlockState const &,enum StalkThickness)const 
	class Block const * Block::setBlockState<enum StoneBrickType>(class BlockState const &,enum StoneBrickType)const 
	class Block const * Block::setBlockState<enum StoneSlabType2>(class BlockState const &,enum StoneSlabType2)const 
	class Block const * Block::setBlockState<enum StoneSlabType3>(class BlockState const &,enum StoneSlabType3)const 
	class Block const * Block::setBlockState<enum StoneSlabType4>(class BlockState const &,enum StoneSlabType4)const 
	class Block const * Block::setBlockState<enum StoneSlabType>(class BlockState const &,enum StoneSlabType)const 
	class Block const * Block::setBlockState<enum StoneType>(class BlockState const &,enum StoneType)const 
	class Block const * Block::setBlockState<enum SweetBerryBushBlock::BerryStage>(class BlockState const &,enum SweetBerryBushBlock::BerryStage)const 
	class Block const * Block::setBlockState<enum TallGrassType>(class BlockState const &,enum TallGrassType)const 
	class Block const * Block::setBlockState<enum TorchFacing>(class BlockState const &,enum TorchFacing)const 
	class Block const * Block::setBlockState<enum TrapDoorBlock::TrapDoorDir>(class BlockState const &,enum TrapDoorBlock::TrapDoorDir)const 
	class Block const * Block::setBlockState<enum WallBlockType>(class BlockState const &,enum WallBlockType)const 
	class Block const * Block::setBlockState<enum WoodType>(class BlockState const &,enum WoodType)const 
	class Block const * Block::setBlockState<bool>(class BlockState const &,bool)const 
	class Block const * Block::setBlockState<int>(class BlockState const &,int)const 
	class Block const * Block::setBlockState<unsigned char>(class BlockState const &,unsigned char)const 

001.013.000.034_added.hpp
	enum AnvilDamage Block::getState<enum AnvilDamage>(class ItemState const &)const 
	enum AttachmentType Block::getState<enum AttachmentType>(class ItemState const &)const 
	enum ChiselType Block::getState<enum ChiselType>(class ItemState const &)const 
	enum LeverDirection Block::getState<enum LeverDirection>(class ItemState const &)const 
	enum NewLeafType Block::getState<enum NewLeafType>(class ItemState const &)const 
	enum NewLogType Block::getState<enum NewLogType>(class ItemState const &)const 
	enum PillarAxis Block::getState<enum PillarAxis>(class ItemState const &)const 
	enum PrismarineBlockType Block::getState<enum PrismarineBlockType>(class ItemState const &)const 
	enum WallBlockType Block::getState<enum WallBlockType>(class ItemState const &)const 
	class Block const * Block::setState<enum LeverDirection>(class ItemState const &,enum LeverDirection)const 
	class Block const * Block::setState<enum PillarAxis>(class ItemState const &,enum PillarAxis)const 

001.013.000.034_removed.hpp
	bool Block::liquidCanFlowIntoFromDirection(unsigned char,class std::function<class Block const & (class BlockPos const &)>,class BlockPos const &)const 
	class Block const * Block::setState<enum ItemFrameBlock::ItemFrameDirection>(class ItemState const &,enum ItemFrameBlock::ItemFrameDirection)const 

001.014.020.001_added.hpp
	bool Block::isSlabBlock(void)const 

001.016.000.002_added.hpp
	enum CreativeItemCategory Block::getCreativeCategory(void)const 
	class Block const & Block::getDefaultState(void)const 
	unsigned int Block::getStateMask(class ItemState const &)const 
	class gsl::not_null<class Block const *> Block::setState<enum AnvilDamage>(class ItemState const &,enum AnvilDamage)const 
	class gsl::not_null<class Block const *> Block::setState<enum AttachmentType>(class ItemState const &,enum AttachmentType)const 
	class gsl::not_null<class Block const *> Block::setState<enum BlockColor>(class ItemState const &,enum BlockColor)const 
	class gsl::not_null<class Block const *> Block::setState<enum ChiselType>(class ItemState const &,enum ChiselType)const 
	class gsl::not_null<class Block const *> Block::setState<enum CoralColor>(class ItemState const &,enum CoralColor)const 
	class gsl::not_null<class Block const *> Block::setState<enum CoralDirection>(class ItemState const &,enum CoralDirection)const 
	class gsl::not_null<class Block const *> Block::setState<enum Direction::Type>(class ItemState const &,enum Direction::Type)const 
	class gsl::not_null<class Block const *> Block::setState<enum DirtType>(class ItemState const &,enum DirtType)const 
	class gsl::not_null<class Block const *> Block::setState<enum DoublePlantType>(class ItemState const &,enum DoublePlantType)const 
	class gsl::not_null<class Block const *> Block::setState<enum Facing::Name>(class ItemState const &,enum Facing::Name)const 
	class gsl::not_null<class Block const *> Block::setState<enum Facing::Rotation>(class ItemState const &,enum Facing::Rotation)const 
	class gsl::not_null<class Block const *> Block::setState<enum FlowerType>(class ItemState const &,enum FlowerType)const 
	class gsl::not_null<class Block const *> Block::setState<enum ItemColor>(class ItemState const &,enum ItemColor)const 
	class gsl::not_null<class Block const *> Block::setState<enum LeafSize>(class ItemState const &,enum LeafSize)const 
	class gsl::not_null<class Block const *> Block::setState<enum LeverDirection>(class ItemState const &,enum LeverDirection)const 
	class gsl::not_null<class Block const *> Block::setState<enum MonsterEggStoneType>(class ItemState const &,enum MonsterEggStoneType)const 
	class gsl::not_null<class Block const *> Block::setState<enum MushroomOuterType>(class ItemState const &,enum MushroomOuterType)const 
	class gsl::not_null<class Block const *> Block::setState<enum PillarAxis>(class ItemState const &,enum PillarAxis)const 
	class gsl::not_null<class Block const *> Block::setState<enum PortalAxis>(class ItemState const &,enum PortalAxis)const 
	class gsl::not_null<class Block const *> Block::setState<enum PrismarineBlockType>(class ItemState const &,enum PrismarineBlockType)const 
	class gsl::not_null<class Block const *> Block::setState<enum RailDirection>(class ItemState const &,enum RailDirection)const 
	class gsl::not_null<class Block const *> Block::setState<enum SandStoneType>(class ItemState const &,enum SandStoneType)const 
	class gsl::not_null<class Block const *> Block::setState<enum SaplingType>(class ItemState const &,enum SaplingType)const 
	class gsl::not_null<class Block const *> Block::setState<enum SeaGrassType>(class ItemState const &,enum SeaGrassType)const 
	class gsl::not_null<class Block const *> Block::setState<enum SpongeType>(class ItemState const &,enum SpongeType)const 
	class gsl::not_null<class Block const *> Block::setState<enum StalkThickness>(class ItemState const &,enum StalkThickness)const 
	class gsl::not_null<class Block const *> Block::setState<enum StoneBrickType>(class ItemState const &,enum StoneBrickType)const 
	class gsl::not_null<class Block const *> Block::setState<enum StoneSlabType2>(class ItemState const &,enum StoneSlabType2)const 
	class gsl::not_null<class Block const *> Block::setState<enum StoneSlabType3>(class ItemState const &,enum StoneSlabType3)const 
	class gsl::not_null<class Block const *> Block::setState<enum StoneSlabType4>(class ItemState const &,enum StoneSlabType4)const 
	class gsl::not_null<class Block const *> Block::setState<enum StoneSlabType>(class ItemState const &,enum StoneSlabType)const 
	class gsl::not_null<class Block const *> Block::setState<enum StoneType>(class ItemState const &,enum StoneType)const 
	class gsl::not_null<class Block const *> Block::setState<enum SweetBerryBushBlock::BerryStage>(class ItemState const &,enum SweetBerryBushBlock::BerryStage)const 
	class gsl::not_null<class Block const *> Block::setState<enum TallGrassType>(class ItemState const &,enum TallGrassType)const 
	class gsl::not_null<class Block const *> Block::setState<enum TorchFacing>(class ItemState const &,enum TorchFacing)const 
	class gsl::not_null<class Block const *> Block::setState<enum TrapDoorBlock::TrapDoorDir>(class ItemState const &,enum TrapDoorBlock::TrapDoorDir)const 
	class gsl::not_null<class Block const *> Block::setState<enum WallBlockType>(class ItemState const &,enum WallBlockType)const 
	class gsl::not_null<class Block const *> Block::setState<enum WeirdoDirection>(class ItemState const &,enum WeirdoDirection)const 
	class gsl::not_null<class Block const *> Block::setState<enum WoodType>(class ItemState const &,enum WoodType)const 
	class gsl::not_null<class Block const *> Block::setState<bool>(class ItemState const &,bool)const 
	class gsl::not_null<class Block const *> Block::setState<int>(class ItemState const &,int)const 
	class gsl::not_null<class Block const *> Block::setState<unsigned char>(class ItemState const &,unsigned char)const 
	class gsl::not_null<class Block const *> Block::setState<unsigned short>(class ItemState const &,unsigned short)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,bool)const 

001.016.000.002_removed.hpp
	class BlockLegacy const & Block::getLegacyBlock(void)const 
	enum AnvilDamage Block::getState<enum AnvilDamage>(class ItemState const &)const 
	enum AttachmentType Block::getState<enum AttachmentType>(class ItemState const &)const 
	enum BlockColor Block::getState<enum BlockColor>(class ItemState const &)const 
	enum CauldronLiquidType Block::getState<enum CauldronLiquidType>(class ItemState const &)const 
	enum ChemistryTableType Block::getState<enum ChemistryTableType>(class ItemState const &)const 
	enum ChiselType Block::getState<enum ChiselType>(class ItemState const &)const 
	enum CoralColor Block::getState<enum CoralColor>(class ItemState const &)const 
	enum Direction::Type Block::getState<enum Direction::Type>(class ItemState const &)const 
	enum DirtType Block::getState<enum DirtType>(class ItemState const &)const 
	enum DoublePlantType Block::getState<enum DoublePlantType>(class ItemState const &)const 
	enum FlowerType Block::getState<enum FlowerType>(class ItemState const &)const 
	enum LeverDirection Block::getState<enum LeverDirection>(class ItemState const &)const 
	enum MonsterEggStoneType Block::getState<enum MonsterEggStoneType>(class ItemState const &)const 
	enum NewLeafType Block::getState<enum NewLeafType>(class ItemState const &)const 
	enum NewLogType Block::getState<enum NewLogType>(class ItemState const &)const 
	enum OldLeafType Block::getState<enum OldLeafType>(class ItemState const &)const 
	enum PillarAxis Block::getState<enum PillarAxis>(class ItemState const &)const 
	enum PortalAxis Block::getState<enum PortalAxis>(class ItemState const &)const 
	enum PrismarineBlockType Block::getState<enum PrismarineBlockType>(class ItemState const &)const 
	enum SandType Block::getState<enum SandType>(class ItemState const &)const 
	enum SaplingType Block::getState<enum SaplingType>(class ItemState const &)const 
	enum SeaGrassType Block::getState<enum SeaGrassType>(class ItemState const &)const 
	enum SpongeType Block::getState<enum SpongeType>(class ItemState const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(class ItemState const &)const 
	enum StoneSlabType2 Block::getState<enum StoneSlabType2>(class ItemState const &)const 
	enum StoneSlabType3 Block::getState<enum StoneSlabType3>(class ItemState const &)const 
	enum StoneSlabType4 Block::getState<enum StoneSlabType4>(class ItemState const &)const 
	enum StoneSlabType Block::getState<enum StoneSlabType>(class ItemState const &)const 
	enum StoneType Block::getState<enum StoneType>(class ItemState const &)const 
	enum SweetBerryBushBlock::BerryStage Block::getState<enum SweetBerryBushBlock::BerryStage>(class ItemState const &)const 
	enum TallGrassType Block::getState<enum TallGrassType>(class ItemState const &)const 
	enum TorchFacing Block::getState<enum TorchFacing>(class ItemState const &)const 
	enum WallBlockType Block::getState<enum WallBlockType>(class ItemState const &)const 
	enum WoodType Block::getState<enum WoodType>(class ItemState const &)const 
	bool Block::getState<bool>(class ItemState const &)const 
	int Block::getState<int>(class ItemState const &)const 
	unsigned char Block::getState<unsigned char>(class ItemState const &)const 
	bool Block::isSlabBlock(void)const 
	class Block const * Block::setState<enum AnvilDamage>(class ItemState const &,enum AnvilDamage)const 
	class Block const * Block::setState<enum AttachmentType>(class ItemState const &,enum AttachmentType)const 
	class Block const * Block::setState<enum BlockColor>(class ItemState const &,enum BlockColor)const 
	class Block const * Block::setState<enum ChiselType>(class ItemState const &,enum ChiselType)const 
	class Block const * Block::setState<enum CoralColor>(class ItemState const &,enum CoralColor)const 
	class Block const * Block::setState<enum Direction::Type>(class ItemState const &,enum Direction::Type)const 
	class Block const * Block::setState<enum DoublePlantType>(class ItemState const &,enum DoublePlantType)const 
	class Block const * Block::setState<enum Facing::Name>(class ItemState const &,enum Facing::Name)const 
	class Block const * Block::setState<enum FlowerType>(class ItemState const &,enum FlowerType)const 
	class Block const * Block::setState<enum ItemColor>(class ItemState const &,enum ItemColor)const 
	class Block const * Block::setState<enum LeafSize>(class ItemState const &,enum LeafSize)const 
	class Block const * Block::setState<enum LeverDirection>(class ItemState const &,enum LeverDirection)const 
	class Block const * Block::setState<enum MonsterEggStoneType>(class ItemState const &,enum MonsterEggStoneType)const 
	class Block const * Block::setState<enum MushroomOuterType>(class ItemState const &,enum MushroomOuterType)const 
	class Block const * Block::setState<enum NewLeafType>(class ItemState const &,enum NewLeafType)const 
	class Block const * Block::setState<enum NewLogType>(class ItemState const &,enum NewLogType)const 
	class Block const * Block::setState<enum OldLogType>(class ItemState const &,enum OldLogType)const 
	class Block const * Block::setState<enum PillarAxis>(class ItemState const &,enum PillarAxis)const 
	class Block const * Block::setState<enum PortalAxis>(class ItemState const &,enum PortalAxis)const 
	class Block const * Block::setState<enum PrismarineBlockType>(class ItemState const &,enum PrismarineBlockType)const 
	class Block const * Block::setState<enum SandStoneType>(class ItemState const &,enum SandStoneType)const 
	class Block const * Block::setState<enum SaplingType>(class ItemState const &,enum SaplingType)const 
	class Block const * Block::setState<enum SeaGrassType>(class ItemState const &,enum SeaGrassType)const 
	class Block const * Block::setState<enum SpongeType>(class ItemState const &,enum SpongeType)const 
	class Block const * Block::setState<enum StalkThickness>(class ItemState const &,enum StalkThickness)const 
	class Block const * Block::setState<enum StoneBrickType>(class ItemState const &,enum StoneBrickType)const 
	class Block const * Block::setState<enum StoneSlabType2>(class ItemState const &,enum StoneSlabType2)const 
	class Block const * Block::setState<enum StoneSlabType3>(class ItemState const &,enum StoneSlabType3)const 
	class Block const * Block::setState<enum StoneSlabType4>(class ItemState const &,enum StoneSlabType4)const 
	class Block const * Block::setState<enum StoneSlabType>(class ItemState const &,enum StoneSlabType)const 
	class Block const * Block::setState<enum StoneType>(class ItemState const &,enum StoneType)const 
	class Block const * Block::setState<enum SweetBerryBushBlock::BerryStage>(class ItemState const &,enum SweetBerryBushBlock::BerryStage)const 
	class Block const * Block::setState<enum TallGrassType>(class ItemState const &,enum TallGrassType)const 
	class Block const * Block::setState<enum TorchFacing>(class ItemState const &,enum TorchFacing)const 
	class Block const * Block::setState<enum TrapDoorBlock::TrapDoorDir>(class ItemState const &,enum TrapDoorBlock::TrapDoorDir)const 
	class Block const * Block::setState<enum WallBlockType>(class ItemState const &,enum WallBlockType)const 
	class Block const * Block::setState<enum WoodType>(class ItemState const &,enum WoodType)const 
	class Block const * Block::setState<bool>(class ItemState const &,bool)const 
	class Block const * Block::setState<int>(class ItemState const &,int)const 
	class Block const * Block::setState<unsigned char>(class ItemState const &,unsigned char)const 
	class Block const * Block::setState<unsigned short>(class ItemState const &,unsigned short)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,float,int)const 

001.016.001.002_added.hpp
	class BlockLegacy const & Block::getLegacyBlock(void)const 
	enum AnvilDamage Block::getState<enum AnvilDamage>(class ItemState const &)const 
	enum AttachmentType Block::getState<enum AttachmentType>(class ItemState const &)const 
	enum BlockColor Block::getState<enum BlockColor>(class ItemState const &)const 
	enum CauldronLiquidType Block::getState<enum CauldronLiquidType>(class ItemState const &)const 
	enum ChemistryTableType Block::getState<enum ChemistryTableType>(class ItemState const &)const 
	enum ChiselType Block::getState<enum ChiselType>(class ItemState const &)const 
	enum CoralColor Block::getState<enum CoralColor>(class ItemState const &)const 
	enum Direction::Type Block::getState<enum Direction::Type>(class ItemState const &)const 
	enum DirtType Block::getState<enum DirtType>(class ItemState const &)const 
	enum DoublePlantType Block::getState<enum DoublePlantType>(class ItemState const &)const 
	enum Facing::Name Block::getState<enum Facing::Name>(class ItemState const &)const 
	enum Facing::Rotation Block::getState<enum Facing::Rotation>(class ItemState const &)const 
	enum FlowerType Block::getState<enum FlowerType>(class ItemState const &)const 
	enum LeverDirection Block::getState<enum LeverDirection>(class ItemState const &)const 
	enum MonsterEggStoneType Block::getState<enum MonsterEggStoneType>(class ItemState const &)const 
	enum NewLeafType Block::getState<enum NewLeafType>(class ItemState const &)const 
	enum NewLogType Block::getState<enum NewLogType>(class ItemState const &)const 
	enum OldLeafType Block::getState<enum OldLeafType>(class ItemState const &)const 
	enum PillarAxis Block::getState<enum PillarAxis>(class ItemState const &)const 
	enum PortalAxis Block::getState<enum PortalAxis>(class ItemState const &)const 
	enum PrismarineBlockType Block::getState<enum PrismarineBlockType>(class ItemState const &)const 
	enum SandType Block::getState<enum SandType>(class ItemState const &)const 
	enum SaplingType Block::getState<enum SaplingType>(class ItemState const &)const 
	enum SeaGrassType Block::getState<enum SeaGrassType>(class ItemState const &)const 
	enum SpongeType Block::getState<enum SpongeType>(class ItemState const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(class ItemState const &)const 
	enum StoneSlabType2 Block::getState<enum StoneSlabType2>(class ItemState const &)const 
	enum StoneSlabType3 Block::getState<enum StoneSlabType3>(class ItemState const &)const 
	enum StoneSlabType4 Block::getState<enum StoneSlabType4>(class ItemState const &)const 
	enum StoneSlabType Block::getState<enum StoneSlabType>(class ItemState const &)const 
	enum StoneType Block::getState<enum StoneType>(class ItemState const &)const 
	enum SweetBerryBushBlock::BerryStage Block::getState<enum SweetBerryBushBlock::BerryStage>(class ItemState const &)const 
	enum TallGrassType Block::getState<enum TallGrassType>(class ItemState const &)const 
	enum TorchFacing Block::getState<enum TorchFacing>(class ItemState const &)const 
	enum WallBlockType Block::getState<enum WallBlockType>(class ItemState const &)const 
	enum WoodType Block::getState<enum WoodType>(class ItemState const &)const 
	bool Block::getState<bool>(class ItemState const &)const 
	int Block::getState<int>(class ItemState const &)const 
	unsigned char Block::getState<unsigned char>(class ItemState const &)const 

001.016.001.002_removed.hpp
	class Block const & Block::getDefaultState(void)const 
	unsigned int Block::getStateMask(class ItemState const &)const 

001.016.100.004_added.hpp
	bool Block::canSurvive(class BlockSource &,class BlockPos const &)const 
	bool Block::checkIsPathable(class Actor &,class BlockPos const &,class BlockPos const &)const 
	class HitResult Block::clip(class BlockSource &,class BlockPos const &,class Vec3 const &,class Vec3 const &,bool)const 
	class HitResult Block::clip(class BlockSource &,class BlockPos const &,class Vec3 const &,class Vec3 const &,bool,class AABB const &)const 
	void Block::destroy(class BlockSource &,class BlockPos const &,class Actor *)const 
	void Block::executeItemEvent(class ItemStackBase &,std::string const &,class BlockSource &,class BlockPos const &,class Actor *)const 
	class AABB const & Block::getAABB(class BlockSource &,class BlockPos const &,class AABB &,bool)const 
	std::string Block::getDescriptionId(void)const 
	float Block::getDestroySpeed(void)const 
	float Block::getFriction(void)const 
	std::string Block::getFullName(void)const 
	struct Brightness Block::getLight(void)const 
	struct Brightness Block::getLightEmission(void)const 
	class Color Block::getMapColor(class BlockSource &,class BlockPos const &)const 
	enum OldLogType Block::getState<enum OldLogType>(class ItemState const &)const 
	bool Block::getState<bool>(unsigned __int64 const &)const 
	int Block::getState<int>(unsigned __int64 const &)const 
	unsigned short Block::getState<unsigned short>(class ItemState const &)const 
	enum WallConnectionType Block::getStateOrDefault<enum WallConnectionType>(class ItemState const &,enum WallConnectionType const &)const 
	int Block::getStateOrDefault<int>(class ItemState const &,int const &)const 
	float Block::getThickness(void)const 
	bool Block::hasProperty(enum BlockProperty)const 
	bool Block::hasTag(class HashedString const &)const 
	bool Block::hasTag(unsigned __int64 const &)const 
	bool Block::isCropBlock(void)const 
	bool Block::isDoorBlock(void)const 
	bool Block::isMotionBlockingBlock(void)const 
	bool Block::isSlabBlock(void)const 
	bool Block::isSolid(void)const 
	bool Block::isStandingSign(void)const 
	bool Block::mayPlace(class BlockSource &,class BlockPos const &,unsigned char)const 
	void Block::neighborChanged(class BlockSource &,class BlockPos const &,class BlockPos const &)const 
	void Block::onFallOn(class BlockSource &,class BlockPos const &,class Actor &,float)const 
	void Block::onPlace(class BlockSource &,class BlockPos const &,class Block const &)const 
	void Block::onPlayerPlacing(class BlockSource &,class BlockPos const &,class Actor &,unsigned char)const 
	void Block::onStepOff(class Actor &,class BlockPos const &)const 
	void Block::onStepOn(class Actor &,class BlockPos const &)const 
	bool Block::operator!=(class Block const &)const 
	bool Block::operator==(class Block const &)const 
	void Block::playerDestroy(class Player &,class BlockPos const &)const 
	void Block::queuedTick(class BlockSource &,class BlockPos const &,class Random &)const 
	void Block::randomTick(class BlockSource &,class BlockPos const &,class Random &)const 
	class gsl::not_null<class Block const *> Block::setState<enum NewLeafType>(class ItemState const &,enum NewLeafType)const 
	class gsl::not_null<class Block const *> Block::setState<enum NewLogType>(class ItemState const &,enum NewLogType)const 
	class gsl::not_null<class Block const *> Block::setState<enum OldLogType>(class ItemState const &,enum OldLogType)const 
	class gsl::not_null<class Block const *> Block::setState<enum WallConnectionType>(class ItemState const &,enum WallConnectionType)const 
	bool Block::shouldRandomTick(void)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,bool)const 
	void Block::tickInternal(class BlockSource &,class BlockPos const &,class Random &)const 
	struct BlockBakedMaterialDataComponent const * Block::tryGetComponent<struct BlockBakedMaterialDataComponent>(void)const 
	struct BlockBreathabilityComponent const * Block::tryGetComponent<struct BlockBreathabilityComponent>(void)const 
	struct BlockCollisionComponent const * Block::tryGetComponent<struct BlockCollisionComponent>(void)const 
	struct BlockFlammableComponent const * Block::tryGetComponent<struct BlockFlammableComponent>(void)const 
	struct BlockMapColorComponent const * Block::tryGetComponent<struct BlockMapColorComponent>(void)const 
	struct BlockMaterialInstancesComponent const * Block::tryGetComponent<struct BlockMaterialInstancesComponent>(void)const 
	struct BlockPlacementFilterComponent const * Block::tryGetComponent<struct BlockPlacementFilterComponent>(void)const 
	struct BlockQueuedTickingComponent const * Block::tryGetComponent<struct BlockQueuedTickingComponent>(void)const 
	struct BlockRandomTickingComponent const * Block::tryGetComponent<struct BlockRandomTickingComponent>(void)const 
	struct BlockRaycastComponent const * Block::tryGetComponent<struct BlockRaycastComponent>(void)const 
	struct BlockRotationComponent const * Block::tryGetComponent<struct BlockRotationComponent>(void)const 
	struct BlockUnitCubeComponent const * Block::tryGetComponent<struct BlockUnitCubeComponent>(void)const 
	struct CraftingTableComponent const * Block::tryGetComponent<struct CraftingTableComponent>(void)const 
	struct OnInteractTrigger const * Block::tryGetComponent<struct OnInteractTrigger>(void)const 
	struct OnPlayerPlacingTrigger const * Block::tryGetComponent<struct OnPlayerPlacingTrigger>(void)const 
	bool Block::use(class Player &,class BlockPos const &,unsigned char)const 

001.016.200.002_added.hpp
	class ItemState const * Block::getBlockState(class HashedString const &)const 
	class mce::Color Block::getMapColor(class BlockSource &,class BlockPos const &)const 
	class HashedString const & Block::getName(void)const 
	bool Block::onFertilized(class BlockSource &,class BlockPos const &,class Actor *,enum FertilizerType)const 

001.016.200.002_removed.hpp
	std::string Block::getFullName(void)const 
	class Color Block::getMapColor(class BlockSource &,class BlockPos const &)const 

001.016.210.005_added.hpp
	Block::Block(unsigned short,class gsl::not_null<class BlockLegacy *>,class CompoundTag,unsigned int const &)
	static float const Block::SIZE_OFFSET
	void Block::addAABBs(class BlockSource &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &)const 
	bool Block::addCollisionShapes(class BlockSource &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &,class Actor *)const 
	class Block & Block::addTag(class HashedString const &)
	void Block::animateTick(class BlockSource &,class BlockPos const &,class Random &)const 
	class ItemInstance Block::asItemInstance(class BlockSource &,class BlockPos const &)const 
	bool Block::attack(class Player *,class BlockPos const &)const 
	bool Block::breaksFallingBlocks(void)const 
	std::string Block::buildDescriptionId(void)const 
	std::string Block::buildDescriptionName(void)const 
	float Block::calcGroundFriction(class Mob &,class BlockPos const &)const 
	bool Block::canBeBrokenFromFalling(void)const 
	bool Block::canBeBuiltOver(class BlockSource &,class BlockPos const &)const 
	bool Block::canBeFertilized(class BlockSource &,class BlockPos const &,class Block const &)const 
	bool Block::canBeOriginalSurface(void)const 
	bool Block::canConnect(class Block const &,unsigned char,class Block const &)const 
	bool Block::canHurtAndBreakItem(void)const 
	bool Block::canInstatick(void)const 
	bool Block::canProvideSupport(unsigned char,enum BlockSupportType)const 
	bool Block::canSlide(class BlockSource &,class BlockPos const &)const 
	bool Block::causesFreezeEffect(class Actor const &)const 
	bool Block::dealsContactDamage(class Actor const &,bool)const 
	void Block::entityInside(class BlockSource &,class BlockPos const &,class Actor &)const 
	void Block::executeEvent(std::string const &,class RenderParams &)const 
	bool Block::executeTrigger(class DefinitionTrigger const &,class RenderParams &)const 
	bool Block::getAllowsRunes(void)const 
	enum BlockActorType Block::getBlockEntityType(void)const 
	int Block::getBurnOdds(void)const 
	bool Block::getCollisionShape(class AABB &,class BlockSource &,class BlockPos const &,class Actor *)const 
	int Block::getColor(class BlockSource &,class BlockPos const &)const 
	int Block::getColor(void)const 
	int Block::getComparatorSignal(class BlockSource &,class BlockPos const &,unsigned char)const 
	void Block::getDebugText(class std::vector<std::string,class std::allocator<std::string > > &,class BlockPos const &)const 
	int Block::getDirectSignal(class BlockSource &,class BlockPos const &,int)const 
	float Block::getExplosionResistance(class Actor *)const 
	int Block::getFlameOdds(void)const 
	bool Block::getIgnoresDestroyPermissions(class Actor &,class BlockPos const &)const 
	class Material const & Block::getMaterial(void)const 
	class MobSpawnerData const * Block::getMobToSpawn(class SpawnConditions const &,class BlockSource &)const 
	class Block const & Block::getPlacementBlock(class Actor &,class BlockPos const &,unsigned char,class Vec3 const &,int)const 
	unsigned int const & Block::getRuntimeId(void)const 
	bool Block::getSecondPart(class BlockSource &,class BlockPos const &,class BlockPos &)const 
	class CompoundTag const & Block::getSerializationId(void)const 
	class ItemInstance Block::getSilkTouchItemInstance(void)const 
	float Block::getTranslucency(void)const 
	int Block::getVariant(void)const 
	class AABB const & Block::getVisualShape(class AABB &,bool)const 
	class AABB const & Block::getVisualShapeInWorld(class BlockSource &,class BlockPos const &,class AABB &,bool)const 
	void Block::handleEntityInside(class BlockSource &,class BlockPos const &,class Actor *,class Vec3 &)const 
	bool Block::hasBlockEntity(void)const 
	bool Block::hasComparatorSignal(void)const 
	bool const Block::hasRuntimeId(void)const 
	bool Block::ignoreEntitiesOnPistonMove(void)const 
	void Block::initEntity(class EntityRegistryOwned &)
	void Block::initParams(class RenderParams &,class BlockSource &,class BlockPos const &,class Actor *)const 
	bool Block::isAttachedTo(class BlockSource &,class BlockPos const &,class BlockPos &)const 
	bool Block::isAuxValueRelevantForPicking(void)const 
	bool Block::isBounceBlock(void)const 
	bool Block::isButtonBlock(void)const 
	bool Block::isClimbable(class Actor const &)const 
	bool Block::isContainerBlock(void)const 
	bool Block::isFenceBlock(void)const 
	bool Block::isHeavy(void)const 
	bool Block::isInteractiveBlock(void)const 
	bool Block::isObstructingChests(class BlockSource &,class BlockPos const &)const 
	bool Block::isRailBlock(void)const 
	bool Block::isSignalSource(void)const 
	bool Block::isStairBlock(void)const 
	bool Block::isStemBlock(void)const 
	bool Block::isThinFenceBlock(void)const 
	bool Block::isWallBlock(void)const 
	bool Block::isWaterBlocking(void)const 
	bool Block::mayConsumeFertilizer(class BlockSource &)const 
	bool Block::mayPick(class BlockSource &,bool)const 
	bool Block::mayPick(void)const 
	bool Block::mayPlace(class BlockSource &,class BlockPos const &)const 
	bool Block::mayPlaceOn(class BlockSource &,class BlockPos const &)const 
	void Block::movedByPiston(class BlockSource &,class BlockPos const &)const 
	void Block::onExploded(class BlockSource &,class BlockPos const &,class Actor *)const 
	void Block::onLightningHit(class BlockSource &,class BlockPos const &)const 
	void Block::onProjectileHit(class BlockSource &,class BlockPos const &,class Actor const &)const 
	void Block::onRemove(class BlockSource &,class BlockPos const &)const 
	void Block::onStandOn(class Actor &,class BlockPos const &)const 
	void Block::onStructureBlockPlace(class BlockSource &,class BlockPos const &)const 
	void Block::onStructureNeighborBlockPlace(class BlockSource &,class BlockPos const &)const 
	bool Block::playerWillDestroy(class Player &,class BlockPos const &)const 
	class ItemActor * Block::popResource(class BlockSource &,class BlockPos const &,class ItemInstance const &)const 
	bool Block::pushesOutItems(void)const 
	bool Block::pushesUpFallingBlocks(void)const 
	class Vec3 Block::randomlyModifyPosition(class BlockPos const &)const 
	void Block::setRuntimeId(unsigned int const &)const 
	bool Block::shouldRandomTickExtraLayer(void)const 
	bool Block::shouldStopFalling(class Actor &)const 
	int Block::telemetryVariant(class BlockSource &,class BlockPos const &)const 
	void Block::transformOnFall(class BlockSource &,class BlockPos const &,class Actor *,float)const 
	void Block::triggerEvent(class BlockSource &,class BlockPos const &,int,int)const 
	void Block::trySpawnResourcesOnExplosion(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,bool)const 
	bool Block::tryToPlace(class BlockSource &,class BlockPos const &,struct ActorBlockSyncMessage const *)const 
	void Block::updateEntityAfterFallOn(class BlockPos const &,struct IActorMovementProxy &)const 

001.016.210.005_removed.hpp
	class ItemState const * Block::getBlockState(class HashedString const &)const 
	class BlockLegacy const & Block::getLegacyBlock(void)const 
	enum Facing::Name Block::getState<enum Facing::Name>(class ItemState const &)const 
	enum FlowerType Block::getState<enum FlowerType>(class ItemState const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(class ItemState const &)const 
	bool Block::getState<bool>(unsigned __int64 const &)const 
	int Block::getState<int>(unsigned __int64 const &)const 
	int Block::getStateOrDefault<int>(class ItemState const &,int const &)const 
	class gsl::not_null<class Block const *> Block::setState<enum DirtType>(class ItemState const &,enum DirtType)const 
	class gsl::not_null<class Block const *> Block::setState<enum NewLeafType>(class ItemState const &,enum NewLeafType)const 
	struct BlockBakedMaterialDataComponent const * Block::tryGetComponent<struct BlockBakedMaterialDataComponent>(void)const 
	struct BlockBreathabilityComponent const * Block::tryGetComponent<struct BlockBreathabilityComponent>(void)const 
	struct BlockRotationComponent const * Block::tryGetComponent<struct BlockRotationComponent>(void)const 
	struct BlockUnitCubeComponent const * Block::tryGetComponent<struct BlockUnitCubeComponent>(void)const 
	struct OnPlayerPlacingTrigger const * Block::tryGetComponent<struct OnPlayerPlacingTrigger>(void)const 

001.016.220.002_added.hpp
	bool Block::isLeverBlock(void)const 
	class Block const * Block::trySetState<int>(class ItemState const &,int)const 

001.017.000.003_added.hpp
	bool Block::_isSolid(void)const 
	void Block::cacheComponentData(void)
	bool Block::causesFreezeEffect(void)const 
	class Block const & Block::getDefaultState(void)const 
	enum BigDripleafTilt Block::getState<enum BigDripleafTilt>(class ItemState const &)const 
	enum DripstoneThickness Block::getState<enum DripstoneThickness>(class ItemState const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(class ItemState const &)const 
	class gsl::not_null<class Block const *> Block::setState<enum DripstoneThickness>(class ItemState const &,enum DripstoneThickness)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,bool,class ItemStack const &)const 
	class CopperBehavior const * Block::tryGetCopperBehavior(void)const 
	class Block const * Block::tryGetInfested(void)const 
	class Block const * Block::tryGetUninfested(void)const 
	bool Block::tryToTill(class BlockSource &,class BlockPos const &,class Actor &,class ItemStack &)const 

001.017.000.003_removed.hpp
	bool Block::causesFreezeEffect(class Actor const &)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,bool)const 
	void Block::tickInternal(class BlockSource &,class BlockPos const &,class Random &)const 

001.017.010.004_added.hpp
	enum CandleCount Block::getState<enum CandleCount>(class ItemState const &)const 
	bool Block::isFenceGateBlock(void)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Block const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,class ItemStack const &)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int)const 
	void Block::trySpawnResourcesOnExplosion(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int)const 

001.017.010.004_removed.hpp
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,bool,class ItemStack const &)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,bool)const 
	class Block const * Block::trySetState<int>(class ItemState const &,int)const 
	void Block::trySpawnResourcesOnExplosion(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,bool)const 

001.017.030.004_added.hpp
	bool Block::addCollisionShapes(class BlockSource &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &,class optional_ref<struct IActorMovementProxy>)const 
	bool Block::breaksFallingBlocks(class BaseGameVersion)const 
	float Block::calcGroundFriction(struct IMobMovementProxy const &,class BlockPos const &)const 
	class HitResult Block::clip(class BlockSource const &,class BlockPos const &,class Vec3 const &,class Vec3 const &,bool)const 
	class HitResult Block::clip(class BlockSource const &,class BlockPos const &,class Vec3 const &,class Vec3 const &,bool,class AABB const &)const 
	class AABB const & Block::getAABB(class BlockSource const &,class BlockPos const &,class AABB &,bool)const 
	bool Block::getCollisionShape(class AABB &,class BlockSource &,class BlockPos const &,class optional_ref<struct IActorMovementProxy>)const 
	void Block::getConnectedDirections(class BlockPos const &,class BlockSource &,bool &,bool &,bool &,bool &)const 
	class gsl::basic_string_span<char const,-1> Block::getCreativeGroup(void)const 
	class BlockLegacy const & Block::getLegacyBlock(void)const 
	bool Block::getSecondPart(class BlockSource const &,class BlockPos const &,class BlockPos &)const 
	struct Brightness Block::getState<struct Brightness>(class ItemState const &)const 
	bool Block::isClimbable(struct IActorMovementProxy const &)const 
	bool Block::isFilteredOut(enum BlockRenderLayer)const 
	bool Block::mayPick(class BlockSource const &,bool)const 
	struct BlockCreativeGroupComponent const * Block::tryGetComponent<struct BlockCreativeGroupComponent>(void)const 
	class Block const * Block::trySetState<int>(class ItemState const &,int)const 

001.017.030.004_removed.hpp
	bool Block::addCollisionShapes(class BlockSource &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &,class Actor *)const 
	bool Block::breaksFallingBlocks(void)const 
	float Block::calcGroundFriction(class Mob &,class BlockPos const &)const 
	class HitResult Block::clip(class BlockSource &,class BlockPos const &,class Vec3 const &,class Vec3 const &,bool)const 
	class HitResult Block::clip(class BlockSource &,class BlockPos const &,class Vec3 const &,class Vec3 const &,bool,class AABB const &)const 
	class AABB const & Block::getAABB(class BlockSource &,class BlockPos const &,class AABB &,bool)const 
	bool Block::getCollisionShape(class AABB &,class BlockSource &,class BlockPos const &,class Actor *)const 
	bool Block::getSecondPart(class BlockSource &,class BlockPos const &,class BlockPos &)const 
	bool Block::isClimbable(class Actor const &)const 
	bool Block::mayPick(class BlockSource &,bool)const 

001.017.040.006_added.hpp
	bool Block::isPartialBlock(class BlockSource const &,class BlockPos const &)const 
	bool Block::isTopPartialBlock(class BlockSource const &,class BlockPos const &)const 

001.018.000.002_added.hpp
	int Block::getResourceCount(class Randomize &,int)const 
	bool Block::isPreservingMediumWhenPlaced(class Block const &)const 

001.018.011.001_added.hpp
	void Block::_tryInitEntityIfNotInitialized(void)
	bool Block::canBeBuiltOver(class BlockSource &,class BlockPos const &,class BlockItem const &)const 
	bool Block::canHaveExtraData(void)const 
	void Block::initEntity(class EntityRegistry &)
	bool Block::isUnbreakable(void)const 
	void Block::onStandOn(class EntityContext &,class BlockPos const &)const 
	struct BlockAimCollisionComponent const * Block::tryGetComponent<struct BlockAimCollisionComponent>(void)const 
	bool Block::updateTallestCollisionShape(class BlockSource &,class BlockPos const &,class AABB const &,class optional_ref<struct IActorMovementProxy>,class AABB &,class Vec3 const &,float &)const 
	void RapidJsonDataFixers::Block::applyLambdaToComponentInBlockSection(class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &,std::string const &,class std::function<void (class rapidjson::GenericMemberIterator<0,struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> >)> const &)
	bool RapidJsonDataFixers::Block::applyLambdaToComponentObject(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,class std::function<void (class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &)> const &)
	void RapidJsonDataFixers::Block::removeComponentField(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,std::string const &)
	void RapidJsonDataFixers::Block::renameComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,std::string const &)

001.018.011.001_removed.hpp
	void Block::initEntity(class EntityRegistryOwned &)
	void Block::onStandOn(class Actor &,class BlockPos const &)const 
	struct BlockRaycastComponent const * Block::tryGetComponent<struct BlockRaycastComponent>(void)const 

001.018.030.004_added.hpp
	bool Block::addCollisionShapes(class BlockSource &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &,class optional_ref<class GetCollisionShapeInterface const>)const 
	bool Block::canProvideFullSupport(unsigned char)const 
	bool Block::canProvideMultifaceSupport(unsigned char)const 
	class AABB const & Block::getAABB(class IConstBlockSource const &,class BlockPos const &,class AABB &,bool)const 
	bool Block::getCollisionShape(class AABB &,class IConstBlockSource const &,class BlockPos const &,class optional_ref<class GetCollisionShapeInterface const>)const 
	bool Block::isEmpty(void)const 
	bool Block::isMultifaceBlock(void)const 
	bool Block::isSculkReplaceable(class Block const &)const 
	bool Block::isVibrationBlocking(void)const 
	bool Block::updateTallestCollisionShape(class BlockSource &,class BlockPos const &,class AABB const &,class optional_ref<class GetCollisionShapeInterface const>,class AABB &,class Vec3 const &,float &)const 

001.018.030.004_removed.hpp
	bool Block::_isSolid(void)const 
	bool Block::addCollisionShapes(class BlockSource &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &,class optional_ref<struct IActorMovementProxy>)const 
	class AABB const & Block::getAABB(class BlockSource const &,class BlockPos const &,class AABB &,bool)const 
	bool Block::getCollisionShape(class AABB &,class BlockSource &,class BlockPos const &,class optional_ref<struct IActorMovementProxy>)const 
	bool Block::updateTallestCollisionShape(class BlockSource &,class BlockPos const &,class AABB const &,class optional_ref<struct IActorMovementProxy>,class AABB &,class Vec3 const &,float &)const 

001.018.032.002_added.hpp
	Block::Block(unsigned short,class gsl::not_null<class BlockLegacy *>)

001.018.032.002_removed.hpp
	enum PillarAxis Block::getState<enum PillarAxis>(class ItemState const &)const 
	unsigned short Block::getState<unsigned short>(class ItemState const &)const 
	class Block const * Block::trySetState<int>(class ItemState const &,int)const 

001.019.001.001_added.hpp
	bool Block::_isSolid(void)const 
	class BlockTypeRegistryReadLock Block::_lockRegistryForRead(void)const 
	void Block::addAABBs(class BlockSource const &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &)const 
	bool Block::addCollisionShapes(class BlockSource const &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &,class optional_ref<class GetCollisionShapeInterface const>)const 
	bool Block::canDamperVibrations(void)const 
	bool Block::canOccludeVibrations(void)const 
	class EntityContext const & Block::getEntity(void)const 
	class EntityContext & Block::getEntityForModification(void)const 
	bool Block::hasPropertyNoLock(enum BlockProperty)const 
	class gsl::not_null<class Block const *> Block::setState<enum BigDripleafTilt>(class ItemState const &,enum BigDripleafTilt)const 
	struct BlockCraftingTableComponent const * Block::tryGetComponent<struct BlockCraftingTableComponent>(void)const 
	class OnInteractTrigger const * Block::tryGetComponent<class OnInteractTrigger>(void)const 
	struct BlockMaterialInstancesComponent const * Block::tryGetComponentNoLock<struct BlockMaterialInstancesComponent>(void)const 
	void Block::updateEntityAfterFallOn(class BlockPos const &,struct UpdateEntityAfterFallOnInterface &)const 
	bool Block::updateTallestCollisionShape(class BlockSource const &,class BlockPos const &,class AABB const &,class optional_ref<class GetCollisionShapeInterface const>,class AABB &,class Vec3 const &,float &)const 

001.019.001.001_removed.hpp
	void Block::addAABBs(class BlockSource &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &)const 
	bool Block::addCollisionShapes(class BlockSource &,class BlockPos const &,class AABB const *,class std::vector<class AABB,class std::allocator<class AABB> > &,class optional_ref<class GetCollisionShapeInterface const>)const 
	void Block::handleEntityInside(class BlockSource &,class BlockPos const &,class Actor *,class Vec3 &)const 
	bool Block::isSculkReplaceable(class Block const &)const 
	bool Block::isVibrationBlocking(void)const 
	struct BlockMaterialInstancesComponent const * Block::tryGetComponent<struct BlockMaterialInstancesComponent>(void)const 
	struct CraftingTableComponent const * Block::tryGetComponent<struct CraftingTableComponent>(void)const 
	struct OnInteractTrigger const * Block::tryGetComponent<struct OnInteractTrigger>(void)const 
	void Block::updateEntityAfterFallOn(class BlockPos const &,struct IActorMovementProxy &)const 
	bool Block::updateTallestCollisionShape(class BlockSource &,class BlockPos const &,class AABB const &,class optional_ref<class GetCollisionShapeInterface const>,class AABB &,class Vec3 const &,float &)const 

001.019.010.003_added.hpp
	class EntityContext const & Block::getEntity(void)const 
	bool Block::isAir(void)const 
	struct BlockCollisionBoxComponent const * Block::tryGetComponent<struct BlockCollisionBoxComponent>(void)const 
	void RapidJsonDataFixers::Block::applyLambdaToComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,class std::function<void (class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &)> const &)
	void RapidJsonDataFixers::Block::renameComponentField(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,std::string const &,std::string const &)
	void RapidJsonDataFixers::Block::replaceComponentObjectWithFieldValue(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,std::string const &)

001.019.010.003_removed.hpp
	class EntityContext const & Block::getEntity(void)const 
	bool Block::operator!=(class Block const &)const 
	bool Block::operator==(class Block const &)const 
	struct BlockCollisionComponent const * Block::tryGetComponent<struct BlockCollisionComponent>(void)const 

001.019.010.020_added.hpp
	class EntityContext const & Block::getEntity(void)const 
	enum AnvilDamage Block::getState<enum AnvilDamage>(unsigned __int64 const &)const 
	enum AttachmentType Block::getState<enum AttachmentType>(unsigned __int64 const &)const 
	enum BigDripleafTilt Block::getState<enum BigDripleafTilt>(unsigned __int64 const &)const 
	enum BlockColor Block::getState<enum BlockColor>(unsigned __int64 const &)const 
	enum CandleCount Block::getState<enum CandleCount>(unsigned __int64 const &)const 
	enum CauldronLiquidType Block::getState<enum CauldronLiquidType>(unsigned __int64 const &)const 
	enum ChemistryTableType Block::getState<enum ChemistryTableType>(unsigned __int64 const &)const 
	enum ChiselType Block::getState<enum ChiselType>(unsigned __int64 const &)const 
	enum CoralColor Block::getState<enum CoralColor>(unsigned __int64 const &)const 
	enum CoralDirection Block::getState<enum CoralDirection>(unsigned __int64 const &)const 
	enum Direction::Type Block::getState<enum Direction::Type>(unsigned __int64 const &)const 
	enum DirtType Block::getState<enum DirtType>(unsigned __int64 const &)const 
	enum DoublePlantType Block::getState<enum DoublePlantType>(unsigned __int64 const &)const 
	enum DripstoneThickness Block::getState<enum DripstoneThickness>(unsigned __int64 const &)const 
	enum Facing::Name Block::getState<enum Facing::Name>(unsigned __int64 const &)const 
	enum Facing::Rotation Block::getState<enum Facing::Rotation>(unsigned __int64 const &)const 
	enum FlowerType Block::getState<enum FlowerType>(unsigned __int64 const &)const 
	enum LeafSize Block::getState<enum LeafSize>(unsigned __int64 const &)const 
	enum LeverDirection Block::getState<enum LeverDirection>(unsigned __int64 const &)const 
	enum MonsterEggStoneType Block::getState<enum MonsterEggStoneType>(unsigned __int64 const &)const 
	enum MushroomOuterType Block::getState<enum MushroomOuterType>(unsigned __int64 const &)const 
	enum NewLeafType Block::getState<enum NewLeafType>(unsigned __int64 const &)const 
	enum NewLogType Block::getState<enum NewLogType>(unsigned __int64 const &)const 
	enum OldLeafType Block::getState<enum OldLeafType>(unsigned __int64 const &)const 
	enum OldLogType Block::getState<enum OldLogType>(unsigned __int64 const &)const 
	enum PillarAxis Block::getState<enum PillarAxis>(unsigned __int64 const &)const 
	enum PortalAxis Block::getState<enum PortalAxis>(unsigned __int64 const &)const 
	enum PrismarineBlockType Block::getState<enum PrismarineBlockType>(unsigned __int64 const &)const 
	enum RailDirection Block::getState<enum RailDirection>(unsigned __int64 const &)const 
	enum SandType Block::getState<enum SandType>(unsigned __int64 const &)const 
	enum SaplingType Block::getState<enum SaplingType>(unsigned __int64 const &)const 
	enum SeaGrassType Block::getState<enum SeaGrassType>(unsigned __int64 const &)const 
	enum SeaPickleCount Block::getState<enum SeaPickleCount>(unsigned __int64 const &)const 
	enum SpongeType Block::getState<enum SpongeType>(unsigned __int64 const &)const 
	enum StalkThickness Block::getState<enum StalkThickness>(unsigned __int64 const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(unsigned __int64 const &)const 
	enum StoneSlabType2 Block::getState<enum StoneSlabType2>(unsigned __int64 const &)const 
	enum StoneSlabType3 Block::getState<enum StoneSlabType3>(unsigned __int64 const &)const 
	enum StoneSlabType4 Block::getState<enum StoneSlabType4>(unsigned __int64 const &)const 
	enum StoneSlabType Block::getState<enum StoneSlabType>(unsigned __int64 const &)const 
	enum StoneType Block::getState<enum StoneType>(unsigned __int64 const &)const 
	enum SweetBerryBushBlock::BerryStage Block::getState<enum SweetBerryBushBlock::BerryStage>(unsigned __int64 const &)const 
	enum TallGrassType Block::getState<enum TallGrassType>(unsigned __int64 const &)const 
	enum TorchFacing Block::getState<enum TorchFacing>(unsigned __int64 const &)const 
	enum TrapDoorBlock::TrapDoorDir Block::getState<enum TrapDoorBlock::TrapDoorDir>(unsigned __int64 const &)const 
	enum WallBlockType Block::getState<enum WallBlockType>(unsigned __int64 const &)const 
	enum WallConnectionType Block::getState<enum WallConnectionType>(unsigned __int64 const &)const 
	enum WeirdoDirection Block::getState<enum WeirdoDirection>(unsigned __int64 const &)const 
	enum WoodType Block::getState<enum WoodType>(unsigned __int64 const &)const 
	int Block::getState<int>(unsigned __int64 const &)const 
	unsigned char Block::getState<unsigned char>(unsigned __int64 const &)const 
	unsigned short Block::getState<unsigned short>(unsigned __int64 const &)const 
	unsigned int Block::getStateMask(class ItemState const &)const 
	bool Block::getStateOrDefault<bool>(class ItemState const &,bool const &)const 
	bool Block::operator!=(class Block const &)const 
	bool Block::operator==(class Block const &)const 
	class gsl::not_null<class Block const *> Block::setState<enum CauldronLiquidType>(class ItemState const &,enum CauldronLiquidType)const 
	class gsl::not_null<class Block const *> Block::setState<enum ChemistryTableType>(class ItemState const &,enum ChemistryTableType)const 
	class gsl::not_null<class Block const *> Block::setState<enum DirtType>(class ItemState const &,enum DirtType)const 
	class gsl::not_null<class Block const *> Block::setState<enum NewLeafType>(class ItemState const &,enum NewLeafType)const 
	class gsl::not_null<class Block const *> Block::setState<enum SandType>(class ItemState const &,enum SandType)const 
	class gsl::not_null<class Block const *> Block::setState<unsigned int>(class ItemState const &,unsigned int)const 
	class Block const * Block::trySetState<int>(class ItemState const &,int)const 

001.019.010.020_removed.hpp
	class EntityContext const & Block::getEntity(void)const 
	enum AnvilDamage Block::getState<enum AnvilDamage>(class ItemState const &)const 
	enum AttachmentType Block::getState<enum AttachmentType>(class ItemState const &)const 
	enum BigDripleafTilt Block::getState<enum BigDripleafTilt>(class ItemState const &)const 
	enum BlockColor Block::getState<enum BlockColor>(class ItemState const &)const 
	struct Brightness Block::getState<struct Brightness>(class ItemState const &)const 
	enum CandleCount Block::getState<enum CandleCount>(class ItemState const &)const 
	enum CauldronLiquidType Block::getState<enum CauldronLiquidType>(class ItemState const &)const 
	enum ChemistryTableType Block::getState<enum ChemistryTableType>(class ItemState const &)const 
	enum ChiselType Block::getState<enum ChiselType>(class ItemState const &)const 
	enum CoralColor Block::getState<enum CoralColor>(class ItemState const &)const 
	enum Direction::Type Block::getState<enum Direction::Type>(class ItemState const &)const 
	enum DirtType Block::getState<enum DirtType>(class ItemState const &)const 
	enum DoublePlantType Block::getState<enum DoublePlantType>(class ItemState const &)const 
	enum DripstoneThickness Block::getState<enum DripstoneThickness>(class ItemState const &)const 
	enum Facing::Rotation Block::getState<enum Facing::Rotation>(class ItemState const &)const 
	enum LeverDirection Block::getState<enum LeverDirection>(class ItemState const &)const 
	enum MonsterEggStoneType Block::getState<enum MonsterEggStoneType>(class ItemState const &)const 
	enum NewLeafType Block::getState<enum NewLeafType>(class ItemState const &)const 
	enum NewLogType Block::getState<enum NewLogType>(class ItemState const &)const 
	enum OldLeafType Block::getState<enum OldLeafType>(class ItemState const &)const 
	enum OldLogType Block::getState<enum OldLogType>(class ItemState const &)const 
	enum PortalAxis Block::getState<enum PortalAxis>(class ItemState const &)const 
	enum PrismarineBlockType Block::getState<enum PrismarineBlockType>(class ItemState const &)const 
	enum SandType Block::getState<enum SandType>(class ItemState const &)const 
	enum SaplingType Block::getState<enum SaplingType>(class ItemState const &)const 
	enum SeaGrassType Block::getState<enum SeaGrassType>(class ItemState const &)const 
	enum SpongeType Block::getState<enum SpongeType>(class ItemState const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(class ItemState const &)const 
	enum StoneSlabType2 Block::getState<enum StoneSlabType2>(class ItemState const &)const 
	enum StoneSlabType3 Block::getState<enum StoneSlabType3>(class ItemState const &)const 
	enum StoneSlabType4 Block::getState<enum StoneSlabType4>(class ItemState const &)const 
	enum StoneSlabType Block::getState<enum StoneSlabType>(class ItemState const &)const 
	enum StoneType Block::getState<enum StoneType>(class ItemState const &)const 
	enum SweetBerryBushBlock::BerryStage Block::getState<enum SweetBerryBushBlock::BerryStage>(class ItemState const &)const 
	enum TallGrassType Block::getState<enum TallGrassType>(class ItemState const &)const 
	enum WallBlockType Block::getState<enum WallBlockType>(class ItemState const &)const 
	enum WoodType Block::getState<enum WoodType>(class ItemState const &)const 
	unsigned char Block::getState<unsigned char>(class ItemState const &)const 
	enum WallConnectionType Block::getStateOrDefault<enum WallConnectionType>(class ItemState const &,enum WallConnectionType const &)const 
	bool Block::isAir(void)const 
	class gsl::not_null<class Block const *> Block::setState<enum TrapDoorBlock::TrapDoorDir>(class ItemState const &,enum TrapDoorBlock::TrapDoorDir)const 
	class gsl::not_null<class Block const *> Block::setState<unsigned char>(class ItemState const &,unsigned char)const 
	void RapidJsonDataFixers::Block::applyLambdaToComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,class std::function<void (class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &)> const &)
	bool RapidJsonDataFixers::Block::applyLambdaToComponentObject(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,class std::function<void (class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &)> const &)
	void RapidJsonDataFixers::Block::replaceComponentObjectWithFieldValue(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,std::string const &)

001.019.011.001_added.hpp
	class EntityContext const & Block::getEntity(void)const 
	enum AnvilDamage Block::getState<enum AnvilDamage>(class ItemState const &)const 
	enum AttachmentType Block::getState<enum AttachmentType>(class ItemState const &)const 
	enum BigDripleafTilt Block::getState<enum BigDripleafTilt>(class ItemState const &)const 
	enum BlockColor Block::getState<enum BlockColor>(class ItemState const &)const 
	struct Brightness Block::getState<struct Brightness>(class ItemState const &)const 
	enum CandleCount Block::getState<enum CandleCount>(class ItemState const &)const 
	enum CauldronLiquidType Block::getState<enum CauldronLiquidType>(class ItemState const &)const 
	enum ChemistryTableType Block::getState<enum ChemistryTableType>(class ItemState const &)const 
	enum ChiselType Block::getState<enum ChiselType>(class ItemState const &)const 
	enum CoralColor Block::getState<enum CoralColor>(class ItemState const &)const 
	enum Direction::Type Block::getState<enum Direction::Type>(class ItemState const &)const 
	enum DirtType Block::getState<enum DirtType>(class ItemState const &)const 
	enum DoublePlantType Block::getState<enum DoublePlantType>(class ItemState const &)const 
	enum DripstoneThickness Block::getState<enum DripstoneThickness>(class ItemState const &)const 
	enum Facing::Rotation Block::getState<enum Facing::Rotation>(class ItemState const &)const 
	enum LeverDirection Block::getState<enum LeverDirection>(class ItemState const &)const 
	enum MonsterEggStoneType Block::getState<enum MonsterEggStoneType>(class ItemState const &)const 
	enum NewLeafType Block::getState<enum NewLeafType>(class ItemState const &)const 
	enum NewLogType Block::getState<enum NewLogType>(class ItemState const &)const 
	enum OldLeafType Block::getState<enum OldLeafType>(class ItemState const &)const 
	enum OldLogType Block::getState<enum OldLogType>(class ItemState const &)const 
	enum PortalAxis Block::getState<enum PortalAxis>(class ItemState const &)const 
	enum PrismarineBlockType Block::getState<enum PrismarineBlockType>(class ItemState const &)const 
	enum SandType Block::getState<enum SandType>(class ItemState const &)const 
	enum SaplingType Block::getState<enum SaplingType>(class ItemState const &)const 
	enum SeaGrassType Block::getState<enum SeaGrassType>(class ItemState const &)const 
	enum SpongeType Block::getState<enum SpongeType>(class ItemState const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(class ItemState const &)const 
	enum StoneSlabType2 Block::getState<enum StoneSlabType2>(class ItemState const &)const 
	enum StoneSlabType3 Block::getState<enum StoneSlabType3>(class ItemState const &)const 
	enum StoneSlabType4 Block::getState<enum StoneSlabType4>(class ItemState const &)const 
	enum StoneSlabType Block::getState<enum StoneSlabType>(class ItemState const &)const 
	enum StoneType Block::getState<enum StoneType>(class ItemState const &)const 
	enum SweetBerryBushBlock::BerryStage Block::getState<enum SweetBerryBushBlock::BerryStage>(class ItemState const &)const 
	enum TallGrassType Block::getState<enum TallGrassType>(class ItemState const &)const 
	enum WallBlockType Block::getState<enum WallBlockType>(class ItemState const &)const 
	enum WoodType Block::getState<enum WoodType>(class ItemState const &)const 
	unsigned char Block::getState<unsigned char>(class ItemState const &)const 
	enum WallConnectionType Block::getStateOrDefault<enum WallConnectionType>(class ItemState const &,enum WallConnectionType const &)const 
	bool Block::isAir(void)const 
	class gsl::not_null<class Block const *> Block::setState<enum TrapDoorBlock::TrapDoorDir>(class ItemState const &,enum TrapDoorBlock::TrapDoorDir)const 
	class gsl::not_null<class Block const *> Block::setState<unsigned char>(class ItemState const &,unsigned char)const 
	void RapidJsonDataFixers::Block::applyLambdaToComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,class std::function<void (class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &)> const &)
	bool RapidJsonDataFixers::Block::applyLambdaToComponentObject(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,class std::function<void (class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &)> const &)
	void RapidJsonDataFixers::Block::replaceComponentObjectWithFieldValue(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,std::string const &)

001.019.011.001_removed.hpp
	class EntityContext const & Block::getEntity(void)const 
	enum AnvilDamage Block::getState<enum AnvilDamage>(unsigned __int64 const &)const 
	enum AttachmentType Block::getState<enum AttachmentType>(unsigned __int64 const &)const 
	enum BigDripleafTilt Block::getState<enum BigDripleafTilt>(unsigned __int64 const &)const 
	enum BlockColor Block::getState<enum BlockColor>(unsigned __int64 const &)const 
	enum CandleCount Block::getState<enum CandleCount>(unsigned __int64 const &)const 
	enum CauldronLiquidType Block::getState<enum CauldronLiquidType>(unsigned __int64 const &)const 
	enum ChemistryTableType Block::getState<enum ChemistryTableType>(unsigned __int64 const &)const 
	enum ChiselType Block::getState<enum ChiselType>(unsigned __int64 const &)const 
	enum CoralColor Block::getState<enum CoralColor>(unsigned __int64 const &)const 
	enum CoralDirection Block::getState<enum CoralDirection>(unsigned __int64 const &)const 
	enum Direction::Type Block::getState<enum Direction::Type>(unsigned __int64 const &)const 
	enum DirtType Block::getState<enum DirtType>(unsigned __int64 const &)const 
	enum DoublePlantType Block::getState<enum DoublePlantType>(unsigned __int64 const &)const 
	enum DripstoneThickness Block::getState<enum DripstoneThickness>(unsigned __int64 const &)const 
	enum Facing::Name Block::getState<enum Facing::Name>(unsigned __int64 const &)const 
	enum Facing::Rotation Block::getState<enum Facing::Rotation>(unsigned __int64 const &)const 
	enum FlowerType Block::getState<enum FlowerType>(unsigned __int64 const &)const 
	enum LeafSize Block::getState<enum LeafSize>(unsigned __int64 const &)const 
	enum LeverDirection Block::getState<enum LeverDirection>(unsigned __int64 const &)const 
	enum MonsterEggStoneType Block::getState<enum MonsterEggStoneType>(unsigned __int64 const &)const 
	enum MushroomOuterType Block::getState<enum MushroomOuterType>(unsigned __int64 const &)const 
	enum NewLeafType Block::getState<enum NewLeafType>(unsigned __int64 const &)const 
	enum NewLogType Block::getState<enum NewLogType>(unsigned __int64 const &)const 
	enum OldLeafType Block::getState<enum OldLeafType>(unsigned __int64 const &)const 
	enum OldLogType Block::getState<enum OldLogType>(unsigned __int64 const &)const 
	enum PillarAxis Block::getState<enum PillarAxis>(unsigned __int64 const &)const 
	enum PortalAxis Block::getState<enum PortalAxis>(unsigned __int64 const &)const 
	enum PrismarineBlockType Block::getState<enum PrismarineBlockType>(unsigned __int64 const &)const 
	enum RailDirection Block::getState<enum RailDirection>(unsigned __int64 const &)const 
	enum SandType Block::getState<enum SandType>(unsigned __int64 const &)const 
	enum SaplingType Block::getState<enum SaplingType>(unsigned __int64 const &)const 
	enum SeaGrassType Block::getState<enum SeaGrassType>(unsigned __int64 const &)const 
	enum SeaPickleCount Block::getState<enum SeaPickleCount>(unsigned __int64 const &)const 
	enum SpongeType Block::getState<enum SpongeType>(unsigned __int64 const &)const 
	enum StalkThickness Block::getState<enum StalkThickness>(unsigned __int64 const &)const 
	enum StoneBrickType Block::getState<enum StoneBrickType>(unsigned __int64 const &)const 
	enum StoneSlabType2 Block::getState<enum StoneSlabType2>(unsigned __int64 const &)const 
	enum StoneSlabType3 Block::getState<enum StoneSlabType3>(unsigned __int64 const &)const 
	enum StoneSlabType4 Block::getState<enum StoneSlabType4>(unsigned __int64 const &)const 
	enum StoneSlabType Block::getState<enum StoneSlabType>(unsigned __int64 const &)const 
	enum StoneType Block::getState<enum StoneType>(unsigned __int64 const &)const 
	enum SweetBerryBushBlock::BerryStage Block::getState<enum SweetBerryBushBlock::BerryStage>(unsigned __int64 const &)const 
	enum TallGrassType Block::getState<enum TallGrassType>(unsigned __int64 const &)const 
	enum TorchFacing Block::getState<enum TorchFacing>(unsigned __int64 const &)const 
	enum TrapDoorBlock::TrapDoorDir Block::getState<enum TrapDoorBlock::TrapDoorDir>(unsigned __int64 const &)const 
	enum WallBlockType Block::getState<enum WallBlockType>(unsigned __int64 const &)const 
	enum WallConnectionType Block::getState<enum WallConnectionType>(unsigned __int64 const &)const 
	enum WeirdoDirection Block::getState<enum WeirdoDirection>(unsigned __int64 const &)const 
	enum WoodType Block::getState<enum WoodType>(unsigned __int64 const &)const 
	int Block::getState<int>(unsigned __int64 const &)const 
	unsigned char Block::getState<unsigned char>(unsigned __int64 const &)const 
	unsigned short Block::getState<unsigned short>(unsigned __int64 const &)const 
	unsigned int Block::getStateMask(class ItemState const &)const 
	bool Block::getStateOrDefault<bool>(class ItemState const &,bool const &)const 
	bool Block::operator!=(class Block const &)const 
	bool Block::operator==(class Block const &)const 
	class gsl::not_null<class Block const *> Block::setState<enum CauldronLiquidType>(class ItemState const &,enum CauldronLiquidType)const 
	class gsl::not_null<class Block const *> Block::setState<enum ChemistryTableType>(class ItemState const &,enum ChemistryTableType)const 
	class gsl::not_null<class Block const *> Block::setState<enum DirtType>(class ItemState const &,enum DirtType)const 
	class gsl::not_null<class Block const *> Block::setState<enum NewLeafType>(class ItemState const &,enum NewLeafType)const 
	class gsl::not_null<class Block const *> Block::setState<enum SandType>(class ItemState const &,enum SandType)const 
	class gsl::not_null<class Block const *> Block::setState<unsigned int>(class ItemState const &,unsigned int)const 
	class Block const * Block::trySetState<int>(class ItemState const &,int)const 

001.019.020.002_added.hpp
	struct BlockLightEmissionComponent const * Block::tryGetComponent<struct BlockLightEmissionComponent>(void)const 
	struct BlockSelectionBoxComponent const * Block::tryGetComponent<struct BlockSelectionBoxComponent>(void)const 
	void RapidJsonDataFixers::Block::removeComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &)

001.019.020.002_removed.hpp
	class Block const & Block::getDefaultState(void)const 
	struct BlockAimCollisionComponent const * Block::tryGetComponent<struct BlockAimCollisionComponent>(void)const 

001.019.021.001_removed.hpp
	void RapidJsonDataFixers::Block::removeComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &)

001.019.030.004_added.hpp
	bool Block::isLavaFlammable(void)const 
	struct BlockDisplayNameComponent const * Block::tryGetComponent<struct BlockDisplayNameComponent>(void)const 
	void RapidJsonDataFixers::Block::applyLambdaToDescriptionObject(class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &,class std::function<void (class rapidjson::GenericValue<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &)> const &)
	void RapidJsonDataFixers::Block::removeComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &)

001.019.030.004_removed.hpp
	class gsl::basic_string_span<char const,-1> Block::getCreativeGroup(void)const 
	struct BlockCreativeGroupComponent const * Block::tryGetComponent<struct BlockCreativeGroupComponent>(void)const 

001.019.040.002_added.hpp
	class gsl::not_null<class Block const *> Block::setState<enum DirtType>(class ItemState const &,enum DirtType)const 
	class gsl::not_null<class Block const *> Block::setState<enum SandType>(class ItemState const &,enum SandType)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Block const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,class ItemStack const &)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float)const 
	struct BlockGeometryComponent const * Block::tryGetComponent<struct BlockGeometryComponent>(void)const 
	void Block::trySpawnResourcesOnExplosion(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float)const 
	bool Block::waterSpreadCausesSpawn(void)const 
	void RapidJsonDataFixers::Block::removeComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,bool,std::string const &)
	void RapidJsonDataFixers::Block::removeDuplicateComponents(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &)
	void RapidJsonDataFixers::Block::removeDuplicateComponentsInComponentsSection(class rapidjson::GenericMemberIterator<0,struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> > &)

001.019.040.002_removed.hpp
	class ItemInstance Block::getSilkTouchItemInstance(void)const 
	bool const Block::hasRuntimeId(void)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Block const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int,class ItemStack const &)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int)const 
	void Block::trySpawnResourcesOnExplosion(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,int)const 
	void RapidJsonDataFixers::Block::removeComponent(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &)

001.019.050.002_added.hpp
	enum BlockOcclusionType Block::_getBlockOcclusionType(void)const 
	enum PillarAxis Block::getState<enum PillarAxis>(class ItemState const &)const 
	bool Block::shouldTickOnSetBlock(void)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,class ItemStack const &)const 

001.019.050.002_removed.hpp
	bool Block::_isSolid(void)const 
	bool Block::hasPropertyNoLock(enum BlockProperty)const 
	bool Block::isStandingSign(void)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Block const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,class ItemStack const &)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float)const 
	struct BlockMapColorComponent const * Block::tryGetComponent<struct BlockMapColorComponent>(void)const 

001.019.060.004_added.hpp
	class Block const & Block::getDefaultState(void)const 
	float Block::getExplosionResistance(void)const 
	enum MushroomOuterType Block::getState<enum MushroomOuterType>(class ItemState const &)const 
	int Block::getState<int>(unsigned __int64 const &)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Randomize &,float,class ItemStack const &)const 
	void Block::trySpawnResourcesOnExplosion(class BlockSource &,class BlockPos const &,class Block const &,float)const 
	bool Block::use(class Player &,class BlockPos const &,unsigned char,class std::optional<class Vec3>)const 
	void RapidJsonDataFixers::Block::legacyFindIfMissingFieldAndRemoveComponent(class rapidjson::GenericMemberIterator<0,struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator> >,std::string const &,std::string const &)
	void RapidJsonDataFixers::Block::legacyRemoveComponentIfMissingField(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>,class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>,class rapidjson::CrtAllocator> &,std::string const &,std::string const &)

001.019.060.004_removed.hpp
	float Block::getExplosionResistance(class Actor *)const 
	int Block::getResourceCount(class Randomize &,int)const 
	void Block::spawnResources(class BlockSource &,class BlockPos const &,class Randomize &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float,class ItemStack const &)const 
	void Block::trySpawnResourcesOnExplosion(class BlockSource &,class BlockPos const &,class Block const &,class std::vector<class Item const *,class std::allocator<class Item const *> > *,float)const 
	bool Block::use(class Player &,class BlockPos const &,unsigned char)const 

001.019.070.002_added.hpp
	bool Block::allowStateMismatchOnPlacement(class Block const &)const 

001.019.070.002_removed.hpp
	bool Block::isAuxValueRelevantForPicking(void)const
 */

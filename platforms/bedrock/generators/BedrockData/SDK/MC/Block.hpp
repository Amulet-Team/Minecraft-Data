#pragma once
#include <limits>
#include "MC/nbt/CompoundTag.hpp"


namespace MinecraftAPI {
	class Block {
		//1.16.100.4
		typedef float (*_getFrictionT)(const Block*);
		static _getFrictionT _getFriction;

		//1.16.210.5
		typedef CompoundTag const& (*_getSerializationIdT)(const Block*);
		static _getSerializationIdT _getSerializationId;

		typedef bool (*_isContainerBlockT)(const Block*);
		static _isContainerBlockT _isContainerBlock;

		typedef enum BlockActorType(*_getBlockEntityTypeT)(const Block*);
		static _getBlockEntityTypeT _getBlockEntityType;


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
	};
}


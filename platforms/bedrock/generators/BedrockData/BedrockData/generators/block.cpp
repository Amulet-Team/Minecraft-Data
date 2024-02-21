#include "generators.hpp"
#include "MC/Minecraft.hpp"
#include "MC/Level.hpp"
#include "MC/BlockPalette.hpp"
#include "MC/nbt/NbtIo.hpp"
#include "logging.hpp"
#include <string>


using namespace MinecraftAPI;


namespace Data {
	void block() {
		debug("Running data generator: Block");
		Minecraft* minecraft = Minecraft::get();
		if (Level* level = minecraft->getLevel()) {
			if (BlockPalette* block_palette = level->getBlockPalette()) {
				unsigned int palette_len = block_palette->len();
				debug("There are " + std::to_string(palette_len) + " blocks in the palette.");
				for (unsigned int i = 0; i < palette_len; i++) {
					const Block* block = block_palette->getBlock(i);
					//logToFile("generated/block/data/friction.txt", block->getFriction());
					const CompoundTag* tag = block->getSerializationId();
					std::string tag_data = NbtIo::serialise(tag);
					logToBinaryFile("generated/block/states.nbtarr", tag_data);
					logToFile("generated/block/is_container.txt", block->isContainerBlock());
					logToFile("generated/block/block_entity.txt", block->getBlockEntityType());
					logToFile("generated/block/variant.txt", block->getVariant());
				}
			}
			else {
				debug("Could not find block palette");
			}
		}
		else {
			debug("Could not find level");
		}
	}
}

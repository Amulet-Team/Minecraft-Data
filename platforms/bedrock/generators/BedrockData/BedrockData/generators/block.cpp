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
		debug("block generator");
		Minecraft* minecraft = Minecraft::get();
		debug("got minecraft ptr");
		if (Level* level = minecraft->getLevel()) {
			debug("got level ptr");
			if (BlockPalette* block_palette = level->getBlockPalette()) {
				debug("got block palette ptr");
				unsigned int palette_len = block_palette->len();
				debug(std::to_string(palette_len));
				for (unsigned int i = 0; i < palette_len; i++) {
					const Block* block = block_palette->getBlock(i);
					//logToFile("generated/block/data/friction.txt", block->getFriction());
					const CompoundTag* tag = block->getSerializationId();
					std::string tag_data = NbtIo::serialise(tag);
					logToBinaryFile("generated/block/states.bin", tag_data);
					logToFile("generated/block/is_container.txt", block->isContainerBlock());
					logToFile("generated/block/block_entity.txt", block->getBlockEntityType());
				}
			}
		}
	}
}

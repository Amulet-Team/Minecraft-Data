#include "generators.hpp"
#include "MC/Minecraft.hpp"
#include "MC/Level.hpp"
#include "MC/BlockPalette.hpp"
#include "logging.hpp"


using namespace MinecraftAPI;

namespace Data {
	void block() {
		Minecraft* minecraft = Minecraft::get();
		Level* level = minecraft->getLevel();
		if (level != nullptr) {
			BlockPalette* block_palette = level->getBlockPalette();
		}
	}
}

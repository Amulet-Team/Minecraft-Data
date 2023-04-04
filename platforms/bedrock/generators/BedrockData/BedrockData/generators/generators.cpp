#include <iostream>

#include "util/get_file.hpp"
#include "MC/Minecraft.hpp"

#include "generators.hpp"


using namespace MinecraftAPI;


void Data::main() {
    Minecraft::waitForPtr();
    Data::game_version();
    Data::data_version();
    Data::effect();
}

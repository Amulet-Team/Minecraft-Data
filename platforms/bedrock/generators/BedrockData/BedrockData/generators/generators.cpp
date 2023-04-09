#include <iostream>

#include "logging.hpp"
#include "MC/Minecraft.hpp"

#include "generators.hpp"


using namespace MinecraftAPI;


void Data::main() {
    Minecraft::get();
    Data::game_version();
    Data::data_version();
    Data::effect();
    Data::block();
}

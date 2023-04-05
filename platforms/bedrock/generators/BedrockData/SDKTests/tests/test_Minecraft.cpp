#include "tests.hpp"
#include "MC/Minecraft.hpp"
#include <string>


using namespace MinecraftAPI;


void Test::test_Minecraft() {
	try {
		Minecraft::waitForPtr();
	}
	catch (const std::string error) {
		throw "test_Minecraft: " + error;
	}
}

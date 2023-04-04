#include "Minecraft.hpp"
#include "HookAPI.h"
#include <mutex>
#include <string>

using namespace MinecraftAPI;

Minecraft** Minecraft::Ptr = (Minecraft**)dlsym("?mGame@ServerCommand@@1PEAVMinecraft@@EA");

int state = 0;  // 0=unchecked, -1=error, 1=success
std::string err;
std::recursive_mutex m;


// Wait until the Minecraft pointer has been set
void Minecraft::waitForPtr() {
	std::lock_guard<std::recursive_mutex> lk(m);

	switch (state)
	{
	case -1:
		throw err;

	case 0:
		// The state has not been checked.
		if (Minecraft::Ptr == nullptr) {
			err = "Could not find Minecraft instance";
			state = -1;
			throw err;
		}
		else {
			for (int i = 0; i < 30 * 4; i++) {
				if (*Minecraft::Ptr == NULL) {
					// This is not set until the server is set up so wait until it is ready
					std::this_thread::sleep_for(std::chrono::milliseconds(250));
				}
				else {
					state = 1;
					return;
				}
			}
			err = "The Minecraft instance was not set after 30 seconds.";
			state = -1;
			throw err;
		}

	case 1:
		return;
	}
}

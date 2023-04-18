#include "Minecraft.hpp"
#include "HookAPI.h"
#include <mutex>
#include <string>
#include <bitset>

using namespace MinecraftAPI;

// Added 1.9.0.15
Minecraft** Minecraft::Ptr = (Minecraft**)dlsym("?mGame@ServerCommand@@1PEAVMinecraft@@EA");
// Added 1.11.4.2
Minecraft::_getLevelT Minecraft::_getLevel = (Minecraft::_getLevelT)dlsym("?getLevel@Minecraft@@QEBAPEAVLevel@@XZ");


bool isReady = false;


THook(void, "?log@BedrockLog@@YAXIIPEBDH0ZZ", unsigned int a,unsigned int b,char const * c,int d,char const * e, va_list args) {
	debug("old log");
	if (std::string(e) == "Server started.") {
		isReady = true;
	}
	original(a, b, c, d, e, args);
}

THook(void, "?log@BedrockLog@@YAXW4LogCategory@1@V?$bitset@$02@std@@W4LogRule@1@W4LogAreaID@@IPEBDH4ZZ", enum LogCategory a, class std::bitset<3> b, enum LogRule c, enum LogAreaID d, unsigned int e, char const* f, int g, char const* h, va_list args) {
	if (std::string(h) == "Server started.") {
		isReady = true;
	}
	original(a, b, c, d, e, f, g, h, args);
}


int state = 0;  // 0=unchecked, -1=error, 1=success
std::string err;
std::recursive_mutex m;

// Wait until the Minecraft pointer has been set and return it
Minecraft* Minecraft::get() {
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
				if (!isReady or *Minecraft::Ptr == nullptr) {
					// This is not set until the server is set up so wait until it is ready
					std::this_thread::sleep_for(std::chrono::milliseconds(250));
				}
				else {
					state = 1;
					return *Minecraft::Ptr;
				}
			}
			err = "The Minecraft instance was not set after 30 seconds.";
			state = -1;
			throw err;
		}
	}
	return *Minecraft::Ptr;
}

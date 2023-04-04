#pragma once


namespace MinecraftAPI {
	class Minecraft {
	public:
		static Minecraft** Ptr;
		static void waitForPtr();
	};

	class Level {};
}

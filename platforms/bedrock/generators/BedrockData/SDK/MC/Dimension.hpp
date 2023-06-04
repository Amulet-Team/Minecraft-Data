#pragma once

namespace MinecraftAPI {
	class Dimension {
		

	public:
		Dimension* getDimension(unsigned int id) {
			if (_getBlock) {
				return &_getBlock(this, id);
			}
			return nullptr;
		};

		unsigned int len();
	};
}
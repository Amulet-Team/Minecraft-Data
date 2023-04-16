#pragma once
#include <string>
#include "HookAPI.h"


namespace MinecraftAPI {
	class IDataOutput {
		void* vtbl;
	public:
		std::string* result;

		IDataOutput(std::string* result) : result(result) {
			vtbl = dlsym("??_7StringByteOutput@@6B@");
		}
	};
}

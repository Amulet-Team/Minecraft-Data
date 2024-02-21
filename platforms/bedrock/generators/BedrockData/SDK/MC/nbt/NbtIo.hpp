#pragma once
#include "CompoundTag.hpp"
#include "IDataOutput.hpp"


namespace MinecraftAPI {
	class NbtIo {
		typedef void (*_writeT)(CompoundTag const*, IDataOutput&);
		static _writeT _write;
	public:
		static std::string serialise(const CompoundTag* tag) {
			std::string result = "";
			IDataOutput iDataOutput(&result);
			_write(tag, iDataOutput);
			return result;
		}
	};
}

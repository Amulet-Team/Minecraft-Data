#pragma once
#include "CompoundTag.hpp"
#include "IDataOutput.hpp"


namespace MinecraftAPI {
	class NbtIo {
		typedef void (*_writeT)(CompoundTag const*, IDataOutput&);
		static _writeT _write;
		static _writeT _write2;
	public:
		static std::string serialise(const CompoundTag* tag) {
			std::string result = "";
			IDataOutput iDataOutput(&result);
			if (_write){
				_write(tag, iDataOutput);
			} else if (_write2){
				_write2(tag, iDataOutput);
			}
			return result;
		}
	};
}

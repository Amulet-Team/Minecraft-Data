#include "NbtIo.hpp"

using namespace MinecraftAPI;


// Added 1.9.0.15
NbtIo::_writeT NbtIo::_write = (NbtIo::_writeT)dlsym("?write@NbtIo@@SAXPEBVCompoundTag@@AEAVIDataOutput@@@Z");
// Changed 1.20.71.01
NbtIo::_writeT NbtIo::_write2 = (NbtIo::_writeT)dlsym("?write@NbtIo@@YAXPEBVCompoundTag@@AEAVIDataOutput@@@Z");

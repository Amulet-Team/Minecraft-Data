#include <memory>
#include <MC/nbt/Tag.hpp>
#include <MC/nbt/CompoundTag.hpp>


using namespace MinecraftAPI;

std::unique_ptr<CompoundTag> CompoundTag::create() {
    return std::unique_ptr<CompoundTag>((CompoundTag*)Tag::newTag(Tag::Type::Compound).release());
}

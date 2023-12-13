#pragma once
#include "../Global.h"

#include "CompoundTag.hpp"
#include "BlockLegacy.hpp"
#include "Brightness.hpp"


class Block {
public:
    // ?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ
    MCAPI BlockLegacy const& getLegacyBlock() const;
    // ?getLight@Block@@QEBA?AUBrightness@@XZ
    MCAPI Brightness getLight() const;
    // ?getLightEmission@Block@@QEBA?AUBrightness@@XZ
    MCAPI Brightness getLightEmission() const;
    // ?getSerializationId@Block@@QEBAAEBVCompoundTag@@XZ
    MCAPI CompoundTag const& getSerializationId() const;
    MCAPI void test() const;
};

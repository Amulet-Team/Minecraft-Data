#pragma once
#include "../Global.h"


class Tag {
public:
    enum class Type : uint8_t {
        End,
        Byte,
        Short,
        Int,
        Int64,
        Float,
        Double,
        ByteArray,
        String,
        List,
        Compound,
        IntArray,
    };
	// ?newTag@Tag@@SA?AV?$unique_ptr@VTag@@U?$default_delete@VTag@@@std@@@std@@W4Type@1@@Z
	MCAPI static std::unique_ptr<class Tag> newTag(enum class Tag::Type);
};

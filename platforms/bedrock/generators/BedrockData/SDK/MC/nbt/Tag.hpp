#pragma once
#include <cstdint>
#include <stdexcept>

class Tag {
public:
    enum class Type : uint8_t {
        End,
        Byte,
        Short,
        Int,
        Long,
        Float,
        Double,
        ByteArray,
        String,
        List,
        Compound,
        IntArray,
    };

private:
    typedef std::unique_ptr<class Tag> (*_newTagT)(enum class Tag::Type);
    static _newTagT _newTag;

public:
    static std::unique_ptr<class Tag> newTag(enum class Tag::Type type) {
        if (_newTag) {
            return _newTag(type);
        }
        throw std::runtime_error("Could not find virtual function Tag::newTag");
    };
};

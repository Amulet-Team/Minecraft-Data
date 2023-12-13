#include "HookAPI.h"
#include "Tag.hpp"

Tag::_newTagT Tag::_newTag = (Tag::_newTagT)dlsym("?newTag@Tag@@SA?AV?$unique_ptr@VTag@@U?$default_delete@VTag@@@std@@@std@@W4Type@1@@Z");

#pragma once

template <typename T>
class WeakPtr {
    T** value;

public:
    inline T* get() {
        if (value)
            return *value;
        return nullptr;
    }
    inline T const* get() const {
        if (value)
            return *value;
        return nullptr;
    }
    inline T& operator*() {
        return *get();
    }
    inline T const& operator*() const {
        return *get();
    }
    inline operator bool() const {
        return get() != nullptr;
    }
};

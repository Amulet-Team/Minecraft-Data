#pragma once
#include <memory>

template <typename T>
class WeakStorageSharePtr {
public:
    enum class VariadicInit : int {
        NonAmbiguous = 0,
    };
    enum class EmptyInit : int {
        NoValue = 0,
    };
    std::weak_ptr<T> mHandle;

    T* get() const {
        return mHandle.lock().get();
    }
};

template <typename T>
struct SharePtrRefTraits {
public:
    using StackRef = T;
    using WeakStorage = WeakStorageSharePtr<StackRef>;
    //using OwnerStorage = OwnerStorageSharePtr<StackRef>;
    //using OwnerStackRef = StackRef;
    //using StackResultStorage = StackResultStorageSharePtr<OwnerStackRef>;
};

template <typename T>
class WeakRefT : public T::WeakStorage {};

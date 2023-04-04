# API Docs

This is a condensed document with examples of the low level API.

Most are taken from this thread in the LiteLoaderBDS discord server.

https://discord.com/channels/849252980430864384/849253492396392448/1019228741504864278

## Wrapping

Wrapping replaces the original function with a custom function.

### Static wrapping

A static member is a variable/function that does not need an instance of the class to be used.

The first argument is the return type and the second argument is the compiled function definition. Following that are the function arguments.

If the return type is not void then the function must return the value.

Header:
```cpp
// https://github.com/LiteLDev/LiteLoaderSDK/blob/6b5ab1f90ee059bdffcc35507786158dd726bcf6/Header/MC/BlockTypeRegistry.hpp#L94
/**
 * @symbol ?registerAlias@BlockTypeRegistry@@SAXAEBVHashedString@@0@Z
 * @hash   -368041733
 */
MCAPI static void registerAlias(class HashedString const &, class HashedString const &);
```

Wrapped:
```cpp
THook(void, "?registerAlias@BlockTypeRegistry@@SAXAEBVHashedString@@0@Z", const HashedString& alias, const HashedString& name) {
    original(alias, name);
}
```

### Instance wrapping

If a member is not defined as being static this is used instead.

The same rules apply as in static wrapping but the first argument is the instance.

Header:
```cpp
https://github.com/LiteLDev/LiteLoaderSDK/blob/6b5ab1f90ee059bdffcc35507786158dd726bcf6/Header/MC/ItemRegistry.hpp#L286
/**
 * @symbol ?registerItem@ItemRegistry@@AEAAXV?$SharedPtr@VItem@@@@@Z
 * @hash   -1779913791
 */
MCAPI void registerItem(class SharedPtr<class Item>);
```

Wrapped:
```cpp
TInstanceHook(void, "?registerItem@ItemRegistry@@SAXV?$SharedPtr@VItem@@@@@Z", ItemRegistry, void* itemV) {
	original(this, itemV);
}
```


### Getting data

A variable can be found from its descriptor as follows.

```cpp
int* num = (int*)dlsym("?MajorVersion@SharedConstants@@3HB");
// If the desciptor does not exist in that version of the game it will return NULL
if (num != NULL){
    // Do your thing here
}
```

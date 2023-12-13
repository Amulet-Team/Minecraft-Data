#pragma once

#ifndef LIAPI
#ifdef LITELOADER_EXPORTS
#define LIAPI __declspec(dllexport)
#else
#define LIAPI __declspec(dllimport)
#endif
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#define MCAPI __declspec(dllimport)
#define MCVAPI __declspec(dllimport)
#define MCINLINE inline
#define MCCLS

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif

#ifndef LL_CONSTEXPR
#if __cplusplus <= 201703L
#define LL_CONSTEXPR inline
#else
#define LL_CONSTEXPR constexpr
#endif
#endif

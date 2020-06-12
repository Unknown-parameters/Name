//
// File: lightpro_types.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//
#ifndef LIGHTPRO_TYPES_H
#define LIGHTPRO_TYPES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#ifdef LIGHTPRO_XIL_BUILD
#if defined(_MSC_VER) || defined(__LCC__)
#define LIGHTPRO_DLL_EXPORT            __declspec(dllimport)
#else
#define LIGHTPRO_DLL_EXPORT
#endif

#elif defined(BUILDING_LIGHTPRO)
#if defined(_MSC_VER) || defined(__LCC__)
#define LIGHTPRO_DLL_EXPORT            __declspec(dllexport)
#else
#define LIGHTPRO_DLL_EXPORT            __attribute__ ((visibility("default")))
#endif

#else
#define LIGHTPRO_DLL_EXPORT
#endif

#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4251)

#endif

#ifdef _MSC_VER

#pragma warning(pop)

#endif
#endif

//
// File trailer for lightpro_types.h
//
// [EOF]
//

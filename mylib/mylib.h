#include <stdio.h>

#ifndef MYLIB_H
#define MYLIB_H

#ifdef __cplusplus
#define MYLIB_EXTERN_C extern "C"
#else
#define MYLIB_EXTERN_C
#endif

#if defined(MYLIB_STATIC_LIBRARY)
#define MYLIB_EXPORT MYLIB_EXTERN_C
#else
#define MYLIB_EXPORT MYLIB_EXTERN_C __attribute__((visibility("default")))
#endif

MYLIB_EXPORT int mylib_hello();

#endif // MYLIB_H

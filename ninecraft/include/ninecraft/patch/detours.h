#ifndef NINECRAFT_PATCH_DETOURS_H
#define NINECRAFT_PATCH_DETOURS_H

#include <stdbool.h>
#include <stdlib.h>

extern void *arm_detour(void *target_addr, void *replacement_addr);

extern void *x86_detour(void *target_addr, void *replacement_addr, bool jump, size_t codelen);

#if defined(__i386__) || defined(_M_IX86)
#define DETOUR(target_addr, replacement_addr, jump, codelen) (x86_detour(target_addr, replacement_addr, jump, codelen))
#else
#if defined(__arm__) || defined(_M_ARM) 
#define DETOUR(target_addr, replacement_addr, jump, codelen) (arm_detour(target_addr, replacement_addr))
#else
#define DETOUR(target_addr, replacement_addr, jump)
#endif
#endif

#endif
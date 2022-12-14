#ifndef NINECRAFT_PATCH_DETOURS_H
#define NINECRAFT_PATCH_DETOURS_H

#include <stdbool.h>

#define THUMB_SET_BIT0(addr) (addr | 0x01)
#define THUMB_CLEAR_BIT0(addr) (addr & 0xfffffffe)
#define THUMB_TEST_BIT0(addr) (addr & 0x01)

extern void arm_detour(void *target_addr, void *replacement_addr);

extern void x86_detour(void *target_addr, void *replacement_addr, bool jump);

#ifdef __i386__
#define DETOUR(target_addr, replacement_addr, jump) (x86_detour(target_addr, replacement_addr, jump))
#else
#ifdef __thumb2__
#define DETOUR(target_addr, replacement_addr, jump) (arm_detour(target_addr, replacement_addr))
#else
#define DETOUR(target_addr, replacement_addr, jump)
#endif
#endif

#endif
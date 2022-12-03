#pragma once

#define THUMB_SET_BIT0(addr) (addr | 0x01)
#define THUMB_CLEAR_BIT0(addr) (addr & 0xfffffffe)
#define THUMB_TEST_BIT0(addr) (addr & 0x01)

void arm_detour(void *target_addr, void *replacement_addr);

void x86_detour(void *target_addr, void *replacement_addr);

#ifdef __i386__
#define DETOUR(target_addr, replacement_addr) (x86_detour(target_addr, replacement_addr))
#else
#ifdef __arm__
#define DETOUR(target_addr, replacement_addr) (arm_detour(target_addr, replacement_addr))
#else
#define DETOUR(target_addr, replacement_addr)
#endif
#endif
#ifndef NINECRAFT_PATCH_DETOURS_H
#define NINECRAFT_PATCH_DETOURS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    size_t len;
    void *addr;
    uint8_t original[8];
    uint8_t detour[8];
} detour_backup_t;

extern void detour_disarm(detour_backup_t backup);

extern void detour_rearm(detour_backup_t backup);

extern detour_backup_t arm_detour(void *target_addr, void *replacement_addr);

extern detour_backup_t x86_detour(void *target_addr, void *replacement_addr, bool jump);

#if defined(__i386__) || defined(_M_IX86)
#define DETOUR(target_addr, replacement_addr, jump) (x86_detour(target_addr, replacement_addr, jump))
#else
#if defined(__arm__) || defined(_M_ARM) 
#define DETOUR(target_addr, replacement_addr, jump) (arm_detour(target_addr, replacement_addr))
#else
#define DETOUR(target_addr, replacement_addr, jump)
#endif
#endif

#endif
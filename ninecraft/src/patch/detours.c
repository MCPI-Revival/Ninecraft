#include <ninecraft/patch/detours.h>
#include <stdint.h>
#include <string.h>
#include <ninecraft/patch/patch_address.h>

void detour_disarm(detour_backup_t backup) {
    patch_address(backup.addr, backup.original, backup.len, PATCH_ADDRESS_PROT_XR);
}

void detour_rearm(detour_backup_t backup) {
    memcpy(backup.addr, backup.detour, backup.len);
    patch_address(backup.addr, backup.detour, backup.len, PATCH_ADDRESS_PROT_XR);
}

detour_backup_t arm_detour(void *target_addr, void *replacement_addr) {
    uint8_t patch[8];
    detour_backup_t backup;
    backup.len = 8;
    if ((uintptr_t)target_addr & 1) {
        uintptr_t addr = (uintptr_t)target_addr & ~1;
        backup.addr = (void *)addr;
        memcpy(backup.original, (void *)addr, 8);
        *(uint16_t *)patch = 0xF8DF;
        if (addr % 4 != 0) {
            *(uint16_t *)(patch + 2) = 0xF002;
        } else {
            *(uint16_t *)(patch + 2) = 0xF000;
        }
        *(uint32_t *)(patch + 4) = (uintptr_t)replacement_addr;
        patch_address((void *)addr, patch, 8, PATCH_ADDRESS_PROT_XR);
        memcpy(backup.detour, (void *)addr, 8);
    } else {
        backup.addr = target_addr;
        memcpy(backup.original, target_addr, 8);
        *(uint32_t *)patch = 0xe51ff004;
        *(uint32_t *)((char *)patch + 4) = (uint32_t)replacement_addr;
        patch_address(target_addr, patch, 8, PATCH_ADDRESS_PROT_XR);
        memcpy(backup.detour, target_addr, 8);
    }
    return backup;
}

detour_backup_t x86_detour(void *target_addr, void *replacement_addr, bool jump) {
    uint8_t patch[5];
    detour_backup_t backup;
    backup.len = 5;
    backup.addr = target_addr;
    memcpy(backup.original, target_addr, 5);
    *(uint8_t *)patch = jump ? 0xe9 : 0xe8;
    *(uint32_t *)((uintptr_t)patch + 1) = (uintptr_t)replacement_addr - (uintptr_t)target_addr - 5;
    patch_address(target_addr, patch, 5, PATCH_ADDRESS_PROT_XR);
    memcpy(backup.detour, target_addr, 5);
    return backup;
}

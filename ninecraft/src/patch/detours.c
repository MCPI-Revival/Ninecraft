#include <ninecraft/patch/detours.h>
#include <stdint.h>
#include <string.h>

void arm_detour(void *target_addr, void *replacement_addr) {
    if (THUMB_TEST_BIT0((uint32_t)target_addr)) {
        *(uint16_t *)(THUMB_CLEAR_BIT0((uint32_t)target_addr)) = 0xF8DF;
        if (THUMB_CLEAR_BIT0((uint32_t)target_addr) % 4 != 0) {
            *(uint16_t *)(THUMB_CLEAR_BIT0((uint32_t)target_addr) + 2) = 0xF002;
        } else {
            *(uint16_t *)(THUMB_CLEAR_BIT0((uint32_t)target_addr) + 2) = 0xF000;
        }
        *(uint16_t *)(THUMB_CLEAR_BIT0((uint32_t)target_addr) + 4) = (uint16_t)((uint32_t)replacement_addr & 0xFFFF);
        *(uint16_t *)(THUMB_CLEAR_BIT0((uint32_t)target_addr) + 6) = (uint16_t)((uint32_t)replacement_addr >> 16);
    } else {
        *(uint32_t *)target_addr = 0xe51ff004;
        *(uint32_t *)((char *)target_addr + 4) = (uint32_t)replacement_addr;
    }
}

void x86_detour(void *target_addr, void *replacement_addr, bool jump) {
    uint32_t addr = (uint32_t)replacement_addr - (uint32_t)target_addr - 5;
    ((uint8_t *)target_addr)[0] = jump ? 0xe9 : 0xe8;
    memcpy(&((uint8_t *)target_addr)[1], &addr, 4);
}
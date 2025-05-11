#include <ninecraft/patch/detours.h>
#include <stdint.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

static uintptr_t trampoline_alloc() {
#ifdef _WIN32
    return (uintptr_t)VirtualAlloc(NULL, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
#else
    return (uintptr_t)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
}

static uintptr_t arm_trampoline(uintptr_t target_addr) {
    uintptr_t trampoline = trampoline_alloc();
    trampoline = (trampoline + 3) & ~3;

    if (target_addr & 1) {
        uintptr_t addr = target_addr & ~1;
        *(uint32_t *)trampoline = *(uint32_t *)addr;
        *(uint32_t *)(trampoline + 4) = *(uint32_t *)(addr + 4);
        *(uint32_t *)(trampoline + 8) = 0xF000F8DF;
        *(uint32_t *)(trampoline + 12) = target_addr + 8;
        return trampoline + 1;
    }
    *(uint32_t *)trampoline = *(uint32_t *)target_addr;
    *(uint32_t *)(trampoline + 4) = *(uint32_t *)(target_addr + 4);
    *(uint32_t *)(trampoline + 8) = 0xe51ff004;
    *(uint32_t *)(trampoline + 12) = target_addr + 8;
    return trampoline;
}

static uintptr_t x86_trampoline(uintptr_t target_addr) {
    uintptr_t trampoline = trampoline_alloc();
    trampoline = (trampoline + 3) & ~3;
    memcpy((void *)trampoline, (void *)target_addr, 5);
    *(uint8_t *)(target_addr + 5) = 0xe9;
    *(uint32_t *)(target_addr + 6) = trampoline - target_addr;
    return trampoline;
}

void *arm_detour(void *target_addr, void *replacement_addr) {
    void *trampoline = (void *)arm_trampoline((uintptr_t)target_addr);
    if ((uintptr_t)target_addr & 1) {
        uintptr_t addr = (uintptr_t)target_addr & ~1;
        *(uint16_t *)addr = 0xF8DF;
        if (addr % 4 != 0) {
            *(uint16_t *)(addr + 2) = 0xF002;
        } else {
            *(uint16_t *)(addr + 2) = 0xF000;
        }
        *(uint32_t *)(addr + 4) = (uintptr_t)replacement_addr;
    } else {
        *(uint32_t *)target_addr = 0xe51ff004;
        *(uint32_t *)((char *)target_addr + 4) = (uint32_t)replacement_addr;
    }
    return trampoline;
}

void *x86_detour(void *target_addr, void *replacement_addr, bool jump) {
    void *trampoline = NULL;
    if (jump) {
        trampoline = (void *)x86_trampoline((uintptr_t)target_addr);
    }
    *(uint8_t *)target_addr = jump ? 0xe9 : 0xe8;
    *(uint32_t *)((uintptr_t)target_addr + 1) = (uintptr_t)replacement_addr - (uintptr_t)target_addr - 5;
    return trampoline;
}
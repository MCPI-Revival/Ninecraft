#include <ninecraft/patch/patch_address.h>
#include <stdint.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>

#define PROT_TO_OSPROT(x) ( \
    (x == PATCH_ADDRESS_PROT_NA) ? PAGE_NOACCESS : ( \
        (x == PATCH_ADDRESS_PROT_R) ? PAGE_READONLY : ( \
            (x == PATCH_ADDRESS_PROT_W) ? PAGE_READWRITE : ( \
                (x == PATCH_ADDRESS_PROT_RW) ? PAGE_READWRITE : ( \
                    (x == PATCH_ADDRESS_PROT_X) ? PAGE_EXECUTE : ( \
                        (x == PATCH_ADDRESS_PROT_XR) ? PAGE_EXECUTE_READ : ( \
                            (x == PATCH_ADDRESS_PROT_XW) ? PAGE_EXECUTE_READWRITE : ( \
                                (x == PATCH_ADDRESS_PROT_XRW) ? PAGE_EXECUTE_READWRITE : ( \
                                    PAGE_NOACCESS \
                                ) \
                            ) \
                        ) \
                    ) \
                ) \
            ) \
        ) \
    ) \
)
#else
#include <sys/mman.h>
#include <unistd.h>

#define PROT_TO_OSPROT(x) ( \
    (x == PATCH_ADDRESS_PROT_NA) ? (PROT_NONE) : ( \
        (x == PATCH_ADDRESS_PROT_R) ? (PROT_READ) : ( \
            (x == PATCH_ADDRESS_PROT_W) ? (PROT_WRITE) : ( \
                (x == PATCH_ADDRESS_PROT_RW) ? (PROT_READ | PROT_WRITE) : ( \
                    (x == PATCH_ADDRESS_PROT_X) ? (PROT_EXEC) : ( \
                        (x == PATCH_ADDRESS_PROT_XR) ? (PROT_EXEC | PROT_READ) : ( \
                            (x == PATCH_ADDRESS_PROT_XW) ? (PROT_EXEC | PROT_WRITE) : ( \
                                (x == PATCH_ADDRESS_PROT_XRW) ? (PROT_EXEC | PROT_READ | PROT_WRITE) : ( \
                                    (PROT_NONE) \
                                ) \
                            ) \
                        ) \
                    ) \
                ) \
            ) \
        ) \
    ) \
)
#endif

static size_t patch_address_get_page_size() {
#ifdef _WIN32
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwPageSize;
#else
    return getpagesize();
#endif
}

void patch_address(void *address, void *data, size_t size, patch_address_prot_t prot) {
    int os_prot = PROT_TO_OSPROT(prot);
    size_t page_size = patch_address_get_page_size();
    uintptr_t aligned_address = (uintptr_t)address & ~(page_size - 1);
    size_t aligned_size = size + (size_t)((uintptr_t)address - aligned_address);
    if (aligned_size % page_size != 0) {
        aligned_size = (aligned_size & ~(page_size - 1)) + page_size;
    }
#ifdef _WIN32
    DWORD old_protect;
    VirtualProtect((void *)aligned_address, aligned_size, PAGE_READWRITE, &old_protect);
#else
    mprotect((void *)aligned_address, aligned_size, PROT_READ | PROT_WRITE);
#endif
    memcpy(address, data, size);
#ifdef _WIN32
    VirtualProtect((void *)aligned_address, aligned_size, os_prot, &old_protect);
#else
    mprotect((void *)aligned_address, aligned_size, os_prot);
#endif
#if !defined(_MSC_VER) && (defined(__arm__) || defined(_M_ARM))
    __builtin___clear_cache((void *)aligned_address, aligned_size);
#endif
}
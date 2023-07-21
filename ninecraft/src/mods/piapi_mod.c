#include <ninecraft/minecraft.h>
#include <ninecraft/version_ids.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/mods/piapi_mod.h>
#include <ninecraft/patch/detours.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

/*
    This mod enables the Minecraft Pi Edition API.
*/

extern int version_id;

__attribute__((__aligned__(4))) static uint8_t _levelgenerated_arm_trampoline[] = {
    0x00, 0xbf, 0x00, 0xbf,
    0x00, 0xbf, 0x00, 0xbf,
    0xdf, 0xf8, 0x00, 0xf0,
    0x00, 0xbf, 0x00, 0xbf
};

void piapi_mod_level_generated_injection(void *minecraft) {
#ifdef __i386__
    minecraft_level_generated(minecraft);
#endif
#ifdef __arm__
    ((void (*)(void *))(_levelgenerated_arm_trampoline + 1))(minecraft);
#endif
    size_t minecraft_command_server_offset;
    if (version_id == version_id_0_7_0 || version_id == version_id_0_7_1) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_0;
    } else if (version_id == version_id_0_6_1 || version_id == version_id_0_6_0) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_6_1;
    } else if (version_id == version_id_0_7_2) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_2;
    }
    void *command_server = *(void **)(minecraft + minecraft_command_server_offset);
    if (command_server != NULL) {
        command_server_deconstruct(command_server);
        if (command_server) {
            free(command_server);
        }
    }
    command_server = malloc(0x4c);
    command_server_construct(command_server, minecraft);
    *(void **)(minecraft + minecraft_command_server_offset) = command_server;
    command_server_init(command_server, 4711);
}

void piapi_mod_inject(int version_id) {
#ifdef __i386__
    if (version_id >= version_id_0_6_0 && version_id <= version_id_0_7_1) {
        DETOUR(minecraft_tick + 188, (void *)piapi_mod_level_generated_injection, false);
    } else if (version_id == version_id_0_7_2) {
        DETOUR(minecraft_tick + 197, (void *)piapi_mod_level_generated_injection, false);
    }
#endif
#ifdef __arm__
    if (version_id >= version_id_0_6_0 && version_id <= version_id_0_6_1) {
        memcpy(_levelgenerated_arm_trampoline, (uint32_t)minecraft_level_generated - 1, 8);
        *(uint32_t *)(_levelgenerated_arm_trampoline + 12) = ((uint32_t)minecraft_level_generated) + 8;
        DETOUR(minecraft_level_generated, (void *)piapi_mod_level_generated_injection, true);
        long page_size = sysconf(_SC_PAGESIZE);
	    void *protect = (void *)(((uintptr_t)_levelgenerated_arm_trampoline) & -page_size);
	    mprotect(protect, 16, PROT_READ | PROT_WRITE | PROT_EXEC);
    }
#endif
}
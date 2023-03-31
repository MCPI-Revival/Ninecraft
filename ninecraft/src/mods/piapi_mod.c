#include <ninecraft/minecraft.h>
#include <ninecraft/version_ids.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/mods/piapi_mod.h>
#include <ninecraft/patch/detours.h>
#include <stddef.h>
#include <stdbool.h>

/*
    This mod enables the Minecraft Pi Edition API.
*/

extern int version_id;

void piapi_mod_level_generated_injection(void *minecraft) {
    minecraft_level_generated(minecraft);
    size_t minecraft_command_server_offset;
    if (version_id == version_id_0_7_0) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_0;
    } else if (version_id == version_id_0_6_1) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_6_1;
    } else if (version_id == version_id_0_7_2) {
        puts("yes");
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
    if (version_id == version_id_0_6_1 || version_id == version_id_0_7_0) {
        DETOUR(minecraft_tick + 188, (void *)piapi_mod_level_generated_injection, false);
    } else if (version_id == version_id_0_7_2) {
        DETOUR(minecraft_tick + 197, (void *)piapi_mod_level_generated_injection, false);
    }
#endif
}
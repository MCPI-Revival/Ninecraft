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
    void *command_server = *(void **)(minecraft + (version_id == version_id_0_7 ? MINECRAFT_COMMANDSERVER_OFFSET_0_7 : MINECRAFT_COMMANDSERVER_OFFSET_0_6));
    if (command_server != NULL) {
        command_server_deconstruct(command_server);
        android_alloc_operator_delete(command_server);
    }
    command_server = android_alloc_operator_new(0x4c);
    command_server_construct(command_server, minecraft);
    *(void **)(minecraft + (version_id == version_id_0_7 ? MINECRAFT_COMMANDSERVER_OFFSET_0_7 : MINECRAFT_COMMANDSERVER_OFFSET_0_6)) = command_server;
    command_server_init(command_server, 4711);
}

void piapi_mod_inject(int version_id) {  
    if (version_id == version_id_0_6 || version_id == version_id_0_7) { 
        #ifdef __i386__
        DETOUR(minecraft_tick + 188, (void *)piapi_mod_level_generated_injection, false);
        #endif
    }
}
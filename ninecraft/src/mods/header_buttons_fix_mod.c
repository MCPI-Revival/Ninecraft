#include <ninecraft/mods/header_buttons_fix_mod.h>
#include <ancmp/android_dlfcn.h>
#include <ninecraft/version_ids.h>

/*
    This mod fixes the missing menu buttons issue
    for mcpe 0.9.0-0.9.5
*/

#if defined(__i386__) || defined(_M_IX86)

#define INST_NOP 0x9090
#define OFFSET_FOR_0_9_0 79
#define OFFSET_FOR_0_9_1 79
#define OFFSET_FOR_0_9_2 79
#define OFFSET_FOR_0_9_3 79
#define OFFSET_FOR_0_9_4 79
#define OFFSET_FOR_0_9_5 79

#else
#if defined(__arm__) || defined(_M_ARM) 

#define INST_NOP 0xbf00
#define OFFSET_FOR_0_9_0 43
#define OFFSET_FOR_0_9_1 43
#define OFFSET_FOR_0_9_2 43
#define OFFSET_FOR_0_9_3 43
#define OFFSET_FOR_0_9_4 43
#define OFFSET_FOR_0_9_5 43

#endif
#endif

void header_buttons_fix_mod_inject(void *handle, int version_id) {
    if (version_id >= version_id_0_9_0 && version_id <= version_id_0_9_5) {
        char *play_screen_reset_base_buttons = (char *)android_dlsym(handle, "_ZN10PlayScreen16resetBaseButtonsEv");
        if (play_screen_reset_base_buttons) {
            if (version_id == version_id_0_9_0) {
                *(short *)(play_screen_reset_base_buttons + OFFSET_FOR_0_9_0) = INST_NOP;
            } else if (version_id == version_id_0_9_1) {
                *(short *)(play_screen_reset_base_buttons + OFFSET_FOR_0_9_1) = INST_NOP;
            } else if (version_id == version_id_0_9_2) {
                *(short *)(play_screen_reset_base_buttons + OFFSET_FOR_0_9_2) = INST_NOP;
            } else if (version_id == version_id_0_9_3) {
                *(short *)(play_screen_reset_base_buttons + OFFSET_FOR_0_9_3) = INST_NOP;
            } else if (version_id == version_id_0_9_4) {
                *(short *)(play_screen_reset_base_buttons + OFFSET_FOR_0_9_4) = INST_NOP;
            } else if (version_id == version_id_0_9_5) {
                *(short *)(play_screen_reset_base_buttons + OFFSET_FOR_0_9_5) = INST_NOP;
            }
        }
    }
}
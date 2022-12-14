#ifndef NINECRAFT_APP_PLATFORM_H
#define NINECRAFT_APP_PLATFORM_H

#include <string.h>
#include <dlfcn.h>
#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/gfx/textures.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/android/android_vector.h>

typedef struct {
    void **vtable;
    void *handle;
    int status;
    int version_id;
} AppPlatform_linux;

typedef struct {
    char *data;
    int size;
} asset_file;

typedef enum {
    did_new_world = 1,
    did_options = 3,
    did_rename_world = 4
} platform_dialogue_id;

typedef struct {
    android_string_t name;
    android_string_t seed;
    char filler[0x1000];
} user_input;

extern void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle, int version_id);

extern void AppPlatform_linux$_tick(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$buyGame(AppPlatform_linux *app_platform);
 
extern int32_t AppPlatform_linux$checkLicense(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$createUserInput(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$finish(AppPlatform_linux *app_platform);

extern android_string_t AppPlatform_linux$getDateString(AppPlatform_linux *app_platform, unsigned int seconds);

extern int32_t AppPlatform_linux$getKeyFromKeyCode(AppPlatform_linux *app_platform, unsigned int key_code, unsigned int meta_state, unsigned int device_id);

extern android_vector_t AppPlatform_linux$getOptionStrings(AppPlatform_linux *app_platform);

extern float AppPlatform_linux$getPixelsPerMillimeter(AppPlatform_linux *app_platform);

extern android_string_t AppPlatform_linux$getPlatformStringVar(AppPlatform_linux *app_platform, int zero);

extern int AppPlatform_linux$getScreenHeight(AppPlatform_linux *app_platform);

extern int AppPlatform_linux$getScreenWidth(AppPlatform_linux *app_platform);

extern android_vector_t AppPlatform_linux$getUserInput(AppPlatform_linux *app_platform);

extern int AppPlatform_linux$getUserInputStatus(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$hasBuyButtonWhenInvalidLicense(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$hideKeyboard(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$isKeyboardVisible(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$isNetworkEnabled(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$isPowerVR(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$isTouchscreen(AppPlatform_linux *app_platform);

extern texture_data_t AppPlatform_linux$loadTexture(AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha);

extern void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, android_string_t *sound_name, float volume, float pitch);

extern asset_file AppPlatform_linux$readAssetFile(AppPlatform_linux *app_platform, android_string_t *path_str);

extern void AppPlatform_linux$saveScreenshot(AppPlatform_linux *app_platform, android_string_t *path, int32_t width, int32_t height);

extern void AppPlatform_linux$showDialog(AppPlatform_linux *app_platform, int32_t dialog_id);

extern void AppPlatform_linux$showKeyboard(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$uploadPlatformDependentData(AppPlatform_linux *app_platform, int32_t size, void *data);

extern void AppPlatform_linux$vibrate(AppPlatform_linux *app_platform, int32_t milliseconds);

extern void AppPlatform_linux$destroy(AppPlatform_linux *app_platform);

#endif
#ifndef NINECRAFT_APP_PLATFORM_H
#define NINECRAFT_APP_PLATFORM_H

#include <string.h>
#include <dlfcn.h>
#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/gfx/textures.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/android/android_vector.h>
#include <ninecraft/options.h>
#include <ninecraft/ninecraft_defs.h>

typedef struct {
    void **vtable;
    void *handle;
    int status;
    int version_id;
    ninecraft_options_t *options;
} AppPlatform_linux;

typedef struct {
    char *data;
    int size;
} asset_file;

typedef enum {
    did_new_world = 1,
    did_chat = 2,
    did_options = 3,
    did_rename_world = 4
} platform_dialogue_id;

typedef struct {
    android_string_t name;
    android_string_t seed;
    char filler[0x1000];
} user_input;

typedef struct {
    android_string_gnu_t unknown0;
    android_string_gnu_t unknown1;
    android_string_gnu_t unknown2;
    android_string_gnu_t unknown3;
} login_information_t;

void AppPlatform_linux$saveImage(AppPlatform_linux *app_platform, android_string_gnu_t *resource_path, android_string_gnu_t *pixels, int width, int height);

void AppPlatform_linux$swapBuffers(AppPlatform_linux *app_platform);

NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$getModelName, AppPlatform_linux *app_platform);

void AppPlatform_linux$captureScreen(AppPlatform_linux *app_platform, int width, int height, bool do_capture);

int AppPlatform_linux$shareOpenGLContext(AppPlatform_linux *app_platform);

android_vector_t AppPlatform_linux$getBroadcastAddresses(AppPlatform_linux *app_platform);

size_t AppPlatform_linux$getTotalMemory(AppPlatform_linux *app_platform);

void AppPlatform_linux$updateTextBoxText(AppPlatform_linux *app_platform, android_string_t *text);

bool AppPlatform_linux$hasIDEProfiler(AppPlatform_linux *app_platform);

void AppPlatform_linux$loadTGA(AppPlatform_linux *app_platform, image_data_t *image, android_string_t *resource_path, bool alpha);

void AppPlatform_linux$loadTGA_0_9_0(AppPlatform_linux *app_platform, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha);

NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$getImagePath, AppPlatform_linux *app_platform, android_string_t *resource_path, bool is_full);

void AppPlatform_linux$loadPNG(AppPlatform_linux *app_platform, image_data_t *image, android_string_t *resource_path, bool alpha);

void AppPlatform_linux$loadPNG_0_9_0(AppPlatform_linux *app_platform, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha);

login_information_t AppPlatform_linux$getLoginInformation(AppPlatform_linux *app_platform);

void AppPlatform_linux$setLoginInformation(AppPlatform_linux *app_platform, login_information_t *info);

void AppPlatform_linux$statsTrackData(AppPlatform_linux *app_platform, android_string_t *unknown0, android_string_t *unknown1);

void AppPlatform_linux$updateStatsUserData(AppPlatform_linux *app_platform, android_string_t *unknown0, android_string_t *unknown1);

void AppPlatform_linux$initWithActivity(AppPlatform_linux *app_platform, void *activity);

void AppPlatform_linux$openLoginWindow(AppPlatform_linux *app_platform);

bool AppPlatform_linux$supportsTouchscreen(AppPlatform_linux *app_platform);

bool AppPlatform_linux$supportsVibration(AppPlatform_linux *app_platform);

void AppPlatform_linux$getSessionIDAndRefreshToken(AppPlatform_linux *app_platform, android_string_t *session_id, android_string_t *refresh_token);

void AppPlatform_linux$setSessionIDAndRefreshToken(AppPlatform_linux *app_platform, android_string_t *session_id, android_string_t *refresh_token);

void AppPlatform_linux$clearSessionIDAndRefreshToken(AppPlatform_linux *app_platform);

void AppPlatform_linux$webRequest(AppPlatform_linux *app_platform, int unknown0, long long unknown1, android_string_t *unknown2, android_string_t *unknown3, android_string_t *unknown4);

int AppPlatform_linux$getWebRequestStatus(AppPlatform_linux *app_platform, int unknown0);

void AppPlatform_linux$getWebRequestContent(AppPlatform_linux *app_platform, int unknown0);

void AppPlatform_linux$abortWebRequest(AppPlatform_linux *app_platform, int unknown0);

extern void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle, int version_id, ninecraft_options_t *options);

extern void AppPlatform_linux$_tick(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$buyGame(AppPlatform_linux *app_platform);

extern int32_t AppPlatform_linux$checkLicense(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$createUserInput(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$finish(AppPlatform_linux *app_platform);

extern NINECRAFT_CSR_FUNCDEF(android_string_stlp_t, AppPlatform_linux$getDateStringSTLP, AppPlatform_linux *app_platform, unsigned int seconds);

extern NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$getDateStringGNU, AppPlatform_linux *app_platform, unsigned int seconds);

extern int32_t AppPlatform_linux$getKeyFromKeyCode(AppPlatform_linux *app_platform, unsigned int key_code, unsigned int meta_state, unsigned int device_id);

extern android_vector_t AppPlatform_linux$getOptionStrings(AppPlatform_linux *app_platform);

extern float AppPlatform_linux$getPixelsPerMillimeter(AppPlatform_linux *app_platform);

extern NINECRAFT_CSR_FUNCDEF(android_string_stlp_t, AppPlatform_linux$getPlatformStringVarSTLP, AppPlatform_linux *app_platform, int zero);

extern NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$getPlatformStringVarGNU, AppPlatform_linux *app_platform, int zero);

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

extern texture_data_old_t AppPlatform_linux$loadTextureOld(AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha);

extern void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, android_string_t *sound_name, float volume, float pitch);

extern asset_file AppPlatform_linux$readAssetFile(AppPlatform_linux *app_platform, android_string_t *path_str);

extern NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$readAssetFile_0_9_0, AppPlatform_linux *app_platform, android_string_t *path_str);

extern void AppPlatform_linux$saveScreenshot(AppPlatform_linux *app_platform, android_string_t *path, int32_t width, int32_t height);

extern void AppPlatform_linux$showDialog(AppPlatform_linux *app_platform, int32_t dialog_id);

extern void AppPlatform_linux$showKeyboard(AppPlatform_linux *app_platform);

void AppPlatform_linux$showKeyboard2(AppPlatform_linux *app_platform, bool show);

extern void AppPlatform_linux$uploadPlatformDependentData(AppPlatform_linux *app_platform, int32_t size, void *data);

extern void AppPlatform_linux$vibrate(AppPlatform_linux *app_platform, int32_t milliseconds);

extern void AppPlatform_linux$destroy(AppPlatform_linux *app_platform);

#endif
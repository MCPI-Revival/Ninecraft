#ifndef NINECRAFT_APP_PLATFORM_H
#define NINECRAFT_APP_PLATFORM_H

#include <string.h>
#include <ancmp/android_dlfcn.h>
#include <ninecraft/gfx/textures.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/android/android_vector.h>
#include <ninecraft/options.h>
#include <ancmp/abi_fix.h>
#include <ninecraft/app_platform.h>

typedef struct {
    void **vtable;
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

typedef union {
    struct {
        android_string_gnu_t unknown0;
        android_string_gnu_t unknown1;
        android_string_gnu_t unknown2;
        android_string_gnu_t unknown3;
    } gnu;
    struct {
        android_string_stlp_t unknown0;
        android_string_stlp_t unknown1;
        android_string_stlp_t unknown2;
        android_string_stlp_t unknown3;
    } stlp;
} login_information_t;

extern ninecraft_options_t platform_options;
extern bool is_keyboard_visible;

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getDataUrl);
void AppPlatform_linux$getDataUrl(android_string_t *ret, AppPlatform_linux *app_platform);

void AppPlatform_linux$saveImage(AppPlatform_linux *app_platform, android_string_t *resource_path, android_string_t *pixels, int width, int height);

void AppPlatform_linux$swapBuffers(AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getModelName);
void AppPlatform_linux$getModelName(android_string_t *ret, AppPlatform_linux *app_platform);

void AppPlatform_linux$captureScreen(AppPlatform_linux *app_platform, int width, int height, bool do_capture);

int AppPlatform_linux$shareOpenGLContext(AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getBroadcastAddresses);
void AppPlatform_linux$getBroadcastAddresses(android_vector_t *ret, AppPlatform_linux *app_platform);

uint64_t AppPlatform_linux$getAvailableMemory(AppPlatform_linux *app_platform);

uint64_t AppPlatform_linux$getTotalMemory(AppPlatform_linux *app_platform);

void AppPlatform_linux$updateTextBoxText(AppPlatform_linux *app_platform, android_string_t *text);

bool AppPlatform_linux$hasIDEProfiler(AppPlatform_linux *app_platform);

void AppPlatform_linux$loadTGA(AppPlatform_linux *app_platform, image_data_t *image, android_string_t *resource_path, bool alpha);

void AppPlatform_linux$loadTGA_0_9_0(AppPlatform_linux *app_platform, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getImagePath);
void AppPlatform_linux$getImagePath(android_string_t *ret, AppPlatform_linux *app_platform, android_string_t *resource_path, bool is_full);

void AppPlatform_linux$loadPNG(AppPlatform_linux *app_platform, image_data_t *image, android_string_t *resource_path, bool alpha);

void AppPlatform_linux$loadPNG_0_9_0(AppPlatform_linux *app_platform, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getLoginInformation);
void AppPlatform_linux$getLoginInformation(login_information_t *ret, AppPlatform_linux *app_platform);

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

extern void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle, int version_id);

extern void AppPlatform_linux$_tick(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$buyGame(AppPlatform_linux *app_platform);

extern int32_t AppPlatform_linux$checkLicense(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$createUserInput(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$finish(AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getDateString);
extern void AppPlatform_linux$getDateString(android_string_t *ret, AppPlatform_linux *app_platform, unsigned int seconds);

extern int32_t AppPlatform_linux$getKeyFromKeyCode(AppPlatform_linux *app_platform, unsigned int key_code, unsigned int meta_state, unsigned int device_id);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings);
void AppPlatform_linux$getOptionStrings(android_vector_t *ret, AppPlatform_linux *app_platform);

extern float AppPlatform_linux$getPixelsPerMillimeter(AppPlatform_linux *app_platform) FLOAT_ABI_FIX;

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar);
extern void AppPlatform_linux$getPlatformStringVar(android_string_t *ret, AppPlatform_linux *app_platform, int zero);

extern int AppPlatform_linux$getScreenHeight(AppPlatform_linux *app_platform);

extern int AppPlatform_linux$getScreenWidth(AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getUserInput);
extern void AppPlatform_linux$getUserInput(android_vector_t *ret, AppPlatform_linux *app_platform);

extern int AppPlatform_linux$getUserInputStatus(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$hasBuyButtonWhenInvalidLicense(AppPlatform_linux *app_platform);

extern void AppPlatform_linux$hideKeyboard(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$isKeyboardVisible(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$isNetworkEnabled(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$isPowerVR(AppPlatform_linux *app_platform);

extern bool AppPlatform_linux$isTouchscreen(AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$loadTexture);
extern void AppPlatform_linux$loadTexture(texture_data_t *ret, AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$loadTextureOld);
extern void AppPlatform_linux$loadTextureOld(texture_data_old_t *ret, AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha);

extern void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, android_string_t *sound_name, float volume, float pitch) FLOAT_ABI_FIX;

EXTERN_SYSV_WRAPPER(AppPlatform_linux$readAssetFile);
extern void AppPlatform_linux$readAssetFile(asset_file *ret, AppPlatform_linux *app_platform, android_string_t *path_str);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$readAssetFile_0_9_0);
extern void AppPlatform_linux$readAssetFile_0_9_0(android_string_t *ret, AppPlatform_linux *app_platform, android_string_t *path_str);

extern void AppPlatform_linux$saveScreenshot(AppPlatform_linux *app_platform, android_string_t *path, int32_t width, int32_t height);

extern void AppPlatform_linux$showDialog(AppPlatform_linux *app_platform, int32_t dialog_id);

extern void AppPlatform_linux$showKeyboard(AppPlatform_linux *app_platform);

void AppPlatform_linux$showKeyboard2(AppPlatform_linux *app_platform, bool show);

extern void AppPlatform_linux$uploadPlatformDependentData(AppPlatform_linux *app_platform, int32_t size, void *data);

extern void AppPlatform_linux$vibrate(AppPlatform_linux *app_platform, int32_t milliseconds);

extern void AppPlatform_linux$destroy(AppPlatform_linux *app_platform);

android_string_t *AppPlatform_linux$getSystemRegion(AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getGraphicsVendor);
void AppPlatform_linux$getGraphicsVendor(android_string_t *ret, AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getGraphicsRenderer);
void AppPlatform_linux$getGraphicsRenderer(android_string_t *ret, AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getGraphicsVersion);
void AppPlatform_linux$getGraphicsVersion(android_string_t *ret, AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getGraphicsExtensions);
void AppPlatform_linux$getGraphicsExtensions(android_string_t *ret, AppPlatform_linux *app_platform);

android_string_t *AppPlatform_linux$getExternalStoragePath(AppPlatform_linux *app_platform);

android_string_t *AppPlatform_linux$getInternalStoragePath(AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getApplicationId);
void AppPlatform_linux$getApplicationId(android_string_t *ret, AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$getDeviceId);
void AppPlatform_linux$getDeviceId(android_string_t *ret, AppPlatform_linux *app_platform);

EXTERN_SYSV_WRAPPER(AppPlatform_linux$createUUID);
void AppPlatform_linux$createUUID(android_string_t *ret, AppPlatform_linux *app_platform);

bool AppPlatform_linux$isFirstSnoopLaunch(AppPlatform_linux *app_platform);

bool AppPlatform_linux$hasHardwareInformationChanged(AppPlatform_linux *app_platform);

bool AppPlatform_linux$isTablet(AppPlatform_linux *app_platform);

void AppPlatform_linux$pickImage(AppPlatform_linux *__this, image_picking_callback_0_11_0_t *callback);

#endif
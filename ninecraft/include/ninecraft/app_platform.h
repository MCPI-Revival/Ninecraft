#pragma once

#include <ninecraft/android/android_string.h>
#include <ninecraft/android/android_vector.h>
#include <ninecraft/gfx/textures.h>
#include <stdbool.h>

typedef struct {
    char *data;
    int size;
} minecraft_asset_t;

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
} minecraft_login_info_t;

typedef struct {
    void **vtable;
    unsigned char is_keyboard_hidden;
    void *u0;
    void *u1;
    void *u2;
    void *u3;
    void *u4;
    void *u5;
    char filler[0x100];
} app_platform_0_9_0_t;

typedef struct {
    void (*__destroy0)(void *__this);
    void (*__destroy1)(void *__this);
    void (*onImagePickingSuccess)(void *__this, android_string_t *resource_path);
    void (*onImagePickingCanceled)(void *__this);
} image_picking_callback_vtable_0_11_0_t;

typedef struct {
    image_picking_callback_vtable_0_11_0_t *vtable;
} image_picking_callback_0_11_0_t;

typedef struct {
    void (*__destroy0)(void *__this);
    void (*__destroy1)(void *__this);
    void (*saveScreenshot)(void *__this, android_string_t *resource_path, int width, int height);
    android_string_t (*getImagePath)(void *__this, android_string_t *resource_path, bool is_full);
    void (*loadPNG)(void *__this, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha);
    void (*loadTGA)(void *__this, image_data_0_9_0_t *image, android_string_t *resource_path);
    void (*playSound)(void *__this, android_string_t *resource_path, float volume, float pitch);
    void (*showDialog)(void *__this, int dialog_id);
    void (*createUserInput)(void *__this);
    int (*getUserInputStatus)(void *__this);
    android_vector_t (*getUserInput)(void *__this);
    android_string_t (*getDateString)(void *__this, int ms);
    int (*checkLicense)(void *__this);
    bool (*hasBuyButtonWhenInvalidLicense)(void *__this);
    void (*uploadPlatformDependentData)(void *__this, int length, void *data);
    minecraft_asset_t (*readAssetFile)(void *__this, android_string_t *resource_path);
    void (*_tick)(void *__this);
    int (*getScreenWidth)(void *__this);
    int (*getScreenHeight)(void *__this);
    float (*getPixelsPerMillimeter)(void *__this);
    bool (*isNetworkEnabled)(void *__this, bool set);
    void (*openLoginWindow)(void *__this);
    bool (*isPowerVR)(void *__this);
    int (*getKeyFromKeyCode)(void *__this, int code, int meta, int dev_id);
    void (*buyGame)(void *__this);
    void (*finish)(void *__this);
    bool (*supportsTouchscreen)(void *__this);
    bool (*hasIDEProfiler)(void *__this);
    bool (*supportsVibration)(void *__this);
    void (*vibrate)(void *__this, int ms);
    android_string_t (*getPlatformStringVar)(void *__this, int reserved);
    void (*showKeyboard)(void *__this, android_string_t *u0, int u1, bool set);
    void (*hideKeyboard)(void *__this);
    void (*updateTextBoxText)(void *__this, android_string_t *text);
    bool (*isKeyboardVisible)(void *__this);
    minecraft_login_info_t (*getLoginInformation)(void *__this);
    void (*setLoginInformation)(void *__this, minecraft_login_info_t *info);
    void (*clearSessionIDAndRefreshToken)(void *__this);
    void (*statsTrackData)(void *__this, android_string_t *u0, android_string_t *u1);
    void (*updateStatsUserData)(void *__this, android_string_t *u0, android_string_t *u1);
    uint64_t (*getAvailableMemory)(void *__this);
    android_vector_t (*getBroadcastAddresses)(void *__this);
} app_platform_vtable_0_9_0_t;

typedef struct {
    void (*__destroy0)(void *__this);
    void (*__destroy1)(void *__this);
    android_string_t (*getImagePath)(void *__this, android_string_t *resource_path, bool is_full);
    void (*loadPNG)(void *__this, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha);
    void (*loadTGA)(void *__this, image_data_0_9_0_t *image, android_string_t *resource_path);
    void (*playSound)(void *__this, android_string_t *resource_path, float volume, float pitch);
    void (*showDialog)(void *__this, int dialog_id);
    void (*createUserInput)(void *__this);
    int (*getUserInputStatus)(void *__this);
    android_vector_t (*getUserInput)(void *__this);
    android_string_t (*getDateString)(void *__this, int ms);
    int (*checkLicense)(void *__this);
    bool (*hasBuyButtonWhenInvalidLicense)(void *__this);
    void (*saveImage)(void *__this, android_string_t *resource_path, android_string_t *name, int width, int height);
    void (*uploadPlatformDependentData)(void *__this, int length, void *data);
    minecraft_asset_t (*readAssetFile)(void *__this, android_string_t *resource_path);
    void (*_tick)(void *__this);
    int (*getScreenWidth)(void *__this);
    int (*getScreenHeight)(void *__this);
    float (*getPixelsPerMillimeter)(void *__this);
    bool (*isNetworkEnabled)(void *__this, bool set);
    void (*openLoginWindow)(void *__this);
    bool (*isPowerVR)(void *__this);
    int (*getKeyFromKeyCode)(void *__this, int code, int meta, int dev_id);
    void (*buyGame)(void *__this);
    void (*finish)(void *__this);
    void (*swapBuffers)(void *__this);
    bool (*supportsTouchscreen)(void *__this);
    bool (*hasIDEProfiler)(void *__this);
    bool (*supportsVibration)(void *__this);
    void (*vibrate)(void *__this, int ms);
    android_string_t (*getPlatformStringVar)(void *__this, int reserved);
    void (*showKeyboard)(void *__this, android_string_t *u0, int u1, bool set);
    void (*hideKeyboard)(void *__this);
    void (*updateTextBoxText)(void *__this, android_string_t *text);
    bool (*isKeyboardVisible)(void *__this);
    minecraft_login_info_t (*getLoginInformation)(void *__this);
    void (*setLoginInformation)(void *__this, minecraft_login_info_t *info);
    void (*clearSessionIDAndRefreshToken)(void *__this);
    void (*statsTrackData)(void *__this, android_string_t *u0, android_string_t *u1);
    void (*captureScreen)(int width, int height, bool do_capture);
    uint64_t (*getAvailableMemory)(void *__this);
    android_vector_t (*getBroadcastAddresses)(void *__this);
    android_string_t (*getModelName)(void *__this);
} app_platform_vtable_0_10_0_t;

typedef struct {
    void (*__destroy0)(void *__this);
    void (*__destroy1)(void *__this);
    android_string_t (*getImagePath)(void *__this, android_string_t *resource_path, bool is_full);
    void (*loadPNG)(void *__this, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha);
    void (*loadTGA)(void *__this, image_data_0_9_0_t *image, android_string_t *resource_path);
    void (*savePNG)(void *__this, image_data_0_9_0_t *image, android_string_t *resource_path);
    int (*getKeyFromKeyCode)(void *__this, int code, int meta, int dev_id);
    void (*showKeyboard)(void *__this, android_string_t *u0, int u1, bool set);
    void (*hideKeyboard)(void *__this);
    void (*captureScreen)(void *__this, int width, int height, unsigned int px_width, bool do_capture);
    void (*swapBuffers)(void *__this);
    android_string_t (*getSystemRegion)(void *__this);
    android_string_t (*getGraphicsVendor)(void *__this);
    android_string_t (*getGraphicsRenderer)(void *__this);
    android_string_t (*getGraphicsVersion)(void *__this);
    android_string_t (*getGraphicsExtensions)(void *__this);
    void (*pickImage)(void *__this, image_picking_callback_0_11_0_t *callback);
    void (*setSleepEnabled)(void *__this, bool set);
    android_string_t (*getExternalStoragePath)(void *__this);
    android_string_t (*getInternalStoragePath)(void *__this);
    void (*playSound)(void *__this, android_string_t *resource_path, float volume, float pitch);
    void (*showDialog)(void *__this, int);
    void (*createUserInput)(void *__this);
    int (*getUserInputStatus)(void *__this);
    android_vector_t (*getUserInput)(void *__this);
    void (*_tick)(void *__this);
    int (*getScreenWidth)(void *__this);
    int (*getScreenHeight)(void *__this);
    float (*getPixelsPerMillimeter)(void *__this);
    void (*openLoginWindow)(void *__this);
    void (*updateTextBoxText)(void *__this, android_string_t *text);
    bool (*isKeyboardVisible)(void *__this);
    minecraft_login_info_t (*getLoginInformation)(void *__this);
    void (*setLoginInformation)(void *__this, minecraft_login_info_t *info);
    void (*clearSessionIDAndRefreshToken)(void *__this);
    bool (*supportsVibration)(void *__this);
    void (*vibrate)(void *__this, int ms);
    minecraft_asset_t (*readAssetFile)(void *__this, android_string_t *resource_path);
    void (*listAssetFilesIn)(void *__this, android_string_t *, android_string_t *);
    android_string_t (*getDateString)(void *__this, int ms);
    int (*checkLicense)(void *__this);
    bool (*hasBuyButtonWhenInvalidLicense)(void *__this);
    void (*uploadPlatformDependentData)(void *__this, int length, void *data);
    bool (*isNetworkEnabled)(void *__this, bool set);
    bool (*isPowerVR)(void *__this);
    void (*buyGame)(void *__this);
    void (*finish)(void *__this);
    bool (*supportsTouchscreen)(void *__this);
    bool (*hasIDEProfiler)(void *__this);
    android_string_t (*getPlatformStringVar)(void *__this, int reserved);
    android_string_t (*getApplicationId)(void *__this);
    uint64_t (*getAvailableMemory)(void *__this);
    android_vector_t (*getBroadcastAddresses)(void *__this);
    android_string_t (*getModelName)(void *__this);
    android_string_t (*getDeviceId)(void *__this);
    android_string_t (*createUUID)(void *__this);
    bool (*isFirstSnoopLaunch)(void *__this);
    bool (*hasHardwareInformationChanged)(void *__this);
    bool (*isTablet)(void *__this);
    void (*registerUriListener)(void *__this, void *uri_listener);
    void (*unregisterUriListener)(void *__this, void *uri_listener);
} app_platform_vtable_0_11_0_t;

extern app_platform_vtable_0_9_0_t platform_vtable_0_9_0;
extern app_platform_vtable_0_10_0_t platform_vtable_0_10_0;
extern app_platform_vtable_0_11_0_t platform_vtable_0_11_0;
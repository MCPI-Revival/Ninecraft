#pragma once

#include <dlfcn.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <hybris/dlfcn.h>
#include <hybris/hook.h>
#include <hybris/jb/linker.h>
#include "textures.hpp"
#include <ninecraft/android_string.hpp>

typedef struct {
    void **vtable;
    unsigned char filler[0xd0];
    void *handle;
} AppPlatform_linux;

typedef struct {
    char *data;
    int size;
} asset_file;

enum class TextureFormat {
    U8888, U888, U565, U5551, U4444, C565, C5551, C4444
};

void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle);

void AppPlatform_linux$_tick(AppPlatform_linux *app_platform);

void AppPlatform_linux$buyGame(AppPlatform_linux *app_platform);
 
int32_t AppPlatform_linux$checkLicense(AppPlatform_linux *app_platform);

void AppPlatform_linux$createUserInput(AppPlatform_linux *app_platform);

void AppPlatform_linux$finish(AppPlatform_linux *app_platform);

android_string AppPlatform_linux$getDateString(AppPlatform_linux *app_platform, unsigned int seconds);

int32_t AppPlatform_linux$getKeyFromKeyCode(AppPlatform_linux *app_platform, unsigned int key_code, unsigned int meta_state, unsigned int device_id);

int AppPlatform_linux$getOptionStrings(AppPlatform_linux *app_platform);

float AppPlatform_linux$getPixelsPerMillimeter(AppPlatform_linux *app_platform);

android_string AppPlatform_linux$getPlatformStringVar(AppPlatform_linux *app_platform, int zero);

int AppPlatform_linux$getScreenHeight(AppPlatform_linux *app_platform);

int AppPlatform_linux$getScreenWidth(AppPlatform_linux *app_platform);

android_string *AppPlatform_linux$getUserInput(AppPlatform_linux *app_platform);

int AppPlatform_linux$getUserInputStatus(AppPlatform_linux *app_platform);

bool AppPlatform_linux$hasBuyButtonWhenInvalidLicense(AppPlatform_linux *app_platform);

void AppPlatform_linux$hideKeyboard(AppPlatform_linux *app_platform);

bool AppPlatform_linux$isKeyboardVisible(AppPlatform_linux *app_platform);

bool AppPlatform_linux$isNetworkEnabled(AppPlatform_linux *app_platform);

bool AppPlatform_linux$isPowerVR(AppPlatform_linux *app_platform);

bool AppPlatform_linux$isTouchscreen(AppPlatform_linux *app_platform);

TextureData AppPlatform_linux$loadTexture(AppPlatform_linux *app_platform, void *path_str, bool alpha);

void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, const android_string& sound_name, float volume, float pitch);

asset_file AppPlatform_linux$readAssetFile(AppPlatform_linux *app_platform, void *path_str);

void AppPlatform_linux$saveScreenshot(AppPlatform_linux *app_platform, const android_string& path, int32_t width, int32_t height);

void AppPlatform_linux$showDialog(AppPlatform_linux *app_platform, int32_t dialog_id);

void AppPlatform_linux$showKeyboard(AppPlatform_linux *app_platform);

void AppPlatform_linux$uploadPlatformDependentData(AppPlatform_linux *app_platform, int32_t size, void *data);

void AppPlatform_linux$vibrate(AppPlatform_linux *app_platform, int32_t milliseconds);

void AppPlatform_linux$destroy(AppPlatform_linux *app_platform);
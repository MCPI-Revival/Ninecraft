#include <ninecraft/AppPlatform_linux.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/version_ids.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <ninecraft/audio/sound_repository.h>
#include <ninecraft/audio/audio_engine.h>
#include <ninecraft/utils.h>
#include <stb_image.h>
#include <ninecraft/gfx/gles_compat.h>
#ifdef _WIN32
#include <direct.h>
#define popen _popen
#define pclose	_pclose
#else
#include <unistd.h>
#endif

int current_dialog_id = -1;

extern GLFWwindow *_window;
int status = -1;
ninecraft_options_t platform_options = {
    .options = NULL,
    .length = 0,
    .capasity = 0
};
bool is_keyboard_visible = false;

void *app_platform_vtable_0_1_0[] = {
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTextureOld),
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings),
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish
};

void *app_platform_vtable_0_1_0_touch[] = {
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTextureOld),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings),
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_1_1[] = {
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTextureOld),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings),
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_1_3[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTexture),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings),
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_3_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTexture),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings),
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_3_2[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTexture),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings),
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar)
};

void *app_platform_vtable_0_4_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTexture),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings),
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar)
};

void *app_platform_vtable_0_6_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTexture),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getOptionStrings),
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$getKeyFromKeyCode,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar),
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)AppPlatform_linux$showKeyboard2
};

void *app_platform_vtable_0_7_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTexture),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$openLoginWindow,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$getKeyFromKeyCode,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$supportsTouchscreen,
    (void *)AppPlatform_linux$supportsVibration,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar),
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)AppPlatform_linux$getSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$setSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$clearSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$showKeyboard2,
    (void *)AppPlatform_linux$webRequest,
    (void *)AppPlatform_linux$getWebRequestStatus,
    (void *)AppPlatform_linux$getWebRequestContent,
    (void *)AppPlatform_linux$abortWebRequest
};

void *app_platform_vtable_0_7_2[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTexture),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$openLoginWindow,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$getKeyFromKeyCode,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$supportsTouchscreen,
    (void *)AppPlatform_linux$supportsVibration,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar),
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)AppPlatform_linux$getSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$setSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$clearSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$initWithActivity,
    (void *)AppPlatform_linux$showKeyboard2,
    (void *)AppPlatform_linux$webRequest,
    (void *)AppPlatform_linux$getWebRequestStatus,
    (void *)AppPlatform_linux$getWebRequestContent,
    (void *)AppPlatform_linux$abortWebRequest
};

void *app_platform_vtable_0_7_3[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$loadTexture),
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$openLoginWindow,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$getKeyFromKeyCode,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$supportsTouchscreen,
    (void *)AppPlatform_linux$supportsVibration,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar),
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getLoginInformation),
    (void *)AppPlatform_linux$setLoginInformation,
    (void *)AppPlatform_linux$clearSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$statsTrackData,
    (void *)AppPlatform_linux$updateStatsUserData,
    (void *)AppPlatform_linux$initWithActivity,
    (void *)AppPlatform_linux$showKeyboard2,
    (void *)AppPlatform_linux$webRequest,
    (void *)AppPlatform_linux$getWebRequestStatus,
    (void *)AppPlatform_linux$getWebRequestContent,
    (void *)AppPlatform_linux$abortWebRequest
};

void *app_platform_vtable_0_8_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getImagePath),
    (void *)AppPlatform_linux$loadPNG,
    (void *)AppPlatform_linux$loadTGA,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$openLoginWindow,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$getKeyFromKeyCode,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$supportsTouchscreen,
    (void *)AppPlatform_linux$hasIDEProfiler,
    (void *)AppPlatform_linux$supportsVibration,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar),
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$updateTextBoxText,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getLoginInformation),
    (void *)AppPlatform_linux$setLoginInformation,
    (void *)AppPlatform_linux$clearSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$statsTrackData,
    (void *)AppPlatform_linux$updateStatsUserData,
    (void *)AppPlatform_linux$initWithActivity,
    (void *)AppPlatform_linux$webRequest,
    (void *)AppPlatform_linux$getWebRequestStatus,
    (void *)AppPlatform_linux$getWebRequestContent,
    (void *)AppPlatform_linux$abortWebRequest
};

void *app_platform_vtable_0_9_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getImagePath),
    (void *)AppPlatform_linux$loadPNG_0_9_0,
    (void *)AppPlatform_linux$loadTGA_0_9_0,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile_0_9_0),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$openLoginWindow,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$getKeyFromKeyCode,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$supportsTouchscreen,
    (void *)AppPlatform_linux$hasIDEProfiler,
    (void *)AppPlatform_linux$supportsVibration,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar),
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$updateTextBoxText,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getLoginInformation),
    (void *)AppPlatform_linux$setLoginInformation,
    (void *)AppPlatform_linux$clearSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$statsTrackData,
    (void *)AppPlatform_linux$updateStatsUserData,
    (void *)AppPlatform_linux$getAvailableMemory,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getBroadcastAddresses),
    (void *)AppPlatform_linux$initWithActivity,
    (void *)AppPlatform_linux$shareOpenGLContext,
    (void *)AppPlatform_linux$webRequest,
    (void *)AppPlatform_linux$getWebRequestStatus,
    (void *)AppPlatform_linux$getWebRequestContent,
    (void *)AppPlatform_linux$abortWebRequest,
    (void *)AppPlatform_linux$getTotalMemory
};

void *app_platform_vtable_0_10_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getImagePath),
    (void *)AppPlatform_linux$loadPNG_0_9_0,
    (void *)AppPlatform_linux$loadTGA_0_9_0,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getUserInput),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString),
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$saveImage,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile_0_9_0),
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$openLoginWindow,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$getKeyFromKeyCode,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$swapBuffers,
    (void *)AppPlatform_linux$supportsTouchscreen,
    (void *)AppPlatform_linux$hasIDEProfiler,
    (void *)AppPlatform_linux$supportsVibration,
    (void *)AppPlatform_linux$vibrate,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar),
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$updateTextBoxText,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getLoginInformation),
    (void *)AppPlatform_linux$setLoginInformation,
    (void *)AppPlatform_linux$clearSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$statsTrackData,
    (void *)AppPlatform_linux$captureScreen,
    (void *)AppPlatform_linux$getAvailableMemory,
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getBroadcastAddresses),
    (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getModelName),
    (void *)AppPlatform_linux$initWithActivity,
    (void *)AppPlatform_linux$webRequest,
    (void *)AppPlatform_linux$getWebRequestStatus,
    (void *)AppPlatform_linux$getWebRequestContent,
    (void *)AppPlatform_linux$abortWebRequest,
    (void *)AppPlatform_linux$updateStatsUserData,
};

void AppPlatform_linux$saveImage(AppPlatform_linux *app_platform, android_string_t *resource_path, android_string_t *pixels, int width, int height) {
    //puts("debug: AppPlatform_linux::saveImage");
}

void AppPlatform_linux$swapBuffers(AppPlatform_linux *app_platform) {
    ////puts("debug: AppPlatform_linux::swapBuffers");
}

SYSV_WRAPPER(AppPlatform_linux$getModelName, 2)
void AppPlatform_linux$getModelName(android_string_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getModelName");
    android_string_cstr(ret, "Linux");
}

void AppPlatform_linux$captureScreen(AppPlatform_linux *app_platform, int width, int height, bool do_capture) {
    //puts("debug: AppPlatform_linux::captureScreen");
}

int AppPlatform_linux$shareOpenGLContext(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::shareOpenGLContext");
    return 1;
}

SYSV_WRAPPER(AppPlatform_linux$getBroadcastAddresses, 2)
void AppPlatform_linux$getBroadcastAddresses(android_vector_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getBroadcastAddresses");
    android_vector_t out;
    out._M_start = 0;
    out._M_finish = 0;
    out._M_end_of_storage = 0;
    android_string_t str;
    android_string_cstr(&str, "0.0.0.0:19132");
    android_vector_push_back(&out, &str, android_string_tsize());
    *ret = out;
}

uint64_t AppPlatform_linux$getAvailableMemory(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getAvailableMemory");
    return 120586240 * 5;
}

uint64_t AppPlatform_linux$getTotalMemory(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getTotalMemory");
    return 1024 * 1024 * 1024;
}

void AppPlatform_linux$updateTextBoxText(AppPlatform_linux *app_platform, android_string_t *text) {
    //puts("debug: AppPlatform_linux::updateTextBoxText");
}

bool AppPlatform_linux$hasIDEProfiler(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::hasIDEProfiler");
    return false;
}

void AppPlatform_linux$loadTGA(AppPlatform_linux *app_platform, image_data_t *image, android_string_t *resource_path, bool alpha) {
    //puts("debug: AppPlatform_linux::loadTGA");
    int channels;
    image->pixels = stbi_load(android_string_to_str(resource_path), &image->width, &image->height, &channels, 0);
}

void AppPlatform_linux$loadTGA_0_9_0(AppPlatform_linux *app_platform, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha) {
    //puts("debug: AppPlatform_linux::loadTGA");
    int channels;
    stbi_uc *pixels = stbi_load(android_string_to_str(resource_path), &image->width, &image->height, &channels, 0);
    android_string_cstrl((android_string_t *)&image->pixels, (char *)pixels, 4 * image->width * image->height);
    stbi_image_free(pixels);
}

SYSV_WRAPPER(AppPlatform_linux$getImagePath, 4)
void AppPlatform_linux$getImagePath(android_string_t *ret, AppPlatform_linux *app_platform, android_string_t *resource_path, bool is_full) {
    //puts("debug: AppPlatform_linux::getImagePath");
    char *resource_path_c = android_string_to_str(resource_path);
    if (is_full) {
        char *str = (char *)malloc(1024);
        str[0] = '\0';
        getcwd(str, 1024);
        strcat(str, "/assets/images/");
        strcat(str, resource_path_c);
        android_string_cstr(ret, str);
        free(str);
    } else {
        android_string_cstr(ret, resource_path_c);
    }
}

void AppPlatform_linux$loadPNG(AppPlatform_linux *app_platform, image_data_t *image, android_string_t *resource_path, bool alpha) {
    //puts("debug: AppPlatform_linux::loadPNG");
    image->pixels = stbi_load(android_string_to_str(resource_path), &image->width, &image->height, NULL, STBI_rgb_alpha);
}

void AppPlatform_linux$loadPNG_0_9_0(AppPlatform_linux *app_platform, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha) {
    //puts("debug: AppPlatform_linux::loadPNG");

    stbi_uc *pixels = stbi_load(android_string_to_str(resource_path), &image->width, &image->height, NULL, STBI_rgb_alpha);
    android_string_cstrl((android_string_t *)&image->pixels, (char *)pixels, 4 * image->width * image->height);
    stbi_image_free(pixels);
}

SYSV_WRAPPER(AppPlatform_linux$getLoginInformation, 2)
void AppPlatform_linux$getLoginInformation(login_information_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getLoginInformation");
    if (android_string_tsize() == sizeof(android_string_stlp_t)) {
        android_string_cstr((android_string_t *)&ret->stlp.unknown0, "");
        android_string_cstr((android_string_t *)&ret->stlp.unknown1, "");
        android_string_cstr((android_string_t *)&ret->stlp.unknown2, "");
        android_string_cstr((android_string_t *)&ret->stlp.unknown3, "");
    } else {
        android_string_cstr((android_string_t *)&ret->gnu.unknown0, "");
        android_string_cstr((android_string_t *)&ret->gnu.unknown1, "");
        android_string_cstr((android_string_t *)&ret->gnu.unknown2, "");
        android_string_cstr((android_string_t *)&ret->gnu.unknown3, "");
    }
}

void AppPlatform_linux$setLoginInformation(AppPlatform_linux *app_platform, login_information_t *info) {
    //puts("debug: AppPlatform_linux::setLoginInformation");
}

void AppPlatform_linux$statsTrackData(AppPlatform_linux *app_platform, android_string_t *unknown0, android_string_t *unknown1) {
    //puts("debug: AppPlatform_linux::statsTrackData");
}

void AppPlatform_linux$updateStatsUserData(AppPlatform_linux *app_platform, android_string_t *unknown0, android_string_t *unknown1) {
    //puts("debug: AppPlatform_linux::updateStatsUserData");
}

void AppPlatform_linux$initWithActivity(AppPlatform_linux *app_platform, void *activity) {
    //puts("debug: AppPlatform_linux::initWithActivity");
}

void AppPlatform_linux$openLoginWindow(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::openLoginWindow");
}

bool AppPlatform_linux$supportsTouchscreen(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::supportsTouchscreen");
    return false;
}

bool AppPlatform_linux$supportsVibration(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::supportsVibration");
    return false;
}

void AppPlatform_linux$getSessionIDAndRefreshToken(AppPlatform_linux *app_platform, android_string_t *session_id, android_string_t *refresh_token) {
    //puts("debug: AppPlatform_linux::getSessionIDAndRefreshToken");
    android_string_equ(session_id, "");
    android_string_equ(refresh_token, "");
}

void AppPlatform_linux$setSessionIDAndRefreshToken(AppPlatform_linux *app_platform, android_string_t *session_id, android_string_t *refresh_token) {
    //puts("debug: AppPlatform_linux::setSessionIDAndRefreshToken");
}

void AppPlatform_linux$clearSessionIDAndRefreshToken(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::clearSessionIDAndRefreshToken");
}

void AppPlatform_linux$webRequest(AppPlatform_linux *app_platform, int unknown0, long long unknown1, android_string_t *unknown2, android_string_t *unknown3, android_string_t *unknown4) {
    //puts("debug: AppPlatform_linux::webRequest");
}

int AppPlatform_linux$getWebRequestStatus(AppPlatform_linux *app_platform, int unknown0) {
    //puts("debug: AppPlatform_linux::getWebRequestStatus");
    return 0;
}

void AppPlatform_linux$getWebRequestContent(AppPlatform_linux *app_platform, int unknown0) {
    //puts("debug: AppPlatform_linux::getWebRequestContent");
}

void AppPlatform_linux$abortWebRequest(AppPlatform_linux *app_platform, int unknown0) {
    //puts("debug: AppPlatform_linux::abortWebRequest");
}

void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle, int version_id) {
    if (version_id == version_id_0_8_1) {
        app_platform->vtable = app_platform_vtable_0_8_0;
    } else if (version_id == version_id_0_8_0) {
        app_platform->vtable = app_platform_vtable_0_8_0;
    } else if (version_id == version_id_0_7_6) {
        app_platform->vtable = app_platform_vtable_0_7_3;
    } else if (version_id == version_id_0_7_5) {
        app_platform->vtable = app_platform_vtable_0_7_3;
    } else if (version_id == version_id_0_7_4) {
        app_platform->vtable = app_platform_vtable_0_7_3;
    } else if (version_id == version_id_0_7_3) {
        app_platform->vtable = app_platform_vtable_0_7_3;
    } else if (version_id == version_id_0_7_2) {
        app_platform->vtable = app_platform_vtable_0_7_2;
    } else if (version_id == version_id_0_7_1) {
        app_platform->vtable = app_platform_vtable_0_7_0;
    } else if (version_id == version_id_0_7_0) {
        app_platform->vtable = app_platform_vtable_0_7_0;
    } else if (version_id == version_id_0_6_1) {
        app_platform->vtable = app_platform_vtable_0_6_0;
    } else if (version_id == version_id_0_6_0) {
        app_platform->vtable = app_platform_vtable_0_6_0;
    } else if (version_id == version_id_0_5_0) {
        app_platform->vtable = app_platform_vtable_0_4_0;
    } else if (version_id == version_id_0_5_0_j) {
        app_platform->vtable = app_platform_vtable_0_4_0;
    } else if (version_id == version_id_0_4_0) {
        app_platform->vtable = app_platform_vtable_0_4_0;
    } else if (version_id == version_id_0_4_0_j) {
        app_platform->vtable = app_platform_vtable_0_4_0;
    } else if (version_id == version_id_0_3_3) {
        app_platform->vtable = app_platform_vtable_0_3_2;
    } else if (version_id == version_id_0_3_3_j) {
        app_platform->vtable = app_platform_vtable_0_3_2;
    } else if (version_id == version_id_0_3_2) {
        app_platform->vtable = app_platform_vtable_0_3_2;
    } else if (version_id == version_id_0_3_2_j) {
        app_platform->vtable = app_platform_vtable_0_3_2;
    } else if (version_id == version_id_0_3_0) {
        app_platform->vtable = app_platform_vtable_0_3_0;
    } else if (version_id == version_id_0_3_0_j) {
        app_platform->vtable = app_platform_vtable_0_3_0;
    } else if (version_id == version_id_0_2_2) {
        app_platform->vtable = app_platform_vtable_0_1_3;
    } else if (version_id == version_id_0_2_1) {
        app_platform->vtable = app_platform_vtable_0_1_3;
    } else if (version_id == version_id_0_2_1_j) {
        app_platform->vtable = app_platform_vtable_0_1_3;
    } else if (version_id == version_id_0_2_0) {
        app_platform->vtable = app_platform_vtable_0_1_3;
    } else if (version_id == version_id_0_2_0_j) {
        app_platform->vtable = app_platform_vtable_0_1_3;
    } else if (version_id == version_id_0_1_3) {
        app_platform->vtable = app_platform_vtable_0_1_3;
    } else if (version_id == version_id_0_1_3_j) {
        app_platform->vtable = app_platform_vtable_0_1_3;
    } else if (version_id == version_id_0_1_2) {
        app_platform->vtable = app_platform_vtable_0_1_1;
    } else if (version_id == version_id_0_1_2_j) {
        app_platform->vtable = app_platform_vtable_0_1_1;
    } else if (version_id == version_id_0_1_1) {
        app_platform->vtable = app_platform_vtable_0_1_1;
    } else if (version_id == version_id_0_1_1_j) {
        app_platform->vtable = app_platform_vtable_0_1_1;
    } else if (version_id == version_id_0_1_0_touch) {
        app_platform->vtable = app_platform_vtable_0_1_0_touch;
    } else if (version_id == version_id_0_1_0) {
        app_platform->vtable = app_platform_vtable_0_1_0;
    }
}

void AppPlatform_linux$_tick(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::_tick");
}

void AppPlatform_linux$buyGame(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::buyGame");
}
 
int AppPlatform_linux$checkLicense(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::checkLicense");
    return 1;
}

void AppPlatform_linux$createUserInput(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::createUserInput");
    status = 1;
    //app_platform->user_input_text = NULL;
}

void AppPlatform_linux$finish(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::finish");
}

SYSV_WRAPPER(AppPlatform_linux$getDateString, 3)
void AppPlatform_linux$getDateString(android_string_t *ret, AppPlatform_linux *app_platform, unsigned int seconds) {
    //puts("debug: AppPlatform_linux::getDateString");
    char date[200];
    date_str(date, seconds);
    android_string_cstr(ret, date);
}

int AppPlatform_linux$getKeyFromKeyCode(AppPlatform_linux *app_platform, unsigned int key_code, unsigned int meta_state, unsigned int device_id) {
    //puts("debug: AppPlatform_linux::getKeyFromKeyCode");
    return 0;
}

SYSV_WRAPPER(AppPlatform_linux$getOptionStrings, 2)
void AppPlatform_linux$getOptionStrings(android_vector_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getOptionsStrings");
    android_vector_t out;
    out._M_start = 0;
    out._M_finish = 0;
    out._M_end_of_storage = 0;
    for (int i = 0; i < platform_options.length; ++i) {
        ninecraft_option_t o = platform_options.options[i];
        android_string_t name;
        android_string_cstr(&name, o.name);
        android_vector_push_back(&out, &name, android_string_tsize());
        android_string_t value;
        android_string_cstr(&value, o.value);
        android_vector_push_back(&out, &value, android_string_tsize());
    }
    *ret = out;
}

FLOAT_ABI_FIX float AppPlatform_linux$getPixelsPerMillimeter(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getPixelsPerMillimeter");
    int cw, ch;
    glfwGetWindowSize(_window, &cw, &ch);
    return (((float)cw + (float)ch) * 0.5f ) / 25.4f;
}

SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar, 3)
void AppPlatform_linux$getPlatformStringVar(android_string_t *ret, AppPlatform_linux *app_platform, int zero) {
    //puts("debug: AppPlatform_linux::getPlatformStringVar");
    printf("%p\n", app_platform);
    android_string_cstr(ret, "Linux");
}

int AppPlatform_linux$getScreenHeight(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getScreenHeight");
    int cw;
    int ch;
    glfwGetWindowSize(_window, &cw, &ch);
    return ch;
}

int AppPlatform_linux$getScreenWidth(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getScreenWidth");
    int cw;
    int ch;
    glfwGetWindowSize(_window, &cw, &ch);
    return cw;
}

SYSV_WRAPPER(AppPlatform_linux$getUserInput, 2)
void AppPlatform_linux$getUserInput(android_vector_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getUserInput");
    FILE *fp;
    android_vector_t out;
    out._M_start = 0;
    out._M_finish = 0;
    out._M_end_of_storage = 0;
    if (current_dialog_id == did_new_world) {
        android_string_t name;
        android_string_t seed;
        android_string_t gamemode;
        fp = popen("zenity --entry --title=\"Create New World\" --text=\"Enter World Name:\"", "r");
        if (fp == NULL) {
            android_string_cstr(&name, "random world");
        } else {
            char input_value[100];
            for (int i = 0; i < 100; ++i) {
                char c = fgetc(fp);
                if (c == '\n' || c == '\0' || c == EOF) {
                    input_value[i] = '\0';
                    break;
                }
                input_value[i] = c;
            }
            input_value[99] = '\0';
            printf("%s\n", input_value);
            android_string_cstr(&name, input_value);
            pclose(fp);
        }

        fp = popen("zenity --entry --title=\"Create New World\" --text=\"Enter World Seed:\"", "r");
        if (fp == NULL) {
            android_string_cstr(&seed, "1234567890");
        } else {
            char input_value[100];
            for (int i = 0; i < 100; ++i) {
                char c = fgetc(fp);
                if (c == '\n' || c == '\0' || c == EOF) {
                    input_value[i] = '\0';
                    break;
                }
                input_value[i] = c;
            }
            input_value[99] = '\0';
            printf("%s\n", input_value);
            android_string_cstr(&seed, input_value);
            pclose(fp);
        }

        fp = popen("zenity --list --title=\"Create New World\" --text=\"Enter World Gamemode:\" --column=\"gamemode\" \"creative\" \"survival\"", "r");
        if (fp == NULL) {
            android_string_cstr(&gamemode, "creative");
        } else {
            char input_value[100];
            for (int i = 0; i < 100; ++i) {
                char c = fgetc(fp);
                if (c == '\n' || c == '\0' || c == EOF) {
                    input_value[i] = '\0';
                    break;
                }
                input_value[i] = c;
            }
            input_value[99] = '\0';
            printf("%s\n", input_value);
            android_string_cstr(&gamemode, input_value);
            pclose(fp);
        }

        status = 1;

        android_vector_push_back(&out, &name, android_string_tsize());
        android_vector_push_back(&out, &seed, android_string_tsize());
        android_vector_push_back(&out, &gamemode, android_string_tsize());
    } else if (current_dialog_id == did_chat) {
        android_string_t message;

        fp = popen("zenity --entry --title=\"Chat\" --text=\"Enter message:\"", "r");
        if (fp) {
            char input_value[100];
            for (int i = 0; i < 100; ++i) {
                char c = fgetc(fp);
                if (c == '\n' || c == '\0' || c == EOF) {
                    input_value[i] = '\0';
                    break;
                }
                input_value[i] = c;
            }
            input_value[99] = '\0';

            android_string_cstr(&message, input_value);
            pclose(fp);

            android_vector_push_back(&out, &message, android_string_tsize());
            status = 1;
        } else {
            status = 0;
        }
    } else if (current_dialog_id == did_rename_world) {
        android_string_t name;

        fp = popen("zenity --entry --title=\"Rename world\" --text=\"Enter a new name:\"", "r");
        if (fp) {
            char input_value[100];
            for (int i = 0; i < 100; ++i) {
                char c = fgetc(fp);
                if (c == '\n' || c == '\0' || c == EOF) {
                    input_value[i] = '\0';
                    break;
                }
                input_value[i] = c;
            }
            input_value[99] = '\0';

            android_string_cstr(&name, input_value);
            pclose(fp);

            android_vector_push_back(&out, &name, android_string_tsize());
            status = 1;
        } else {
            status = 0;
        }
    } else {
        status = 0;
    }
    current_dialog_id = -1;
    *ret = out;
}

int AppPlatform_linux$getUserInputStatus(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getUserInputStatus");
    return status;
}

bool AppPlatform_linux$hasBuyButtonWhenInvalidLicense(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::hasBuyButtonWhenInvalidLicense");
    return true;
}

void AppPlatform_linux$hideKeyboard(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::hideKeyboard");
    is_keyboard_visible = false;
}

bool AppPlatform_linux$isKeyboardVisible(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::isKeyboardVisible");
    return false;
}

bool AppPlatform_linux$isNetworkEnabled(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::isNetworkEnabled");
    return true;
}

bool AppPlatform_linux$isPowerVR(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::isPowerVR");
    return false;
}

bool AppPlatform_linux$isTouchscreen(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::isTouchscreen");
    for (size_t i = 0; i < platform_options.length; ++i) {
        if (strcmp(platform_options.options[i].name, "ctrl_usetouchscreen") == 0) {
            if (strcmp(platform_options.options[i].value, "true") == 0) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

SYSV_WRAPPER(AppPlatform_linux$loadTexture, 4)
void AppPlatform_linux$loadTexture(texture_data_t *ret, AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha) {
    //puts("debug: AppPlatform_linux::loadTexture");
    char *resource = android_string_to_str(path_str);
    char *path = (char *)malloc(1024);
    path[0] = '\0';
    getcwd(path, 1024);
    strcat(path, "/overrides/assets/");
    strcat(path, resource);
    if (access(path, 0) != 0) {
        getcwd(path, 1024);
        strcat(path, "/internal_overrides/assets/");
        strcat(path, resource);
        if (access(path, 0) != 0) {
            getcwd(path, 1024);
            strcat(path, "/assets/");
            strcat(path, resource);
        }
    }
    printf("%p %s\n", app_platform, path);
    texture_data_t texture_data = {
        .unknown = 0,
        .alpha = 1,
        .keep_buffer_data = 0,
        .texture_type = texture_type_ub,
        .unknown2 = 0xffffffff
    };
    texture_data.pixels = stbi_load(path, &texture_data.width, &texture_data.height, NULL, STBI_rgb_alpha);
    free(path);
    *ret = texture_data;
}

SYSV_WRAPPER(AppPlatform_linux$loadTextureOld, 4)
void AppPlatform_linux$loadTextureOld(texture_data_old_t *ret, AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha) {
    //puts("debug: AppPlatform_linux::loadTexture");
    char *resource = android_string_to_str(path_str);
    char *path = (char *)malloc(1024);
    path[0] = '\0';
    getcwd(path, 1024);
    strcat(path, "/overrides/assets/");
    strcat(path, resource);
    if (access(path, 0) != 0) {
        getcwd(path, 1024);
        strcat(path, "/internal_overrides/assets/");
        strcat(path, resource);
        if (access(path, 0) != 0) {
            getcwd(path, 1024);
            strcat(path, "/assets/");
            strcat(path, resource);
        }
    }
    texture_data_old_t texture_data = {
        .alpha = 1,
        .keep_buffer_data = 0
    };
    texture_data.pixels = stbi_load(path, &texture_data.width, &texture_data.height, NULL, STBI_rgb_alpha);
    free(path);
    *ret = texture_data;
}

FLOAT_ABI_FIX void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, android_string_t *sound_name, float volume, float pitch) {
    //puts("debug: AppPlatform_linux::playSound");
    ninecraft_sound_resource_t *res = ninecraft_get_sound_buffer(android_string_to_str(sound_name));
    audio_engine_play(res->buffer, res->buffer_size, res->num_channels, res->bits_per_sample, res->freq, volume, pitch);
}

SYSV_WRAPPER(AppPlatform_linux$readAssetFile, 3)
void AppPlatform_linux$readAssetFile(asset_file *ret, AppPlatform_linux *app_platform, android_string_t *path_str) {
    //puts("debug: AppPlatform_linux::readAssetFile");
    android_string_t str;
    char *resource = android_string_to_str(path_str);
    size_t resourcelen = strlen(resource);
    char *path = (char *)malloc(1024);
    path[0] = '\0';
    getcwd(path, 1024);
    strcat(path, "/overrides/assets/");
    strcat(path, resource);
    if (access(path, 0) != 0) {
        getcwd(path, 1024);
        strcat(path, "/internal_overrides/assets/");
        strcat(path, resource);
        if (access(path, 0) != 0) {
            getcwd(path, 1024);
            strcat(path, "/assets/");
            strcat(path, resource);
        }
    }
    asset_file asset;

    FILE *file = fopen(path, "rb");
    if (!file) {
        free(path);
        printf("Error[%d] failed to read %s\n", errno, path);
        asset.data = NULL;
        asset.size = -1;
        *ret = asset;
        return;
    }
    printf("Read asset: %s\n", path);
    free(path);
    fseek(file, 0, SEEK_END);
    asset.size = ftell(file);
    asset.data = (char *) malloc(asset.size);
    fseek(file, 0, SEEK_SET);
    fread(asset.data, 1, asset.size, file);

    *ret = asset;
}

SYSV_WRAPPER(AppPlatform_linux$readAssetFile_0_9_0, 3)
void AppPlatform_linux$readAssetFile_0_9_0(android_string_t *ret, AppPlatform_linux *app_platform, android_string_t *path_str) {
    asset_file asset;
    AppPlatform_linux$readAssetFile(&asset, app_platform, path_str);
    if (asset.data == NULL && asset.size == -1) {
        android_string_cstr(ret, "");
    } else {
        android_string_cstrl(ret, asset.data, asset.size);
    }
}

void AppPlatform_linux$saveScreenshot(AppPlatform_linux *app_platform, android_string_t *path, int width, int height) {
    //puts("debug: AppPlatform_linux::saveScreenshot");
}

void AppPlatform_linux$showDialog(AppPlatform_linux *app_platform, int dialog_id) {
    //puts("debug: AppPlatform_linux::showDialog");
    current_dialog_id = dialog_id;
    status = -1;
}

void AppPlatform_linux$showKeyboard(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::showKeyboard");
    is_keyboard_visible = true;
}

void AppPlatform_linux$showKeyboard2(AppPlatform_linux *app_platform, bool show) {
    //puts("debug: AppPlatform_linux::showKeyboard2");
    is_keyboard_visible = true;
}

void AppPlatform_linux$uploadPlatformDependentData(AppPlatform_linux *app_platform, int size, void *data) {
    //puts("debug: AppPlatform_linux::uploadPlatformDependentData");
}

void AppPlatform_linux$vibrate(AppPlatform_linux *app_platform, int milliseconds) {
    //puts("debug: AppPlatform_linux::vibrate");
}

void AppPlatform_linux$destroy(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::destroy");
}

android_string_t *AppPlatform_linux$getSystemRegion(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getSystemRegion");
    android_string_t *str = (android_string_t *)malloc(sizeof(android_string_t));
    android_string_cstr(str, "US");
    return str;
}

SYSV_WRAPPER(AppPlatform_linux$getGraphicsVendor, 2)
void AppPlatform_linux$getGraphicsVendor(android_string_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getGraphicsVendor");
    android_string_cstr(ret, (char *)glGetString(GL_VENDOR));
}

SYSV_WRAPPER(AppPlatform_linux$getGraphicsRenderer, 2)
void AppPlatform_linux$getGraphicsRenderer(android_string_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getGraphicsRenderer");
    android_string_cstr(ret, (char *)glGetString(GL_RENDERER));
}

SYSV_WRAPPER(AppPlatform_linux$getGraphicsVersion, 2)
void AppPlatform_linux$getGraphicsVersion(android_string_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getGraphicsVersion");
    android_string_cstr(ret, (char *)glGetString(GL_VERSION));
}

SYSV_WRAPPER(AppPlatform_linux$getGraphicsExtensions, 2)
void AppPlatform_linux$getGraphicsExtensions(android_string_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getGraphicsExtensions");
    android_string_cstr(ret, (char *)glGetString(GL_EXTENSIONS));
}

android_string_t *AppPlatform_linux$getExternalStoragePath(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getExternalStoragePath");
    android_string_t *str = (android_string_t *)malloc(sizeof(android_string_t));
    char *storage_path = (char *)malloc(1024);
    storage_path[0] = '\0';
    getcwd(storage_path, 1024);
    strcat(storage_path, "/storage/");
    android_string_cstr(str, storage_path);
    free(storage_path);
    return str;
}

android_string_t *AppPlatform_linux$getInternalStoragePath(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getInternalStoragePath");
    android_string_t *str = (android_string_t *)malloc(sizeof(android_string_t));
    char *storage_path = (char *)malloc(1024);
    storage_path[0] = '\0';
    getcwd(storage_path, 1024);
    strcat(storage_path, "/storage/");
    android_string_cstr(str, storage_path);
    free(storage_path);
    return str;
}

SYSV_WRAPPER(AppPlatform_linux$getApplicationId, 2)
void AppPlatform_linux$getApplicationId(android_string_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getApplicationId");
    android_string_cstr(ret, "com.mojang.minecraftpe");
}

SYSV_WRAPPER(AppPlatform_linux$getDeviceId, 2)
void AppPlatform_linux$getDeviceId(android_string_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::getDeviceId");
    android_string_cstr(ret, "Ninecraft");
}

SYSV_WRAPPER(AppPlatform_linux$createUUID, 2)
void AppPlatform_linux$createUUID(android_string_t *ret, AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::createUUID");
    android_string_cstr(ret, "bef07706-f3c5-489d-b251-fb6a297e9b1c");
}

bool AppPlatform_linux$isFirstSnoopLaunch(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::isFirstSnoopLaunch");
    return false;
}

bool AppPlatform_linux$hasHardwareInformationChanged(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::hasHardwareInformationChanged");
    return false;
}

bool AppPlatform_linux$isTablet(AppPlatform_linux *app_platform) {
    //puts("debug: AppPlatform_linux::isTablet");
    return false;
}

void AppPlatform_linux$pickImage(AppPlatform_linux *__this, image_picking_callback_0_11_0_t *callback) {
    android_string_t path;
    FILE *fp = popen("zenity --file-selection", "r");
    if (fp) {
        char input_value[256];
        for (int i = 0; i < 100; ++i) {
            char c = fgetc(fp);
            if (c == '\n' || c == '\0' || c == EOF) {
                input_value[i] = '\0';
                break;
            }
            input_value[i] = c;
        }
        input_value[255] = '\0';
        android_string_cstr(&path, input_value);
        pclose(fp);
        callback->vtable->onImagePickingSuccess(callback, &path);
    } else {
        callback->vtable->onImagePickingCanceled(callback);
    }
}
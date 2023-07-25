#include <ninecraft/AppPlatform_linux.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/version_ids.h>
#include <unistd.h>
#include <GLFW/glfw3.h>
#include <ninecraft/audio/sound_repository.h>
#include <ninecraft/audio/audio_engine.h>
#include <ninecraft/utils.h>
#include <stb_image.h>

extern GLFWwindow *_window;

void *app_platform_vtable_0_1_0[] = {
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTextureOld,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish
};

void *app_platform_vtable_0_1_0_touch[] = {
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTextureOld,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_1_1[] = {
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTextureOld,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_1_3_stlp[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_1_3_gnu[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringGNU,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_3_0_stlp[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_3_0_gnu[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringGNU,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate
};

void *app_platform_vtable_0_3_2_stlp[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate,
    (void *)AppPlatform_linux$getPlatformStringVarSTLP
};

void *app_platform_vtable_0_3_2_gnu[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringGNU,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate,
    (void *)AppPlatform_linux$getPlatformStringVarGNU
};

void *app_platform_vtable_0_4_0_stlp[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate,
    (void *)AppPlatform_linux$getPlatformStringVarSTLP
};

void *app_platform_vtable_0_4_0_gnu[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringGNU,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate,
    (void *)AppPlatform_linux$getPlatformStringVarGNU
};

void *app_platform_vtable_0_6_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
    (void *)AppPlatform_linux$_tick,
    (void *)AppPlatform_linux$getScreenWidth,
    (void *)AppPlatform_linux$getScreenHeight,
    (void *)AppPlatform_linux$getPixelsPerMillimeter,
    (void *)AppPlatform_linux$isNetworkEnabled,
    (void *)AppPlatform_linux$getOptionStrings,
    (void *)AppPlatform_linux$isPowerVR,
    (void *)AppPlatform_linux$getKeyFromKeyCode,
    (void *)AppPlatform_linux$buyGame,
    (void *)AppPlatform_linux$finish,
    (void *)AppPlatform_linux$isTouchscreen,
    (void *)AppPlatform_linux$vibrate,
    (void *)AppPlatform_linux$getPlatformStringVarSTLP,
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)AppPlatform_linux$showKeyboard2
};

void *app_platform_vtable_0_7_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
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
    (void *)AppPlatform_linux$getPlatformStringVarSTLP,
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
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringSTLP,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
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
    (void *)AppPlatform_linux$getPlatformStringVarSTLP,
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
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringGNU,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
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
    (void *)AppPlatform_linux$getPlatformStringVarGNU,
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)AppPlatform_linux$getLoginInformation,
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
    (void *)AppPlatform_linux$getImagePath,
    (void *)AppPlatform_linux$loadPNG,
    (void *)AppPlatform_linux$loadTGA,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringGNU,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile,
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
    (void *)AppPlatform_linux$getPlatformStringVarGNU,
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$updateTextBoxText,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)AppPlatform_linux$getLoginInformation,
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
    (void *)AppPlatform_linux$getImagePath,
    (void *)AppPlatform_linux$loadPNG_0_9_0,
    (void *)AppPlatform_linux$loadTGA_0_9_0,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateStringGNU,
    (void *)AppPlatform_linux$checkLicense,
    (void *)AppPlatform_linux$hasBuyButtonWhenInvalidLicense,
    (void *)AppPlatform_linux$uploadPlatformDependentData,
    (void *)AppPlatform_linux$readAssetFile_0_9_0,
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
    (void *)AppPlatform_linux$getPlatformStringVarGNU,
    (void *)AppPlatform_linux$showKeyboard,
    (void *)AppPlatform_linux$hideKeyboard,
    (void *)AppPlatform_linux$updateTextBoxText,
    (void *)AppPlatform_linux$isKeyboardVisible,
    (void *)AppPlatform_linux$getLoginInformation,
    (void *)AppPlatform_linux$setLoginInformation,
    (void *)AppPlatform_linux$clearSessionIDAndRefreshToken,
    (void *)AppPlatform_linux$statsTrackData,
    (void *)AppPlatform_linux$updateStatsUserData,
    (void *)AppPlatform_linux$getTotalMemory,
    (void *)AppPlatform_linux$getBroadcastAddresses,
    (void *)AppPlatform_linux$initWithActivity,
    (void *)AppPlatform_linux$shareOpenGLContext,
    (void *)AppPlatform_linux$webRequest,
    (void *)AppPlatform_linux$getWebRequestStatus,
    (void *)AppPlatform_linux$getWebRequestContent,
    (void *)AppPlatform_linux$abortWebRequest
};

int AppPlatform_linux$shareOpenGLContext(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::shareOpenGLContext");
    return 1;
}

android_vector_t AppPlatform_linux$getBroadcastAddresses(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getBroadcastAddresses");
    android_vector_t out;
    out._M_start = 0;
    out._M_finish = 0;
    out._M_end_of_storage = 0;
    android_string_gnu_t str;
    android_string_cstr(&str, "0.0.0.0:19132");
    android_vector_push_back(&out, &str, sizeof(str));
    return out;
}

size_t AppPlatform_linux$getTotalMemory(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getTotalMemory");
    return 536870912;
}

void AppPlatform_linux$updateTextBoxText(AppPlatform_linux *app_platform, android_string_t *text) {
    puts("debug: AppPlatform_linux::updateTextBoxText");
}

bool AppPlatform_linux$hasIDEProfiler(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::hasIDEProfiler");
    return false;
}

void AppPlatform_linux$loadTGA(AppPlatform_linux *app_platform, image_data_t *image, android_string_t *resource_path, bool alpha) {
    puts("debug: AppPlatform_linux::loadTGA");
    int channels;
    image->pixels = stbi_load(android_string_to_str(resource_path), &image->width, &image->height, &channels, 0);
}

void AppPlatform_linux$loadTGA_0_9_0(AppPlatform_linux *app_platform, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha) {
    puts("debug: AppPlatform_linux::loadTGA");
    int channels;
    stbi_uc *pixels = stbi_load(android_string_to_str(resource_path), &image->width, &image->height, &channels, 0);
    android_string_cstrl(&image->pixels, pixels, 4 * image->width * image->height);
    stbi_image_free(pixels);
}

NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$getImagePath, AppPlatform_linux *app_platform, android_string_t *resource_path, bool is_full) {
    puts("debug: AppPlatform_linux::getImagePath");
    if (is_full) {
        char str[MAXPATHLEN];
        getcwd(str, MAXPATHLEN);
        strcat(str, "/assets/images/");
        strcat(str, android_string_to_str(resource_path));
        android_string_t out;
        android_string_cstr(&out, str);
        NINECRAFT_CSR_RETURN(out.gnu);
    } else {
        NINECRAFT_CSR_RETURN(resource_path->gnu);
    }
}

void AppPlatform_linux$loadPNG(AppPlatform_linux *app_platform, image_data_t *image, android_string_t *resource_path, bool alpha) {
    puts("debug: AppPlatform_linux::loadPNG");
    image->pixels = stbi_load(android_string_to_str(resource_path), &image->width, &image->height, NULL, STBI_rgb_alpha);
}

void AppPlatform_linux$loadPNG_0_9_0(AppPlatform_linux *app_platform, image_data_0_9_0_t *image, android_string_t *resource_path, bool alpha) {
    puts("debug: AppPlatform_linux::loadPNG");

    stbi_uc *pixels = stbi_load(android_string_to_str(resource_path), &image->width, &image->height, NULL, STBI_rgb_alpha);
    android_string_cstrl(&image->pixels, pixels, 4 * image->width * image->height);
    stbi_image_free(pixels);
}

login_information_t AppPlatform_linux$getLoginInformation(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getLoginInformation");
    login_information_t info;
    android_string_cstr(&info.unknown0, "");
    android_string_cstr(&info.unknown1, "");
    android_string_cstr(&info.unknown2, "");
    android_string_cstr(&info.unknown3, "");
    return info;
}

void AppPlatform_linux$setLoginInformation(AppPlatform_linux *app_platform, login_information_t *info) {
    puts("debug: AppPlatform_linux::setLoginInformation");
}

void AppPlatform_linux$statsTrackData(AppPlatform_linux *app_platform, android_string_t *unknown0, android_string_t *unknown1) {
    puts("debug: AppPlatform_linux::statsTrackData");
}

void AppPlatform_linux$updateStatsUserData(AppPlatform_linux *app_platform, android_string_t *unknown0, android_string_t *unknown1) {
    puts("debug: AppPlatform_linux::updateStatsUserData");
}

void AppPlatform_linux$initWithActivity(AppPlatform_linux *app_platform, void *activity) {
    puts("debug: AppPlatform_linux::initWithActivity");
}

void AppPlatform_linux$openLoginWindow(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::openLoginWindow");
}

bool AppPlatform_linux$supportsTouchscreen(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::supportsTouchscreen");
    return false;
}

bool AppPlatform_linux$supportsVibration(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::supportsVibration");
    return false;
}

void AppPlatform_linux$getSessionIDAndRefreshToken(AppPlatform_linux *app_platform, android_string_t *session_id, android_string_t *refresh_token) {
    puts("debug: AppPlatform_linux::getSessionIDAndRefreshToken");
    android_string_equ(session_id, "");
    android_string_equ(refresh_token, "");
}

void AppPlatform_linux$setSessionIDAndRefreshToken(AppPlatform_linux *app_platform, android_string_t *session_id, android_string_t *refresh_token) {
    puts("debug: AppPlatform_linux::setSessionIDAndRefreshToken");
}

void AppPlatform_linux$clearSessionIDAndRefreshToken(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::clearSessionIDAndRefreshToken");
}

void AppPlatform_linux$webRequest(AppPlatform_linux *app_platform, int unknown0, long long unknown1, android_string_t *unknown2, android_string_t *unknown3, android_string_t *unknown4) {
    puts("debug: AppPlatform_linux::webRequest");
}

int AppPlatform_linux$getWebRequestStatus(AppPlatform_linux *app_platform, int unknown0) {
    puts("debug: AppPlatform_linux::getWebRequestStatus");
    return 0;
}

void AppPlatform_linux$getWebRequestContent(AppPlatform_linux *app_platform, int unknown0) {
    puts("debug: AppPlatform_linux::getWebRequestContent");
}

void AppPlatform_linux$abortWebRequest(AppPlatform_linux *app_platform, int unknown0) {
    puts("debug: AppPlatform_linux::abortWebRequest");
}

void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle, int version_id, ninecraft_options_t *options) {
    if (version_id == version_id_0_9_4) {
        **(void ****)internal_dlsym(handle, "_ZN11AppPlatform10_singletonE") = app_platform_vtable_0_9_0;
        app_platform->vtable = app_platform_vtable_0_9_0;
    } else if (version_id == version_id_0_9_3) {
        **(void ****)internal_dlsym(handle, "_ZN11AppPlatform10_singletonE") = app_platform_vtable_0_9_0;
        app_platform->vtable = app_platform_vtable_0_9_0;
    } else if (version_id == version_id_0_9_2) {
        **(void ****)internal_dlsym(handle, "_ZN11AppPlatform10_singletonE") = app_platform_vtable_0_9_0;
        app_platform->vtable = app_platform_vtable_0_9_0;
    } else if (version_id == version_id_0_9_1) {
        **(void ****)internal_dlsym(handle, "_ZN11AppPlatform10_singletonE") = app_platform_vtable_0_9_0;
        app_platform->vtable = app_platform_vtable_0_9_0;
    } else if (version_id == version_id_0_9_0) {
        **(void ****)internal_dlsym(handle, "_ZN11AppPlatform10_singletonE") = app_platform_vtable_0_9_0;
        app_platform->vtable = app_platform_vtable_0_9_0;
    } else if (version_id == version_id_0_8_1) {
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
        app_platform->vtable = app_platform_vtable_0_4_0_stlp;
    } else if (version_id == version_id_0_5_0_j) {
        app_platform->vtable = app_platform_vtable_0_4_0_gnu;
    } else if (version_id == version_id_0_4_0) {
        app_platform->vtable = app_platform_vtable_0_4_0_stlp;
    } else if (version_id == version_id_0_4_0_j) {
        app_platform->vtable = app_platform_vtable_0_4_0_gnu;
    } else if (version_id == version_id_0_3_3) {
        app_platform->vtable = app_platform_vtable_0_3_2_stlp;
    } else if (version_id == version_id_0_3_3_j) {
        app_platform->vtable = app_platform_vtable_0_3_2_gnu;
    } else if (version_id == version_id_0_3_2) {
        app_platform->vtable = app_platform_vtable_0_3_2_stlp;
    } else if (version_id == version_id_0_3_2_j) {
        app_platform->vtable = app_platform_vtable_0_3_2_gnu;
    } else if (version_id == version_id_0_3_0) {
        app_platform->vtable = app_platform_vtable_0_3_0_stlp;
    } else if (version_id == version_id_0_3_0_j) {
        app_platform->vtable = app_platform_vtable_0_3_0_gnu;
    } else if (version_id == version_id_0_2_2) {
        app_platform->vtable = app_platform_vtable_0_1_3_stlp;
    } else if (version_id == version_id_0_2_1) {
        app_platform->vtable = app_platform_vtable_0_1_3_gnu;
    } else if (version_id == version_id_0_2_1_j) {
        app_platform->vtable = app_platform_vtable_0_1_3_gnu;
    } else if (version_id == version_id_0_2_0) {
        app_platform->vtable = app_platform_vtable_0_1_3_gnu;
    } else if (version_id == version_id_0_2_0_j) {
        app_platform->vtable = app_platform_vtable_0_1_3_gnu;
    } else if (version_id == version_id_0_1_3) {
        app_platform->vtable = app_platform_vtable_0_1_3_stlp;
    } else if (version_id == version_id_0_1_3_j) {
        app_platform->vtable = app_platform_vtable_0_1_3_stlp;
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
    
    app_platform->handle = handle;
    app_platform->status = -1;
    app_platform->version_id = version_id;
    app_platform->options = options;
}

void AppPlatform_linux$_tick(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::_tick");
}

void AppPlatform_linux$buyGame(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::buyGame");
}
 
int AppPlatform_linux$checkLicense(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::checkLicense");
    return 1;
}

void AppPlatform_linux$createUserInput(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::createUserInput");
    app_platform->status = 1;
    //app_platform->user_input_text = NULL;
}

void AppPlatform_linux$finish(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::finish");
}

NINECRAFT_CSR_FUNCDEF(android_string_stlp_t, AppPlatform_linux$getDateStringSTLP, AppPlatform_linux *app_platform, unsigned int seconds) {
    puts("debug: AppPlatform_linux::getDateString");
    android_string_stlp_t str;
    char date[200];
    date_str(date, seconds);
    android_string_cstr((android_string_t *)&str, date);
    NINECRAFT_CSR_RETURN(str);
}

NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$getDateStringGNU, AppPlatform_linux *app_platform, unsigned int seconds) {
    puts("debug: AppPlatform_linux::getDateString");
    android_string_gnu_t str;
    char date[200];
    date_str(date, seconds);
    android_string_cstr((android_string_t *)&str, date);
    NINECRAFT_CSR_RETURN(str);
}

int AppPlatform_linux$getKeyFromKeyCode(AppPlatform_linux *app_platform, unsigned int key_code, unsigned int meta_state, unsigned int device_id) {
    puts("debug: AppPlatform_linux::getKeyFromKeyCode");
    return 0;
}

android_vector_t AppPlatform_linux$getOptionStrings(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getOptionsStrings");
    android_vector_t out;
    out._M_start = 0;
    out._M_finish = 0;
    out._M_end_of_storage = 0;
    for (int i = 0; i < app_platform->options->length; ++i) {
        ninecraft_option_t option = app_platform->options->options[i];
        android_string_t name;
        android_string_cstr(&name, option.name);
        android_vector_push_back(&out, &name, android_string_tsize());
        android_string_t value;
        android_string_cstr(&value, option.value);
        android_vector_push_back(&out, &value, android_string_tsize());
    }
    return out;
}

NINECRAFT_FLOAT_FUNC float AppPlatform_linux$getPixelsPerMillimeter(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getPixelsPerMillimeter");
    int cw, ch;
    glfwGetWindowSize(_window, &cw, &ch);
    return (((float)cw + (float)ch) * 0.5f ) / 25.4f;
}

NINECRAFT_CSR_FUNCDEF(android_string_stlp_t, AppPlatform_linux$getPlatformStringVarSTLP, AppPlatform_linux *app_platform, int zero) {
    puts("debug: AppPlatform_linux::getPlatformStringVar");
    android_string_stlp_t str;
    android_string_cstr((android_string_t *)&str, "Linux");
    NINECRAFT_CSR_RETURN(str);
}

NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$getPlatformStringVarGNU, AppPlatform_linux *app_platform, int zero) {
    puts("debug: AppPlatform_linux::getPlatformStringVar");
    android_string_gnu_t str;
    android_string_cstr((android_string_t *)&str, "Linux");
    NINECRAFT_CSR_RETURN(str);
}

int AppPlatform_linux$getScreenHeight(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getScreenHeight");
    int cw;
    int ch;
    glfwGetWindowSize(_window, &cw, &ch);
    return ch;
}

int AppPlatform_linux$getScreenWidth(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getScreenWidth");
    int cw;
    int ch;
    glfwGetWindowSize(_window, &cw, &ch);
    return cw;
}

android_vector_t AppPlatform_linux$getUserInput(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getUserInput");
    android_string_t name;
    android_string_t seed;
    android_string_t gamemode;
    FILE *fp = popen("zenity --entry --title='Create New World' --text='Enter World Name:'", "r");
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

    fp = popen("zenity --entry --title='Create New World' --text='Enter World Seed:'", "r");
    if (fp == NULL) {
        android_string_cstr(&seed, "random world");
    } else {
        char input_value[100];
        for (int i = 0; i < 100; ++i) {
            char c = fgetc(fp);
            if (c == '\n' || c == '\0' || c == EOF) {
                input_value[i] = '\0';
                break;
            } else if (c < '0' || c > '9') {
                input_value[0] = '\0';
                break;
            }
            input_value[i] = c;
        }
        input_value[99] = '\0';
        printf("%s\n", input_value);
        android_string_cstr(&seed, input_value);
        pclose(fp);
    }

    fp = popen("zenity --entry --title='Create New World' --text='Enter World Gamemode:' 'creative' 'survival'", "r");
    if (fp == NULL) {
        android_string_cstr(&seed, "random world");
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
    unsigned int size = 24;
    android_vector_t out;
    out._M_start = 0;
    out._M_finish = 0;
    out._M_end_of_storage = 0;
    puts("ok----");
    android_vector_push_back(&out, &name, android_string_tsize());
    android_vector_push_back(&out, &seed, android_string_tsize());
    android_vector_push_back(&out, &gamemode, android_string_tsize());

    printf("start: %u; finish: %u; end: %u;\n", out._M_start, out._M_finish, out._M_end_of_storage);
    return out;
}

int AppPlatform_linux$getUserInputStatus(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getUserInputStatus");
    return app_platform->status;
}

bool AppPlatform_linux$hasBuyButtonWhenInvalidLicense(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::hasBuyButtonWhenInvalidLicense");
    return true;
}

void AppPlatform_linux$hideKeyboard(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::hideKeyboard");
}

bool AppPlatform_linux$isKeyboardVisible(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::isKeyboardVisible");
    return false;
}

bool AppPlatform_linux$isNetworkEnabled(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::isNetworkEnabled");
    return true;
}

bool AppPlatform_linux$isPowerVR(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::isPowerVR");
    return false;
}

bool AppPlatform_linux$isTouchscreen(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::isTouchscreen");
    for (size_t i = 0; i < app_platform->options->length; ++i) {
        if (strcmp(app_platform->options->options[i].name, "ctrl_usetouchscreen") == 0) {
            if (strcmp(app_platform->options->options[i].value, "true") == 0) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

texture_data_t AppPlatform_linux$loadTexture(AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha) {
    puts("debug: AppPlatform_linux::loadTexture");
    char *resource = android_string_to_str(path_str);
    char path[MAXPATHLEN];
    getcwd(path, MAXPATHLEN);
    strcat(path, "/overrides/assets/");
    strcat(path, resource);
    if (access(path, F_OK) != 0) {
        getcwd(path, MAXPATHLEN);
        strcat(path, "/internal_overrides/assets/");
        strcat(path, resource);
        if (access(path, F_OK) != 0) {
            getcwd(path, MAXPATHLEN);
            strcat(path, "/assets/");
            strcat(path, resource);
        }
    }
    texture_data_t texture_data = {
        .unknown = 0,
        .alpha = 1,
        .keep_buffer_data = 0,
        .texture_type = texture_type_ub,
        .unknown2 = 0xffffffff
    };
    texture_data.pixels = stbi_load(path, &texture_data.width, &texture_data.height, NULL, STBI_rgb_alpha);
    return texture_data;
}

texture_data_old_t AppPlatform_linux$loadTextureOld(AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha) {
    puts("debug: AppPlatform_linux::loadTexture");
    char *resource = android_string_to_str(path_str);
    char path[MAXPATHLEN];
    getcwd(path, MAXPATHLEN);
    strcat(path, "/overrides/assets/");
    strcat(path, resource);
    if (access(path, F_OK) != 0) {
        getcwd(path, MAXPATHLEN);
        strcat(path, "/internal_overrides/assets/");
        strcat(path, resource);
        if (access(path, F_OK) != 0) {
            getcwd(path, MAXPATHLEN);
            strcat(path, "/assets/");
            strcat(path, resource);
        }
    }
    texture_data_old_t texture_data = {
        .alpha = 1,
        .keep_buffer_data = 0
    };
    texture_data.pixels = stbi_load(path, &texture_data.width, &texture_data.height, NULL, STBI_rgb_alpha);
    return texture_data;
}

NINECRAFT_FLOAT_FUNC void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, android_string_t *sound_name, float volume, float pitch) {
    puts("debug: AppPlatform_linux::playSound");
    ninecraft_sound_resource_t *res = ninecraft_get_sound_buffer(android_string_to_str(sound_name));
    audio_engine_play(res->buffer, res->buffer_size, res->num_channels, res->bits_per_sample, res->freq, volume, pitch);
}

asset_file AppPlatform_linux$readAssetFile(AppPlatform_linux *app_platform, android_string_t *path_str) {
    puts("debug: AppPlatform_linux::readAssetFile");
    android_string_t str;
    char *path = android_string_to_str(path_str);
    size_t pathlen = strlen(path);
    char *fullpath_original = (char *) malloc(10 + pathlen);
    memcpy(fullpath_original, "./assets/", 9);
    memcpy(fullpath_original+9, path, pathlen+1);
    char *fullpath_internal_overrides = (char *) malloc(29 + pathlen);
    memcpy(fullpath_internal_overrides, "./internal_overrides/assets/", 28);
    memcpy(fullpath_internal_overrides+28, path, pathlen+1);
    char *fullpath_overrides = (char *) malloc(20 + pathlen);
    memcpy(fullpath_overrides, "./overrides/assets/", 19);
    memcpy(fullpath_overrides+19, path, pathlen+1);
    char *fullpath = NULL;
    if(access(fullpath_overrides, F_OK) == 0) {
        fullpath = fullpath_overrides;
    } else if(access(fullpath_internal_overrides, F_OK) == 0) {
        fullpath = fullpath_internal_overrides;
    } else if(access(fullpath_original, F_OK) == 0) {
        fullpath = fullpath_original;
    }
    asset_file asset;

    FILE *file = fopen(fullpath, "r");
    if (!file) {
        printf("Error[%d] failed to read %s\n", errno, fullpath);
        android_string_cstr(&str, "");
        asset.data = 0;
        asset.size = -1;
        return asset;
    }
    printf("Read asset: %s\n", fullpath);
    fseek(file, 0, SEEK_END);
    asset.size = ftell(file);
    asset.data = (char *) malloc(asset.size);
    fseek(file, 0, SEEK_SET);
    fread(asset.data, 1, asset.size, file);
    free(fullpath_original);
    free(fullpath_internal_overrides);
    free(fullpath_overrides);
    return asset;
}

NINECRAFT_CSR_FUNCDEF(android_string_gnu_t, AppPlatform_linux$readAssetFile_0_9_0, AppPlatform_linux *app_platform, android_string_t *path_str) {
    asset_file asset = AppPlatform_linux$readAssetFile(app_platform, path_str);
    android_string_gnu_t str;
    android_string_cstrl(&str, asset.data, asset.size);
    NINECRAFT_CSR_RETURN(str);
}

void AppPlatform_linux$saveScreenshot(AppPlatform_linux *app_platform, android_string_t *path, int width, int height) {
    puts("debug: AppPlatform_linux::saveScreenshot");
}

void AppPlatform_linux$showDialog(AppPlatform_linux *app_platform, int dialog_id) {
    puts("debug: AppPlatform_linux::showDialog");
    if (dialog_id == did_new_world) {
        puts("Create New World");
        app_platform->status = 1;
    } else if (dialog_id == did_options) {
        puts("Options");
    } else if (dialog_id == did_rename_world) {
        puts("Rename World");
    }
}

void AppPlatform_linux$showKeyboard(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::showKeyboard");
}

void AppPlatform_linux$showKeyboard2(AppPlatform_linux *app_platform, bool show) {
    puts("debug: AppPlatform_linux::showKeyboard2");
}

void AppPlatform_linux$uploadPlatformDependentData(AppPlatform_linux *app_platform, int size, void *data) {
    puts("debug: AppPlatform_linux::uploadPlatformDependentData");
}

void AppPlatform_linux$vibrate(AppPlatform_linux *app_platform, int milliseconds) {
    puts("debug: AppPlatform_linux::vibrate");
}

void AppPlatform_linux$destroy(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::destroy");
}
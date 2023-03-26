#include <ninecraft/AppPlatform_linux.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/version_ids.h>
#include <unistd.h>
#include <GLFW/glfw3.h>
#include <ninecraft/ninecraft_defs.h>

extern GLFWwindow *_window;

void *app_platform_vtable_0_4_0[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateString,
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
    (void *)AppPlatform_linux$getPlatformStringVar
};

void *app_platform_vtable_0_6_1[] = {
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$destroy,
    (void *)AppPlatform_linux$saveScreenshot,
    (void *)AppPlatform_linux$loadTexture,
    (void *)AppPlatform_linux$playSound,
    (void *)AppPlatform_linux$showDialog,
    (void *)AppPlatform_linux$createUserInput,
    (void *)AppPlatform_linux$getUserInputStatus,
    (void *)AppPlatform_linux$getUserInput,
    (void *)AppPlatform_linux$getDateString,
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
    (void *)AppPlatform_linux$getPlatformStringVar,
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
    (void *)AppPlatform_linux$getDateString,
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
    (void *)AppPlatform_linux$getPlatformStringVar,
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
    (void *)AppPlatform_linux$getDateString,
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
    (void *)AppPlatform_linux$getPlatformStringVar,
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

void AppPlatform_linux$initWithActivity(AppPlatform_linux *app_platform, void *activity) {
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

void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle, int version_id) {
    if (version_id == version_id_0_6_1) {
        app_platform->vtable = app_platform_vtable_0_6_1;
    } else if (version_id == version_id_0_5_0) {
        app_platform->vtable = app_platform_vtable_0_4_0;
    } else if (version_id == version_id_0_4_0) {
        app_platform->vtable = app_platform_vtable_0_4_0;
    } else if (version_id == version_id_0_7_0) {
        app_platform->vtable = app_platform_vtable_0_7_0;
    } else if (version_id == version_id_0_7_2) {
        app_platform->vtable = app_platform_vtable_0_7_2;
    }
    app_platform->handle = handle;
    app_platform->status = -1;
    app_platform->version_id = version_id;
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

android_string_t AppPlatform_linux$getDateString(AppPlatform_linux *app_platform, unsigned int seconds) {
    puts("debug: AppPlatform_linux::getDateString");
    android_string_t str;

    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int currYear, daysTillNow, extraTime, extraDays, index, date, month, hours, minutes, secondss, flag = 0;
 
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;
 
    // Calculating current year
    while (daysTillNow >= 365) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0
                && currYear % 100 != 0)) {
            daysTillNow -= 366;
        }
        else {
            daysTillNow -= 365;
        }
        currYear += 1;
    }

    extraDays = daysTillNow + 1;
 
    if (currYear % 400 == 0
        || (currYear % 4 == 0
            && currYear % 100 != 0))
        flag = 1;
 
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {
 
            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays
                        - daysOfMonth[index]
                    < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {
 
            if (extraDays
                    - daysOfMonth[index]
                < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }
 
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }
 
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;

    char ans[200];
    
    sprintf(ans, "%d/%d/%d %d:%d:%d", date, month, currYear, hours, minutes, secondss);
    
    android_string_cstr(&str, (char *) ans);
    return str;
}

int AppPlatform_linux$getKeyFromKeyCode(AppPlatform_linux *app_platform, unsigned int key_code, unsigned int meta_state, unsigned int device_id) {
    puts("debug: AppPlatform_linux::getKeyFromKeyCode");
    return 0;
}

android_vector_t AppPlatform_linux$getOptionStrings(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getOptionsStrings");
    android_string_t username_name; // mp_username
    android_string_t username_value; // Steve
    android_string_t server_name; // mp_server
    android_string_t server_value; // Ninecraft
    android_string_t server_visible_name; // mp_server_visible_default
    android_string_t server_visible_value; // true
    android_string_t fancygraphics_name; // gfx_fancygraphics
    android_string_t fancygraphics_value; // true
    android_string_t lowquality_name; // gfx_lowquality
    android_string_t lowquality_value; // false
    android_string_t sensitivity_name; // ctrl_sensitivity
    android_string_t sensitivity_value; // gcvt(0.01 * 100) 100
    android_string_t invertmouse_name; // ctrl_invertmouse
    android_string_t invertmouse_value; // false
    android_string_t islefthanded_name; // ctrl_islefthanded
    android_string_t islefthanded_value; // false
    android_string_t usetouchscreen_name; // ctrl_usetouchscreen
    android_string_t usetouchscreen_value; // false
    android_string_t usetouchjoypad_name; // ctrl_usetouchjoypad
    android_string_t usetouchjoypad_value; // true
    android_string_t vibration_name; // feedback_vibration
    android_string_t vibration_value; // false
    android_string_t difficulty_name; // game_difficulty
    android_string_t difficulty_value; // 0, 4
    unsigned int size = 24;
    char tmp[100];
    android_string_cstr(&username_name, "mp_username");
    FILE *fp = popen("zenity --entry --title='Profile' --text='Enter Username:'", "r");
    if (fp == NULL) {
        android_string_cstr(&username_value, "Steve");
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
        if (input_value[0] != 0) {
            android_string_cstr(&username_value, input_value);
        } else {
            android_string_cstr(&username_value, "Steve");
        }
        pclose(fp);
    }
    android_string_cstr(&server_name, "mp_server");
    android_string_cstr(&server_value, "Ninecraft");
    android_string_cstr(&server_visible_name, "mp_server_visible_default");
    android_string_cstr(&server_visible_value, "true");
    android_string_cstr(&fancygraphics_name, "gfx_fancygraphics");
    android_string_cstr(&fancygraphics_value, "true");
    android_string_cstr(&lowquality_name, "gfx_lowquality");
    android_string_cstr(&lowquality_value, "false");
    android_string_cstr(&sensitivity_name, "ctrl_sensitivity");
    android_string_cstr(&sensitivity_value, gcvt(0.01 * 100, 6, tmp));
    android_string_cstr(&invertmouse_name, "ctrl_invertmouse");
    android_string_cstr(&invertmouse_value, "false");
    android_string_cstr(&islefthanded_name, "ctrl_islefthanded");
    android_string_cstr(&islefthanded_value, "false");
    android_string_cstr(&usetouchscreen_name, "ctrl_usetouchscreen");
    android_string_cstr(&usetouchscreen_value, "false");
    android_string_cstr(&usetouchjoypad_name, "ctrl_usetouchjoypad");
    android_string_cstr(&usetouchjoypad_value, "false");
    android_string_cstr(&vibration_name, "feedback_vibration");
    android_string_cstr(&vibration_value, "false");
    android_string_cstr(&difficulty_name, "game_difficulty");
    android_string_cstr(&difficulty_value, "4");
    android_vector_t out;
    out._M_start = 0;
    out._M_finish = 0;
    out._M_end_of_storage = 0;
    android_vector_push_back(&out, &username_name, sizeof(android_string_t));
    android_vector_push_back(&out, &username_value, sizeof(android_string_t));
    android_vector_push_back(&out, &server_name, sizeof(android_string_t));
    android_vector_push_back(&out, &server_value, sizeof(android_string_t));
    android_vector_push_back(&out, &server_visible_name, sizeof(android_string_t));
    android_vector_push_back(&out, &server_visible_value, sizeof(android_string_t));
    android_vector_push_back(&out, &fancygraphics_name, sizeof(android_string_t));
    android_vector_push_back(&out, &fancygraphics_value, sizeof(android_string_t));
    android_vector_push_back(&out, &lowquality_name, sizeof(android_string_t));
    android_vector_push_back(&out, &lowquality_value, sizeof(android_string_t));
    android_vector_push_back(&out, &sensitivity_name, sizeof(android_string_t));
    android_vector_push_back(&out, &sensitivity_value, sizeof(android_string_t));
    android_vector_push_back(&out, &invertmouse_name, sizeof(android_string_t));
    android_vector_push_back(&out, &invertmouse_value, sizeof(android_string_t));
    android_vector_push_back(&out, &islefthanded_name, sizeof(android_string_t));
    android_vector_push_back(&out, &islefthanded_value, sizeof(android_string_t));
    android_vector_push_back(&out, &usetouchscreen_name, sizeof(android_string_t));
    android_vector_push_back(&out, &usetouchscreen_value, sizeof(android_string_t));
    android_vector_push_back(&out, &usetouchjoypad_name, sizeof(android_string_t));
    android_vector_push_back(&out, &usetouchjoypad_value, sizeof(android_string_t));
    android_vector_push_back(&out, &vibration_name, sizeof(android_string_t));
    android_vector_push_back(&out, &vibration_value, sizeof(android_string_t));
    android_vector_push_back(&out, &difficulty_name, sizeof(android_string_t));
    android_vector_push_back(&out, &difficulty_value, sizeof(android_string_t));
    printf("start: %u; finish: %u; end: %u;\n", out._M_start, out._M_finish, out._M_end_of_storage);
    return out;
}

NINECRAFT_FLOAT_FUNC float AppPlatform_linux$getPixelsPerMillimeter(AppPlatform_linux *app_platform) {
    puts("debug: AppPlatform_linux::getPixelsPerMillimeter");
    int cw, ch;
    glfwGetWindowSize(_window, &cw, &ch);
    return (((float)cw + (float)ch) * 0.5f ) / 25.4f;
}

android_string_t AppPlatform_linux$getPlatformStringVar(AppPlatform_linux *app_platform, int zero) {
    puts("debug: AppPlatform_linux::getPlatformStringVar");
    android_string_t str;
    android_string_cstr(&str, "Linux");
    return str;
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
    android_vector_push_back(&out, &name, sizeof(android_string_t));
    android_vector_push_back(&out, &seed, sizeof(android_string_t));
    android_vector_push_back(&out, &gamemode, sizeof(android_string_t));

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
    return false;
}

texture_data_t AppPlatform_linux$loadTexture(AppPlatform_linux *app_platform, android_string_t *path_str, bool alpha) {
    puts("debug: AppPlatform_linux::loadTexture");
    printf("%p\n", app_platform);
    char *path = (char *)path_str->_M_start_of_storage;
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
    texture_data_t texture_data = read_png(fullpath, alpha, false);
    free(fullpath_original);
    free(fullpath_internal_overrides);
    free(fullpath_overrides);
    return texture_data;
}

NINECRAFT_FLOAT_FUNC void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, android_string_t *sound_name, float volume, float pitch) {
    puts("debug: AppPlatform_linux::playSound");
}

asset_file AppPlatform_linux$readAssetFile(AppPlatform_linux *app_platform, android_string_t *path_str) {
    puts("debug: AppPlatform_linux::readAssetFile");
    android_string_t str;
    char *path = (char *)path_str->_M_start_of_storage;
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
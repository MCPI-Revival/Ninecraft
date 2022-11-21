#include <ninecraft/AppPlatform_linux.hpp>
#include <cstdlib>
#include <errno.h>
#include <ninecraft/android_alloc.hpp>

void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle) {
    app_platform->vtable = (void **) operator new(31 * sizeof(void *));
    app_platform->vtable[0] = (void *) AppPlatform_linux$destroy;
    app_platform->vtable[1] = (void *) AppPlatform_linux$destroy;
    app_platform->vtable[2] = (void *) AppPlatform_linux$saveScreenshot;
    app_platform->vtable[3] = (void *) AppPlatform_linux$loadTexture;
    app_platform->vtable[4] = (void *) AppPlatform_linux$playSound;
    app_platform->vtable[5] = (void *) AppPlatform_linux$showDialog;
    app_platform->vtable[6] = (void *) AppPlatform_linux$createUserInput;
    app_platform->vtable[7] = (void *) AppPlatform_linux$getUserInputStatus;
    app_platform->vtable[8] = (void *) AppPlatform_linux$getUserInput;
    app_platform->vtable[9] = (void *) AppPlatform_linux$getDateString;
    app_platform->vtable[10] = (void *) AppPlatform_linux$checkLicense;
    app_platform->vtable[11] = (void *) AppPlatform_linux$hasBuyButtonWhenInvalidLicense;
    app_platform->vtable[12] = (void *) AppPlatform_linux$uploadPlatformDependentData;
    app_platform->vtable[13] = (void *) AppPlatform_linux$readAssetFile;
    app_platform->vtable[14] = (void *) AppPlatform_linux$_tick;
    app_platform->vtable[15] = (void *) AppPlatform_linux$getScreenWidth;
    app_platform->vtable[16] = (void *) AppPlatform_linux$getScreenHeight;
    app_platform->vtable[17] = (void *) AppPlatform_linux$getPixelsPerMillimeter;
    app_platform->vtable[18] = (void *) AppPlatform_linux$isNetworkEnabled;
    app_platform->vtable[19] = (void *) AppPlatform_linux$getOptionStrings;
    app_platform->vtable[20] = (void *) AppPlatform_linux$isPowerVR;
    app_platform->vtable[21] = (void *) AppPlatform_linux$getKeyFromKeyCode;
    app_platform->vtable[22] = (void *) AppPlatform_linux$buyGame;
    app_platform->vtable[23] = (void *) AppPlatform_linux$finish;
    app_platform->vtable[24] = (void *) AppPlatform_linux$isTouchscreen;
    app_platform->vtable[25] = (void *) AppPlatform_linux$vibrate;
    app_platform->vtable[26] = (void *) AppPlatform_linux$getPlatformStringVar;
    app_platform->vtable[27] = (void *) AppPlatform_linux$showKeyboard;
    app_platform->vtable[28] = (void *) AppPlatform_linux$hideKeyboard;
    app_platform->vtable[29] = (void *) AppPlatform_linux$isKeyboardVisible;
    app_platform->vtable[30] = (void *) AppPlatform_linux$showKeyboard;
    app_platform->handle = handle;
    app_platform->status = -1;
}

void AppPlatform_linux$_tick(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::_tick" << std::endl;
}

void AppPlatform_linux$buyGame(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::buyGame" << std::endl;
}
 
int AppPlatform_linux$checkLicense(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::checkLicense" << std::endl;
    return 0;
}

void AppPlatform_linux$createUserInput(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::createUserInput" << std::endl;
    app_platform->status = 1;
    //app_platform->user_input_text = NULL;
}

void AppPlatform_linux$finish(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::finish" << std::endl;
}

android_string AppPlatform_linux$getDateString(AppPlatform_linux *app_platform, unsigned int seconds) {
    std::cout << "debug: AppPlatform_linux::getDateString" << std::endl;
    android_string str;

    std::string ans = "";

    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long int currYear, daysTillNow, extraTime, extraDays, index, date, month, hours, minutes, secondss, flag = 0;
 
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

    ans += std::to_string(date);
    ans += "/";
    ans += std::to_string(month);
    ans += "/";
    ans += std::to_string(currYear);
    ans += " ";
    ans += std::to_string(hours);
    ans += ":";
    ans += std::to_string(minutes);
    ans += ":";
    ans += std::to_string(secondss);

    to_str(&str, (char *) ans.c_str(), app_platform->handle);
    return str;
}

int AppPlatform_linux$getKeyFromKeyCode(AppPlatform_linux *app_platform, unsigned int key_code, unsigned int meta_state, unsigned int device_id) {
    std::cout << "debug: AppPlatform_linux::getKeyFromKeyCode" << std::endl;
    return 0;
}

android_vector AppPlatform_linux$getOptionStrings(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getOptionsStrings" << std::endl;
    android_string username_name; // mp_username
    android_string username_value; // Steve
    android_string server_visible_name; // mp_server_visible_default
    android_string server_visible_value; // true
    android_string fancygraphics_name; // gfx_fancygraphics
    android_string fancygraphics_value; // true
    android_string lowquality_name; // gfx_lowquality
    android_string lowquality_value; // false
    android_string sensitivity_name; // ctrl_sensitivity
    android_string sensitivity_value; // gcvt(0.01 * 100) 100
    android_string invertmouse_name; // ctrl_invertmouse
    android_string invertmouse_value; // false
    android_string islefthanded_name; // ctrl_islefthanded
    android_string islefthanded_value; // false
    android_string usetouchscreen_name; // ctrl_usetouchscreen
    android_string usetouchscreen_value; // false
    android_string difficulty_name; // game_difficulty
    android_string difficulty_value; // 0, 4
    unsigned int size = 24;
    char tmp[100];
    to_str(&username_name, "mp_username", app_platform->handle);
    to_str(&username_value, "Ninecraft", app_platform->handle);
    to_str(&server_visible_name, "mp_server_visible_default", app_platform->handle);
    to_str(&server_visible_value, "true", app_platform->handle);
    to_str(&fancygraphics_name, "gfx_fancygraphics", app_platform->handle);
    to_str(&fancygraphics_value, "true", app_platform->handle);
    to_str(&lowquality_name, "gfx_lowquality", app_platform->handle);
    to_str(&lowquality_value, "false", app_platform->handle);
    to_str(&sensitivity_name, "ctrl_sensitivity", app_platform->handle);
    to_str(&sensitivity_value, gcvt(0.01 * 100, 6, tmp), app_platform->handle);
    to_str(&invertmouse_name, "ctrl_invertmouse", app_platform->handle);
    to_str(&invertmouse_value, "false", app_platform->handle);
    to_str(&islefthanded_name, "ctrl_islefthanded", app_platform->handle);
    to_str(&islefthanded_value, "false", app_platform->handle);
    to_str(&usetouchscreen_name, "ctrl_usetouchscreen", app_platform->handle);
    to_str(&usetouchscreen_value, "false", app_platform->handle);
    to_str(&difficulty_name, "game_difficulty", app_platform->handle);
    to_str(&difficulty_value, "4", app_platform->handle);
    android_vector out;
    out._M_start = (unsigned long)android_alloc$allocate(&size, app_platform->handle);
    out._M_finish = out._M_start;
    out._M_end_of_storage = out._M_start + 24;
    android_vector$push_back(&out, &username_name, app_platform->handle);
    android_vector$push_back(&out, &username_value, app_platform->handle);
    //android_vector$push_back(&out, &server_visible_name, app_platform->handle);
    //android_vector$push_back(&out, &server_visible_value, app_platform->handle);
    //android_vector$push_back(&out, &fancygraphics_name, app_platform->handle);
    //android_vector$push_back(&out, &fancygraphics_value, app_platform->handle);
    //android_vector$push_back(&out, &lowquality_name, app_platform->handle);
    //android_vector$push_back(&out, &lowquality_value, app_platform->handle);
    //android_vector$push_back(&out, &sensitivity_name, app_platform->handle);
    //android_vector$push_back(&out, &sensitivity_value, app_platform->handle);
    //android_vector$push_back(&out, &invertmouse_name, app_platform->handle);
    //android_vector$push_back(&out, &invertmouse_value, app_platform->handle);
    //android_vector$push_back(&out, &islefthanded_name, app_platform->handle);
    //android_vector$push_back(&out, &islefthanded_value, app_platform->handle);
    //android_vector$push_back(&out, &usetouchscreen_name, app_platform->handle);
    //android_vector$push_back(&out, &usetouchscreen_value, app_platform->handle);
    //android_vector$push_back(&out, &difficulty_name, app_platform->handle);
    //android_vector$push_back(&out, &difficulty_value, app_platform->handle);
    printf("start: %u; finish: %u; end: %u;\n", out._M_start, out._M_finish, out._M_end_of_storage);
    return out;
}

float AppPlatform_linux$getPixelsPerMillimeter(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getPixelsPerMillimeter" << std::endl;
    return 1.f;
}

android_string AppPlatform_linux$getPlatformStringVar(AppPlatform_linux *app_platform, int zero) {
    std::cout << "debug: AppPlatform_linux::getPlatformStringVar" << std::endl;
    android_string str;
    to_str(&str, "Linux", app_platform->handle);
    return str;
}

int AppPlatform_linux$getScreenHeight(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getScreenHeight" << std::endl;
    return 1440;
}

int AppPlatform_linux$getScreenWidth(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getScreenWidth" << std::endl;
    return 900;
}

android_vector AppPlatform_linux$getUserInput(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getUserInput" << std::endl;
    android_string name;
    android_string seed;
    android_string gamemode;
    to_str(&name, "random world", app_platform->handle);
    to_str(&seed, "12345678", app_platform->handle);
    to_str(&gamemode, "creative", app_platform->handle);
    unsigned int size = 24;
    android_vector out;
    out._M_start = (unsigned long)android_alloc$allocate(&size, app_platform->handle);
    out._M_finish = out._M_start;
    out._M_end_of_storage = out._M_start + 24;
    puts("ok----");
    android_vector$push_back(&out, &name, app_platform->handle);
    android_vector$push_back(&out, &seed, app_platform->handle);
    android_vector$push_back(&out, &gamemode, app_platform->handle);

    printf("start: %u; finish: %u; end: %u;\n", out._M_start, out._M_finish, out._M_end_of_storage);
    return out;
}

int AppPlatform_linux$getUserInputStatus(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getUserInputStatus" << std::endl;
    return app_platform->status;
}

bool AppPlatform_linux$hasBuyButtonWhenInvalidLicense(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::hasBuyButtonWhenInvalidLicense" << std::endl;
    return true;
}

void AppPlatform_linux$hideKeyboard(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::hideKeyboard" << std::endl;
}

bool AppPlatform_linux$isKeyboardVisible(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::isKeyboardVisible" << std::endl;
    return false;
}

bool AppPlatform_linux$isNetworkEnabled(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::isNetworkEnabled" << std::endl;
    return true;
}

bool AppPlatform_linux$isPowerVR(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::isPowerVR" << std::endl;
    return false;
}

bool AppPlatform_linux$isTouchscreen(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::isTouchscreen" << std::endl;
    return false;
}

TextureData AppPlatform_linux$loadTexture(AppPlatform_linux *app_platform, void *path_str, bool alpha) {
    std::cout << "debug: AppPlatform_linux::loadTexture" << std::endl;
    printf("%p\n", app_platform);
    char *path = *(char **)(path_str + 20);
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
    TextureData texture_data = read_png(fullpath, alpha, false);
    free(fullpath_original);
    free(fullpath_internal_overrides);
    free(fullpath_overrides);
    return texture_data;
}

void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, const android_string& sound_name, float volume, float pitch) {
    std::cout << "debug: AppPlatform_linux::playSound" << std::endl;
}

asset_file AppPlatform_linux$readAssetFile(AppPlatform_linux *app_platform, void *path_str) {
    std::cout << "debug: AppPlatform_linux::readAssetFile" << std::endl;
    android_string str;
    char *path = *(char **)(path_str + 20);
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
        to_str(&str, "", app_platform->handle);
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
    asset.size;
    free(fullpath_original);
    free(fullpath_internal_overrides);
    free(fullpath_overrides);
    return asset;
}

void AppPlatform_linux$saveScreenshot(AppPlatform_linux *app_platform, const android_string& path, int width, int height) {
    std::cout << "debug: AppPlatform_linux::saveScreenshot" << std::endl;
}

void AppPlatform_linux$showDialog(AppPlatform_linux *app_platform, int dialog_id) {
    std::cout << "debug: AppPlatform_linux::showDialog" << std::endl;
    if (dialog_id == did_new_world) {
        std::cout << "Create New World" << std::endl;
        app_platform->status = 1;
    } else if (dialog_id == did_options) {
        std::cout << "Options" << std::endl;
    } else if (dialog_id == did_rename_world) {
        std::cout << "Rename World" << std::endl;
    }
}

void AppPlatform_linux$showKeyboard(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::showKeyboard" << std::endl;
}

void AppPlatform_linux$uploadPlatformDependentData(AppPlatform_linux *app_platform, int size, void *data) {
    std::cout << "debug: AppPlatform_linux::uploadPlatformDependentData" << std::endl;
}

void AppPlatform_linux$vibrate(AppPlatform_linux *app_platform, int milliseconds) {
    std::cout << "debug: AppPlatform_linux::vibrate" << std::endl;
}

void AppPlatform_linux$destroy(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::destroy" << std::endl;
    operator delete(app_platform->vtable);
}
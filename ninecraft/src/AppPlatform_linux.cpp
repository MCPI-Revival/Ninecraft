#include <ninecraft/AppPlatform_linux.hpp>
#include <cstdlib>
#include <errno.h>

void AppPlatform_linux$AppPlatform_linux(AppPlatform_linux *app_platform, void *handle) {
    memset(app_platform->filler, 0, 0xd0);
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

int AppPlatform_linux$getOptionStrings(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getOptionsStrings" << std::endl;
    /*std::string *strarr = new std::string[1024];
    for (unsigned int i = 0; i < 1024; ++i) {
        strarr[i] = NULL;
    }
    return strarr;*/
    char *buf = (char *) hybris_dlsym(app_platform->handle, "_ZZN19AppPlatform_android16getOptionStringsEvE3buf");
    return 1;
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

android_string *AppPlatform_linux$getUserInput(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getUserInput" << std::endl;
    return NULL;
}

int AppPlatform_linux$getUserInputStatus(AppPlatform_linux *app_platform) {
    std::cout << "debug: AppPlatform_linux::getUserInputStatus" << std::endl;
    return -1;
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
    char *fullpath = (char *) malloc(10 + pathlen);
    fullpath[0] = '.';
    fullpath[1] = '/';
    fullpath[2] = 'a';
    fullpath[3] = 's';
    fullpath[4] = 's';
    fullpath[5] = 'e';
    fullpath[6] = 't';
    fullpath[7] = 's';
    fullpath[8] = '/';
    memcpy(fullpath+9, path, pathlen+1);
    return read_png(fullpath, alpha, false);
}

void AppPlatform_linux$playSound(AppPlatform_linux *app_platform, const android_string& sound_name, float volume, float pitch) {
    std::cout << "debug: AppPlatform_linux::playSound" << std::endl;
}

asset_file AppPlatform_linux$readAssetFile(AppPlatform_linux *app_platform, void *path_str) {
    std::cout << "debug: AppPlatform_linux::readAssetFile" << std::endl;
    android_string str;
    char *path = *(char **)(path_str + 20);
    size_t pathlen = strlen(path);
    char *fullpath = (char *) malloc(8 + pathlen);

    fullpath[0] = 'a';
    fullpath[1] = 's';
    fullpath[2] = 's';
    fullpath[3] = 'e';
    fullpath[4] = 't';
    fullpath[5] = 's';
    fullpath[6] = '/';
    asset_file asset;

    memcpy(fullpath+7, path, pathlen+1);

    FILE *file = fopen(fullpath, "r");
    if (!file) {
        printf("Error[%d] failed to read %s\n", errno, fullpath);
        to_str((void *) &str, "", app_platform->handle);
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
    return asset;
}

void AppPlatform_linux$saveScreenshot(AppPlatform_linux *app_platform, const android_string& path, int width, int height) {
    std::cout << "debug: AppPlatform_linux::saveScreenshot" << std::endl;
}

void AppPlatform_linux$showDialog(AppPlatform_linux *app_platform, int dialog_id) {
    std::cout << "debug: AppPlatform_linux::showDialog" << std::endl;
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
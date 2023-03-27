# Ninecraft

![alt screenshot](https://raw.githubusercontent.com/MCPI-Revival/Ninecraft/master/screenshots/Screenshot%20from%202022-09-10%2000-45-48.png)

## Compile dependencies
### Debian/Ubuntu:
x86:
```
git make cmake gcc gcc-multilib g++ zlib1g-dev:i386 libpng-dev:i386 zlib1g-dev libpng-dev libopenal-dev:i386 libopenal-dev libx11-dev:i386 libx11-dev libxrandr-dev:i386 libxrandr-dev libxinerama-dev:i386 libxinerama-dev libxcursor-dev:i386 libxcursor-dev libxi-dev:i386 libxi-dev libgles-dev:i386 libgles-dev zenity patchelf
```
ARM:
```
git make cmake gcc g++ zlib1g-dev:armhf libpng-dev:armhf zlib1g-dev libpng-dev libopenal-dev:armhf libopenal-dev libx11-dev:armhf libx11-dev libxrandr-dev:armhf libxrandr-dev libxinerama-dev:armhf libxinerama-dev libxcursor-dev:armhf libxcursor-dev libxi-dev:armhf libxi-dev libgles-dev:armhf libgles-dev zenity patchelf
```
### ArchLinux:
```
git make cmake gcc gcc-multilib zlib lib32-zlib libpng lib32-libpng openal lib32-openal libx11 lib32-libx11 libxrandr lib32-libxrandr libxinerama lib32-libxinerama libxcursor lib32-libxcursor libxi lib32-libxi libglvnd lib32-libglvnd zenity patchelf
```

## Compiling
```
git clone --recursive http://github.com/MCPI-Revival/Ninecraft.git
cd Ninecraft
make
```    

## Before running for the first time
### x86:
```
./tools/extract.sh /path/to/your/apk
./tools/patch.sh x86
```
### ARM
```
./tools/extract.sh /path/to/your/apk
./tools/patch.sh armeabi-v7a
```

## Running
```
./build/ninecraft/ninecraft
```

## Creating mods
### Example mod
```c
#include <stdio.h>

extern void *handle;
extern void *ninecraft_app;

int mod_init() {
    puts("TEST > Loaded mod");
}
```
### Compiling

To compile you must include the ninecraft header files
in your project's root directory

#### x86
```
gcc -m32 -c -fpic -I./ninecraft/include test.c
gcc -m32 -shared -o mods/libtest.so test.o
```
#### ARM
```
gcc -mthumb -c -fpic -I./ninecraft/include test.c
gcc -mthumb -shared -o mods/libtest.so test.o
```

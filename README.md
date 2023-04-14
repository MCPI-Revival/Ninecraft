# Ninecraft

![alt screenshot](https://raw.githubusercontent.com/MCPI-Revival/Ninecraft/master/screenshots/Screenshot%20from%202022-09-10%2000-45-48.png)

## Installing compile dependencies
### Debian/Ubuntu:
x86_64 & arm64:
```
sudo dpkg --add-architecture armhf
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install git make cmake gcc-i686-linux-gnu g++-i686-linux-gnu gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf libopenal-dev:armhf libopenal-dev:i386 libx11-dev:armhf libx11-dev:i386 libxrandr-dev:armhf libxrandr-dev:i386 libxinerama-dev:armhf libxinerama-dev:i386 libxcursor-dev:armhf libxcursor-dev:i386 libxi-dev:armhf libxi-dev:i386 libgles-dev:armhf libgles-dev:i386 zenity patchelf
```
x86:
```
sudo dpkg --add-architecture armhf
sudo apt update
sudo apt install git make cmake gcc g++ gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf libopenal-dev:armhf libopenal-dev libx11-dev:armhf libx11-dev libxrandr-dev:armhf libxrandr-dev libxinerama-dev:armhf libxinerama-dev libxcursor-dev:armhf libxcursor-dev libxi-dev:armhf libxi-dev libgles-dev:armhf libgles-dev zenity patchelf
```
arm:
```
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install git make cmake gcc g++ gcc-i686-linux-gnu g++-i686-linux-gnu libopenal-dev:i386 libopenal-dev libx11-dev:i386 libx11-dev libxrandr-dev:i386 libxrandr-dev libxinerama-dev:i386 libxinerama-dev libxcursor-dev:i386 libxcursor-dev libxi-dev:i386 libxi-dev libgles-dev:i386 libgles-dev zenity patchelf
```

## Compiling
```
git clone --recursive http://github.com/MCPI-Revival/Ninecraft.git
cd Ninecraft
make
```    

## Before running for the first time
### x86_64 & x86:
```
./tools/extract.sh /path/to/your/apk
./tools/patch.sh x86
```
### arm64 & arm
```
./tools/extract.sh /path/to/your/apk
./tools/patch.sh armeabi-v7a
```

## Running
### x86_64 & x86:
```
./build-i686/ninecraft/ninecraft
```
### arm64 & arm
```
./build-arm/ninecraft/ninecraft
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

# Ninecraft

![alt screenshot](https://raw.githubusercontent.com/MCPI-Revival/Ninecraft/master/screenshots/Screenshot%20from%202022-09-10%2000-45-48.png)

## Installing compile dependencies
### Debian/Ubuntu:
x86_64:
```
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install git make cmake gcc g++ gcc-multilib g++-multilib libopenal-dev:i386 libx11-dev:i386 libxrandr-dev:i386 libxinerama-dev:i386 libxcursor-dev:i386 libxi-dev:i386 libgl-dev:i386 zenity unzip
```
arm64:
```
sudo dpkg --add-architecture armhf
sudo apt update
sudo apt install git make cmake gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf libopenal-dev:armhf libx11-dev:armhf libxrandr-dev:armhf libxinerama-dev:armhf libxcursor-dev:armhf libxi-dev:armhf libgl-dev:armhf zenity unzip
```
x86:
```
sudo apt update
sudo apt install git make cmake gcc g++ libopenal-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl-dev zenity unzip
```
arm:
```
sudo apt update
sudo apt install git make cmake gcc g++ libopenal-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl-dev zenity unzip
```
### ArchLinux
x86_64:
```
sudo pacman -Syu
sudo pacman -S git make cmake gcc gcc-multilib lib32-openal lib32-libx11 lib32-libxrandr lib32-libxinerama lib32-libxcursor lib32-libxi lib32-libglvnd zenity unzip
```
arm:
```
sudo pacman -Syu
sudo pacman -S git make cmake gcc openal libx11 libxrandr libxinerama libxcursor libxi libglvnd zenity unzip
```
### AlpineLinux (Not working)
x86:
```
apk update
apk add git make cmake gcc g++ openal-soft-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev mesa-dev zenity unzip
```

## Compiling
### x86_64 & x86:
```
git clone --recursive http://github.com/MCPI-Revival/Ninecraft.git
cd Ninecraft
make build-i686
```
### arm64 & arm:
```
git clone --recursive http://github.com/MCPI-Revival/Ninecraft.git
cd Ninecraft
make build-arm
```

## Before running for the first time
```
./tools/extract.sh /path/to/your/apk
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

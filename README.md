# Ninecraft

![alt screenshot](https://raw.githubusercontent.com/MCPI-Revival/Ninecraft/master/screenshots/Screenshot%20from%202022-09-10%2000-45-48.png)

## Compile dependencies
### Debian/Ubuntu:
```
git make cmake gcc gcc-multilib g++ zlib1g-dev:i386 libpng-dev:i386 zlib1g-dev libpng-dev libopenal-dev:i386 libopenal-dev libx11-dev:i386 libx11-dev libxrandr-dev:i386 libxrandr-dev libxinerama-dev:i386 libxinerama-dev libxcursor-dev:i386 libxcursor-dev libxi-dev:i386 libxi-dev python3 zenity patchelf
```
### ArchLinux:
```
git make cmake gcc gcc-multilib zlib lib32-zlib libpng lib32-libpng openal lib32-openal libx11 lib32-libx11 libxrandr lib32-libxrandr libxinerama lib32-libxinerama libxcursor lib32-libxcursor libxi lib32-libxi python3 zenity patchelf
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
#include <ninecraft/audio/audio_engine.h>
#include <stdio.h>

extern audio_engine_t audio_engine;
extern void *handle;
extern void *ninecraft_app;

int mod_init() {
    puts("TEST > When the mod loads it will make a pop sound");
    audio_engine_play(&audio_engine, handle, "random.pop", 0, 0, 0, 0.3, 1, 1);
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

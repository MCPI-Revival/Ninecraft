# Ninecraft

![alt screenshot](https://raw.githubusercontent.com/MCPI-Revival/Ninecraft/master/screenshots/Screenshot%20from%202022-09-10%2000-45-48.png)

## Compile dependencies
```
git make cmake gcc gcc-multilib g++ zlib1g-dev:i386 libpng-dev:i386 zlib1g-dev libpng-dev libopenal-dev:i386 libopenal-dev libx11-dev:i386 libx11-dev libxrandr-dev:i386 libxrandr-dev libxinerama-dev:i386 libxinerama-dev libxcursor-dev:i386 libxcursor-dev libxi-dev:i386 libxi-dev python3 zenity
```

## Compiling
```
make
cp ./build/ninecraft-core/ninecraft ninecraft-core
```    

## Before running
### x86:
```
./tools/extract.sh /path/to/your/apk
```
### ARM
```
./tools/extract.sh /path/to/your/apk arm
```
## Running
```
./ninecraft-core
```

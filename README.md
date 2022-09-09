# Ninecraft

![alt screenshot](https://raw.githubusercontent.com/MCPI-Revival/Ninecraft/master/screenshots/Screenshot%20from%202022-09-10%2000-45-48.png)

## Compile dependencies
```
gcc gcc-multilib g++ g++-multilib libxcursor-dev:i386 libxi-dev:i386 libxinerama-dev:i386 libxrandr-dev:i386 libpng-dev:i386 zlib1g-dev:i386 libgl1-mesa-dev:i386 libopenal-dev:i386
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

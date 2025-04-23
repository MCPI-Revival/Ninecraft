# Ninecraft

![alt screenshot](https://raw.githubusercontent.com/MCPI-Revival/Ninecraft/master/screenshots/0.6.1-menu.png)

## Installing compile dependencies
### Microsoft Windows:
To compile Ninecraft on Windows, you'll need either MinGW32, LLVM-MinGW, or the Visual Studio 2022 Build Tools. CMake, Python and Git are also required.
After python is installed you must run `pip install jinja2`
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
### AlpineLinux
x86:
```
apk update
apk add git make cmake gcc g++ openal-soft-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev mesa-dev zenity unzip
```
### Fedora
x86_64:
```
dnf update
dnf install git make cmake gcc g++ glibc-devel.i686 libstdc++-devel.i686 openal-soft-devel.i686 libX11-devel.i686 libXrandr-devel.i686 libXinerama-devel.i686 libXcursor-devel.i686 libXi-devel.i686 libglvnd-devel.i686 zenity unzip
```
x86:
```
dnf update
dnf install git make cmake gcc g++ openal-soft-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel libglvnd-devel zenity unzip
```
arm:
```
dnf update
dnf install git make cmake gcc g++ openal-soft-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel libglvnd-devel zenity unzip
```
## Compiling on windows
### mingw32 & llvm-mingw
```
git clone --recursive http://github.com/MCPI-Revival/Ninecraft.git
cd Ninecraft
.\compile.bat
```
### Visual Studio 2022 build tools
```
git clone --recursive http://github.com/MCPI-Revival/Ninecraft.git
cd Ninecraft
.\compile-msvc.bat
```
## Compiling on linux
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

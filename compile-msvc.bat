@echo off

cd /D "%~dp0"

if not exist build-win32 (
    echo "Created build"
    mkdir build-win32
)
cd build-win32
cmake -G "Visual Studio 17 2022" -A Win32 .. -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build .
cd ..
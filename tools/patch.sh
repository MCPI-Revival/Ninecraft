#!/usr/bin/env bash

if [ -z ${1} ]; then
    echo "Please specify the architecture"
    exit
fi

if [ $1 != "x86" -a $1 != 'armeabi-v7a' ]; then
    echo "The architecture must be x86 or armeabi-v7a"
    exit
fi

echo lib/${1}/libminecraftpe.so

patchelf \
    --remove-needed libandroid.so \
    --remove-needed libc.so \
    --remove-needed libEGL.so \
    --remove-needed liblog.so \
    --remove-needed libm.so \
    --remove-needed libOpenSLES.so \
    --remove-needed libstdc++.so \
    --remove-needed libGLESv1_CM.so \
    --remove-needed libz.so \
    lib/${1}/libminecraftpe.so

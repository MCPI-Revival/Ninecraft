#!/usr/bin/env bash

if [ -z ${1} ]; then
    echo "Please specify the archive"
    exit
fi
if [ ! -f ${1} ]; then
    echo "The specified file doesn't exist!"
    exit
fi
if ! [[ ${1} =~ \.apk$ ]]; then
    echo "The file must be an .apk"
    exit
fi

rm -rf assets/

unzip ${1} "assets/*"

if [[ ${2} = "arm" ]]; then
unzip -p ${1} lib/armeabi-v7a/libminecraftpe.so > libs/arm/libminecraftpe.so
else
unzip -p ${1} lib/x86/libminecraftpe.so > libs/x86/libminecraftpe.so
fi
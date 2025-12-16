#!/bin/sh

# Logging
error() {
    echo "ERROR:" "$@"
    exit 1
}
info() {
    echo "INFO:" "$@"
}

# Check If File Exists
require_file() {
    FILE="$1"
    if [ ! -e "${FILE}" ]; then
        error "Missing File: ${FILE}"
    fi
}

# Detect Architecture
validate_arch() {
    case "${ARCH}" in
        i686)
            PLATFORM='linux/386'
            CONTAINER_PREFIX='i386/'
            ANDROID_ARCH='x86'
            ;;
        arm)
            PLATFORM='linux/arm/v7'
            CONTAINER_PREFIX='arm32v7/'
            ANDROID_ARCH='armeabi-v7a'
            ;;
        *)
            error "Unsupported Architecture: ${ARCH}"
            ;;
    esac
}
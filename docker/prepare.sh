#!/bin/sh

set -e

# Prepare
cd "$(dirname "$0")"
. ./common.sh

# Constants
export VERSION='trixie'

# Arguments
TYPE="$1"
ARCH="$2"
validate_arch
export CONTAINER_PREFIX

# Get Group ID
gid() {
    NAME="$1"
    getent group "${NAME}" | cut -d: -f3
}

# Build
TAG="ninecraft-${TYPE}-${ARCH}"
info "Building Docker Image: ${TAG}..."
cd "${TYPE}"
docker build \
    --tag "${TAG}" \
    --platform "${PLATFORM}" \
    --network host \
    --build-arg VERSION \
    --build-arg CONTAINER_PREFIX \
    --build-arg "USER_ID=$(id -u)" \
    --build-arg "GROUP_ID=$(id -g)" \
    --build-arg "EXTRA_GROUP_IDS=$(gid render) $(gid video) $(gid input)" \
    .

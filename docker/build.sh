#!/bin/sh

set -e

# Prepare
cd "$(dirname "$0")"
. ./common.sh

# Arguments
ARCH="$1"
validate_arch

# Prepare Build Environment
info 'Creating Build Environment...'
./prepare.sh build "${ARCH}"

# Build
info 'Building Ninecraft...'
ROOT="$(cd ../ && pwd)"
DATA='/data'
BUILD="build-docker-${ARCH}"
mkdir -p "${ROOT}/${BUILD}"
docker run \
    --rm \
    --network none \
    --volume "${ROOT}:${DATA}" \
    --workdir "${DATA}/${BUILD}" \
    "ninecraft-build-${ARCH}" \
    sh -c 'cmake -DUSE_SYSTEM_DEPENDENCIES=ON .. && cmake --build .'

# Package
info 'Creating Final Container...'
FILE="${ROOT}/${BUILD}/ninecraft/ninecraft"
require_file "${FILE}"
cp "${FILE}" run
./prepare.sh run "${ARCH}"
info 'Done!'
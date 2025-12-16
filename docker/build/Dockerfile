# syntax=docker/dockerfile:1
# check=error=true;skip=InvalidDefaultArgInFrom

# Base Container
ARG CONTAINER_PREFIX
ARG VERSION
FROM ${CONTAINER_PREFIX}buildpack-deps:${VERSION}

# Install Dependencies
RUN \
    apt-get update && \
    apt-get remove -y make && \
    apt-get install -y --no-install-recommends \
        gcc g++ \
        gdb \
        cmake \
        ninja-build \
        zlib1g-dev \
        libsdl2-dev \
        python3-jinja2 && \
    rm -rf /var/lib/apt/lists/*

# Configure CMake
ENV CMAKE_GENERATOR=Ninja

# Setup User
ARG USER_ID
ARG GROUP_ID
RUN \
    groupadd --non-unique --gid "${GROUP_ID}" main && \
    useradd --non-unique --create-home --uid "${USER_ID}" --gid "${GROUP_ID}" user
USER user

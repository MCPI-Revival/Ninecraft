.DEFAULT_GOAL := build

ARM_BUILD_DIR ?= build-arm/
I686_BUILD_DIR ?= build-i686/

.PHONY: build
build:
	mkdir -p ${ARM_BUILD_DIR}
	cmake -B ${ARM_BUILD_DIR} -DCMAKE_TOOLCHAIN_FILE=./cmake/arm_toolchain.cmake
	cmake --build ${ARM_BUILD_DIR}
	mkdir -p ${I686_BUILD_DIR}
	cmake -B ${I686_BUILD_DIR} -DCMAKE_TOOLCHAIN_FILE=./cmake/i686_toolchain.cmake
	cmake --build ${I686_BUILD_DIR}

.PHONY: clean
clean:
	rm -rf $(ARM_BUILD_DIR)
	rm -rf $(I686_BUILD_DIR)

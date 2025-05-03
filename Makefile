.DEFAULT_GOAL := build

ARM_BUILD_DIR ?= build-arm/
I686_BUILD_DIR ?= build-i686/

.PHONY: build-i686
build-i686:
	mkdir -p ${I686_BUILD_DIR}
	cd ${I686_BUILD_DIR}; cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/i686_toolchain.cmake .. -DCMAKE_POLICY_VERSION_MINIMUM=3.5; make

.PHONY: build-arm
build-arm:
	mkdir -p ${ARM_BUILD_DIR}
	cd ${ARM_BUILD_DIR}; cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/arm_toolchain.cmake .. -DCMAKE_POLICY_VERSION_MINIMUM=3.5; make

.PHONY: build
build: build-arm build-i686

.PHONY: clean
clean:
	rm -rf $(ARM_BUILD_DIR)
	rm -rf $(I686_BUILD_DIR)

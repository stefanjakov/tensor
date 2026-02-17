# --------------------------------------------
# Configuration
# --------------------------------------------
BUILD_DIR := build
BUILD_TYPE := Release
GENERATOR := Ninja

# --------------------------------------------
# Main Targets
# --------------------------------------------
all: configure build

configure:
	cmake -S . -B $(BUILD_DIR) -G "$(GENERATOR)" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build:
	cmake --build $(BUILD_DIR)

run: build
	$(BUILD_DIR)/bin/my_app.exe

test: build
	cd $(BUILD_DIR) && ctest --output-on-failure

clean:
	cmake --build $(BUILD_DIR) --target clean || rmdir /S /Q $(BUILD_DIR)

rebuild: clean all

.PHONY: all configure build run test clean rebuild

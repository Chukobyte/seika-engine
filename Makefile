CC := gcc # C Compiler
CXX := g++ # C++ compiler
I_FLAGS := -I"./include" -I"${SDL2_HOME}/include"
L_FLAGS := -lmingw32 -lSDL2main -lSDL2_mixer -lSDL2 -lfreetype -static-libgcc
C_FLAGS := -w -std=c++14 -Wfatal-errors
LIBRARIES := -L"${SDL2_HOME}/lib" -L"${FREETYPE_HOME}/lib"

PROJECT_NAME := roll_back_engine
BUILD_OBJECT := $(PROJECT_NAME).exe
TEST_BUILD_OBJECT := test_$(PROJECT_NAME).exe

SRC = $(wildcard src/main.cpp src/core/*.cpp src/math/*.cpp src/core/utils/*.cpp src/core/rendering/*.cpp include/stb_image/*.cpp)
SRC_C = $(wildcard lib/glad.c)

OBJ = $(SRC:.cpp=.o)
OBJ_C = $(SRC_C:.c=.o)

TEST_SRC = $(wildcard src/test/*.cpp src/test/unit/*.cpp src/core/*.cpp src/math/*.cpp src/core/utils/*.cpp src/core/rendering/*.cpp include/stb_image/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

EXPORT_PACKAGE_DIR := export_package

# MAIN

.PHONY: all build clean

all: clean format build

%.o: %.cpp
	@echo "Compiling " $< " into " $@
	@$(CXX) -c $(C_FLAGS) $< -o $@ $(I_FLAGS)

%.o: %.c
	@echo "Compiling " $< " into " $@
	@$(CC) -c $(C_FLAGS) $< -o $@ $(I_FLAGS)

build: $(OBJ) $(OBJ_C)
	@echo "Linking " $@
	@$(CXX) -o $(BUILD_OBJECT) $^ $(I_FLAGS) $(L_FLAGS) $(LIBRARIES)

format:
	astyle -n --style=google --recursive src/*.cpp src/*.h

clean:
ifneq ("$(wildcard $(BUILD_OBJECT))","")
	del $(BUILD_OBJECT)
endif
	$(foreach object, $(OBJ) $(OBJ_C), @del $(subst /,\, $(object));)

run:
	./$(BUILD_OBJECT)

package: clean build
ifneq ($(wildcard $(EXPORT_PACKAGE_DIR)/.*),)
	rd /S /Q $(EXPORT_PACKAGE_DIR)
endif
	mkdir $(EXPORT_PACKAGE_DIR)
	copy $(BUILD_OBJECT) $(EXPORT_PACKAGE_DIR)
	copy *.dll $(EXPORT_PACKAGE_DIR)
	copy version.json $(EXPORT_PACKAGE_DIR)
	cd $(EXPORT_PACKAGE_DIR) && echo %cd% && 7z a $(PROJECT_NAME).zip *


# Tests
test: build-test run-test

build-test: $(TEST_OBJ) $(OBJ_C)
	@echo "Linking " $@
	@$(CXX) -o $(TEST_BUILD_OBJECT) $^ $(I_FLAGS) $(L_FLAGS) $(LIBRARIES)

clean-test:
ifneq ("$(wildcard $(TEST_BUILD_OBJECT))","")
	del $(TEST_BUILD_OBJECT)
endif
	$(foreach object, $(TEST_OBJ) $(OBJ_C), @del $(subst /,\, $(object));)

run-test:
	./$(TEST_BUILD_OBJECT) --success

PROJECT_NAME := seika_engine

# OS Specific
ifeq ($(OS),Windows_NT)
    OS_TYPE := windows
    BUILD_OBJECT := $(PROJECT_NAME).exe
    L_FLAGS := -lmingw32 -lSDL2main -lSDL2_mixer -lSDL2 -lpython37 -lfreetype -lOpenAL32 -lwsock32 -lws2_32 -static-libgcc -static-libstdc++ -lstdc++fs
    DELETE_CMD := del
else
    OS_TYPE := linux
    BUILD_OBJECT := $(PROJECT_NAME)
    # TODO: Need to validate linux flags
    L_FLAGS := -lSDL2 -lSDL2_mixer -lGL -lpython3.7m -lfreetype -lcrypt -lpthread -ldl  -lutil -lm -static-libgcc -static-libstdc++
    DELETE_CMD := rm
endif

CC := gcc # C Compiler
CXX := g++ # C++ compiler
I_FLAGS := -I"./include" -I"${SDL2_INCLUDE}" -I"${PYTHON_INCLUDE}" -I"${FREETYPE_INCLUDE}" -I"${OPENAL_INCLUDE}"
C_FLAGS := -Wfatal-errors -Wall -Wextra -Wno-write-strings -Wno-deprecated-declarations -Wno-unused-variable -Wno-cast-function-type -Wno-unused-parameter -Wno-missing-field-initializers
CPP_FLAGS := -std=c++14 $(C_FLAGS) -Wno-reorder
LIBRARIES := -L"${SDL2_LIBS}" -L"${PYTHON_LIBS}" -L"${FREETYPE_LIBS}" -L"${OPENAL_LIBS}"
RELEASE_FLAGS = -DHAVE_SNPRINTF=1

BUILD_OBJECT := $(PROJECT_NAME).exe
TEST_BUILD_OBJECT := test_$(PROJECT_NAME).exe

SRC = $(wildcard src/main.cpp src/core/*.cpp src/core/math/*.cpp src/core/utils/*.cpp src/core/rendering/*.cpp src/core/rendering/shader/*.cpp src/core/input/*.cpp src/core/audio/*.cpp src/core/timer/*.cpp src/core/scripting/python/*.cpp src/core/ecs/*.cpp src/core/networking/*.cpp include/stb_image/*.cpp)
SRC_C = $(wildcard lib/glad.c include/kuba_zip/zip.c)

OBJ = $(SRC:.cpp=.o)
OBJ_C = $(SRC_C:.c=.o)

TEST_SRC = $(wildcard src/test/*.cpp src/test/unit/*.cpp src/core/*.cpp src/core/math/*.cpp src/core/utils/*.cpp src/core/rendering/*.cpp src/core/rendering/shader/*.cpp src/core/input/*.cpp src/core/timer/*.cpp src/core/scripting/python/*.cpp src/core/ecs/*.cpp src/core/networking/*.cpp include/stb_image/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

EXPORT_PACKAGE_DIR := export_package

# MAIN

.PHONY: all build clean

all: clean format build

%.o: %.cpp
	@echo "Compiling " $< " into " $@
	@$(CXX) -c $(CPP_FLAGS) $< -o $@ $(I_FLAGS) $(RELEASE_FLAGS)

%.o: %.c
	@echo "Compiling " $< " into " $@
	@$(CC) -c $(C_FLAGS) $< -o $@ $(I_FLAGS) $(RELEASE_FLAGS)

build: $(OBJ) $(OBJ_C)
	@echo "Linking " $@
	@$(CXX) -o $(BUILD_OBJECT) $^ $(I_FLAGS) $(L_FLAGS) $(LIBRARIES)

# Adds debug symbols for debugger
debug-build: C_FLAGS +=  -g
debug-build: build

format:
	astyle -n --style=google --recursive src/*.cpp src/*.h src/*.hpp

clean:
ifneq ("$(wildcard $(BUILD_OBJECT))","")
	@$(DELETE_CMD) $(BUILD_OBJECT)
endif
ifeq ($(OS_TYPE),windows)
	@$(foreach object, $(OBJ) $(OBJ_C), $(DELETE_CMD) $(subst /,\,$(object));)
else
	@$(foreach object, $(OBJ) $(OBJ_C), $(DELETE_CMD) $(object);)
endif

run:
	./$(BUILD_OBJECT) -l debug -local-assets true

run-2d-test:
	./$(BUILD_OBJECT) -l debug -local-assets false -d assets/game_projects/2d_test/

run-3d-test:
	./$(BUILD_OBJECT) -l debug -local-assets true -d assets/game_projects/3d_test/

full-build: clean format build

package-without-clean:
ifneq ($(wildcard $(EXPORT_PACKAGE_DIR)/.*),)
	rd /S /Q $(EXPORT_PACKAGE_DIR)
endif
	mkdir $(EXPORT_PACKAGE_DIR)
	copy $(BUILD_OBJECT) $(EXPORT_PACKAGE_DIR)
	copy *.dll $(EXPORT_PACKAGE_DIR)
	copy *.zip $(EXPORT_PACKAGE_DIR)
	copy *.json $(EXPORT_PACKAGE_DIR)
	copy *.scfg $(EXPORT_PACKAGE_DIR)
	Xcopy /E /I assets $(EXPORT_PACKAGE_DIR)\assets
	rd /S /Q $(EXPORT_PACKAGE_DIR)\assets\game_projects
	cd $(EXPORT_PACKAGE_DIR) && echo %cd% && 7z a $(PROJECT_NAME).zip *

package: RELEASE_FLAGS +=  -O2
package: clean build package-without-clean

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

clean-and-run-test: clean-test build-test
	./$(TEST_BUILD_OBJECT) --success

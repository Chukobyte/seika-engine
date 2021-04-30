CC := gcc # C Compiler
CXX := g++ # C++ compiler
I_FLAGS := -I"./include"
L_FLAGS := -lmingw32 -static-libgcc
C_FLAGS := -w -std=c++14 -Wfatal-errors
BUILD_OBJECT := roll_back_engine.exe

SRC = $(wildcard src/main.cpp src/core/*.cpp)
OBJ = $(SRC:.cpp=.o)

# MAIN

.PHONY: all build clean

all: clean format build

%.o: %.cpp
	@echo "Compiling " $< " into " $@
	@$(CXX) -c $(C_FLAGS) $< -o $@ $(I_FLAGS)

build: $(OBJ)
	@echo "Linking " $@
	@$(CXX) -o $(BUILD_OBJECT) $^ $(I_FLAGS) $(L_FLAGS)

format:
	astyle -n --style=google --recursive src/*.cpp src/*.h

clean:
ifneq ("$(wildcard $(BUILD_OBJECT))","")
	del $(BUILD_OBJECT)
endif
	$(foreach object, $(OBJ) $(OBJ_C), @del $(subst /,\, $(object));)

run:
	./$(BUILD_OBJECT)

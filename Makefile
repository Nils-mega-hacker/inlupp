# Kataloger och filer
SRC_DIR = src
BUILD_DIR = build/debug
INCLUDE_DIR = include
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play

# Kompilatorflagor
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g -I$(INCLUDE_DIR)

# SDL bibliotek
LIBS = -lSDL3 -lSDL3_image

# Standard mål
all: $(BUILD_DIR)/$(OBJ_NAME)

# Bygg mål
$(BUILD_DIR)/$(OBJ_NAME): $(SRC_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(SRC_FILES) -o $@ $(LIBS)

# Rensa
clean:
	rm -rf build

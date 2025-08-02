CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -fPIC

SRC_DIR := src
INC_DIR := includes
BIN_DIR := build

LIBS := -lnerva
LIB_DIR := /usr/local/lib
INCLUDES := -I$(INC_DIR)

SOURCES := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SOURCES))
TARGET := $(BIN_DIR)/plugin

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -L$(LIB_DIR) $(OBJECTS) -o $@ $(LIBS)

all: $(TARGET)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean

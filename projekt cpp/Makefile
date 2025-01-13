TARGET = main

# compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinc

# catalogs
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

# srcs and objs 
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# default target 
all: $(TARGET)

# main compilation
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# objs compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# all clean
.PHONY: all clean
TARGET = main 

# compilator and flags 
CXX = g++ 
CXXFLAGS = -std=c++17 -Wall -Iinc 

# catalogs
SRC_DIR = src 
INC_DIR = inc

# sources and objects
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# default 
all: $(TARGET)

# compilation 
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

#clean 
clean: 
	rm -f $(OBJS) $(TARGET)

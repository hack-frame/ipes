TARGET = ipes-cpp-server
LIB_NAME = libipes.a
LIB_DIR = lib
SRC_DIR = src
INC_DIR = inc
LIB_INC_DIR = $(LIB_DIR)/inc

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

CC = g++ -std=c++17
CFLAGS = -Wall -Wextra -I$(INC_DIR) -I$(LIB_INC_DIR)

all: $(LIB_DIR)/$(LIB_NAME) $(TARGET)

$(LIB_DIR)/$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

$(TARGET): $(OBJ) $(LIB_DIR)/$(LIB_NAME)
	$(CC) $(OBJ) -o $@ -L$(LIB_DIR) -lipes

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
	$(MAKE) -C $(LIB_DIR) clean

.PHONY: all clean

TARGET = client

SRC_DIR = src
INC_DIR = inc

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean 

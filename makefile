CC = gcc
CFLAGS = -g -Wall
CLIBS = -lm -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lGL 

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

OUTPUT = $(BIN_DIR)/3d

all: 3d

3d: $(OBJ)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ) $(CLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(CLIBS)

clean:
	rm -f $(OBJ_DIR)/*.o $(OUTPUT)


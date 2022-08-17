# -*- Makefile -*

# Compiler options
# Compiler
CC=gcc
# Include
#INCDIRS=-I"Sources/App/Common/" -I"Sources/App/Device/Components/Shell/Utils/" -I"Sources/App/Device/Components/Shell/Middleware/" -I"Sources/App/Device/Components/Shell/Commands/"
# Optimization
OPT=-O0
# Defines
DEFINES= -DTARGET_HOST
# Build flags
CFLAGS= -Wall -g $(INCDIRS) $(OPT) $(DEFINES)

# Direcotory structure
# Where the objects will be stored
OBJ_DIR=Objects
# Where the executable will reside
BIN_DIR=Binaries/Host

# Files used on the build
# The source files
CFILES=Sources/App/main.c
CFILES+= Sources/App/Device/Components/Shell/Commands/shellCommands.c
CFILES+= Sources/App/Device/Components/Shell/Middleware/shell.c
CFILES+= Sources/App/Device/Components/Shell/Utils/shellUtils.c

# Direcotry for the objects
OBJECTS=$(OBJ_DIR)/Sources/App/main.o
OBJECTS+= $(OBJ_DIR)/Sources/App/Device/Components/Shell/Commands/shellCommands.o
OBJECTS+= $(OBJ_DIR)/Sources/App/Device/Components/Shell/Middleware/shell.o
OBJECTS+= $(OBJ_DIR)/Sources/App/Device/Components/Shell/Utils/shellUtils.o

# Directory for the binary executable
BINARY=$(BIN_DIR)/output

all: $(BINARY)

$(BINARY): $(OBJECTS)
	@echo "If the directory ($(@D)) does not exists, create it"
	@mkdir -p $(@D)
	@echo "Make the binary target ($@) based on the dependency ($^)"
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@echo "If the directory ($(@D)) does not exists, create it"
	@mkdir -p $(@D)
	@echo "Create the objects ($@) with the .c files ($^)"
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@echo "Clean the objects and the binary file"
	rm -rf $(BINARY) $(OBJ_DIR)/*

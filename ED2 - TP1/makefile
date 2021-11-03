PROJ_NAME=pesquisa

# .c files
C_src=$(wildcard ./src/*.c)

# .h files
H_src=$(wildcard ./headers/*.h)

# Object files
OBJ=$(subst .c,.o,$(subst src,obj,$(C_src)))

# Compiler and linker
CC=gcc

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wextra    \
         -Wall      

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./obj/%.o: ./src/%.c ./headers/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./obj/main.o: ./src/main.c $(H_src)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p obj

clean:
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
	@ rmdir obj

.PHONY: all clean
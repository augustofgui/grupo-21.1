PROJ_NAME=imobiliaria

# .cpp files
CPP_src=$(wildcard ./src/*.cpp)

# .h files
H_src=$(wildcard ./headers/*.h)

# Object files
OBJ=$(subst .cpp,.o,$(subst src,obj,$(CPP_src)))

# Compiler and linker
CC=g++

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

./obj/%.o: ./src/%.cpp ./headers/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./obj/Main.o: ./src/Main.cpp $(H_src)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p obj

clean:
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
	@ rmdir obj

.PHONY: all clean
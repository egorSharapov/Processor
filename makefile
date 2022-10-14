CFLAGS =    -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations 		\
		  	-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion	\
			-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers 		\
			-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits         \
			-Wwrite-strings -D_EJUDGE_CLIENT_SIDE

CC = g++

OBJ_FOLDER = release/

all: assembler disassembler processor

assembler: $(OBJ_FOLDER)file_analyze.o $(OBJ_FOLDER)assembler.o $(OBJ_FOLDER)main_assembler.o
	$(CC) $^ -o $@


$(OBJ_FOLDER)%.o: assembler/%.cpp
	$(CC) -c  $(CFLAGS) $< -o $@


disassembler: $(OBJ_FOLDER)disassembler.o $(OBJ_FOLDER)main_disassembler.o
	$(CC) $^ -o $@


$(OBJ_FOLDER)%.o: disassembler/%.cpp
	$(CC) -c  $(CFLAGS) $< -o $@



processor: $(OBJ_FOLDER)cpu.o  $(OBJ_FOLDER)main_cpu.o $(OBJ_FOLDER)stack.o $(OBJ_FOLDER)check_stack.o
	$(CC)  $^ -o $@

$(OBJ_FOLDER)%.o: cpu/%.cpp
	$(CC) -c  $(CFLAGS) $< -o $@


$(OBJ_FOLDER)check_stack.o:
	$(CC) -c $(CFLAGS) cpu/stack/check_stack.cpp -DDEBUG -o $@

$(OBJ_FOLDER)stack.o:
	$(CC) -c $(CFLAGS) cpu/stack/stack_functions.cpp -o $@

open:
	$(CC) $(CFLAGS) open.cpp -o $@
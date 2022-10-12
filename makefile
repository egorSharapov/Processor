# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=g++
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS = 	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations 		\
		  	-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion	\
			-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers 		\
			-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits         \
			-Wwrite-strings -D_EJUDGE_CLIENT_SIDE

OBJ_FOLDER = object_files/

assembler: file_analyze.o asm.o main_assembler.o
	$(CC) $(OBJ_FOLDER)file_analyze.o  $(OBJ_FOLDER)asm.o $(OBJ_FOLDER)main_assembler.o -o assembler


asm.o: 
	$(CC) -c $(CFLAGS) assembler/assembler.cpp -o $(OBJ_FOLDER)asm.o

file_analyze.o:
	$(CC) -c $(CFLAGS) assembler/file_analyze.cpp -o $(OBJ_FOLDER)file_analyze.o

main_assembler.o:
	$(CC) -c $(CFLAGS) assembler/main.cpp -o $(OBJ_FOLDER)main_assembler.o



disassembler: disasm.o main_disassembler.o
	$(CC)  $(OBJ_FOLDER)disasm.o $(OBJ_FOLDER)main_disassembler.o -o disassembler


disasm.o: 
	$(CC) -c $(CFLAGS) disassembler/disassembler.cpp -o $(OBJ_FOLDER)disasm.o

main_disassembler.o:
	$(CC) -c $(CFLAGS) disassembler/main.cpp -o $(OBJ_FOLDER)main_disassembler.o

open:
	$(CC) open.cpp -o open
# processor: cpu.o main_cpu.o stack.o:
# 	$(OBJ_FOLDER)cpu.o  $(OBJ_FOLDER)main_cpu.o $(OBJ_FOLDER)stack.o -o processor

# cpu.o:
# 	$(CC) -c $(CFLAGS) cpu/cpu.cpp -o $(OBJ_FOLDER)cpu.o

# main_cpu.o:
# 	$(CC) -c $(CFLAGS) cpu/main.cpp -o $(OBJ_FOLDER)main_cpu.o

# stack.o:
# 	$(CC) -c $(CFLAGS) cpu/stack/stack.cpp cpu/stack/stack_functions.cpp -DNDEBUG -o $(OBJ_FOLDER)stack.o

clean:
	rm -rf *.o $(OBJ_FOLDER)asm
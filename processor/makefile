CXFLAGS = 	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations 		\
		  	-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion	\
			-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op                              		\
			-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits         \
			-Wwrite-strings -D_EJUDGE_CLIENT_SIDE

release:
	g++ $(CXFLAGS) main.cpp cpu.cpp C:\Users\Egor\projects\processor\cpu\stack\stack_functions.cpp C:\Users\Egor\projects\processor\cpu\stack\check_stack.cpp -DNDEBUG -o cpu

debug:
	g++ $(CXFLAGS) main.cpp cpu.cpp C:\Users\Egor\projects\processor\cpu\stack\check_stack.cpp C:\Users\Egor\projects\processor\cpu\stack\stack_functions.cpp -DDEBUG -o cpu


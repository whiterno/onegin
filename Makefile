Headers := comparators/comparators.h file_input_ptrtxt_init/file_input_ptrtxt_init.h file_output/file_output.h sort/sort.h useful/useful.h onegin.h

a.out: obj/main.o obj/comparators.o obj/file_input_ptrtxt_init.o obj/file_output.o obj/sort.o obj/useful.o
	g++ obj/main.o obj/comparators.o obj/file_input_ptrtxt_init.o obj/file_output.o obj/sort.o obj/useful.o

obj/main.o: main.cpp $(Headers)
	g++ -c main.cpp -o obj/main.o

obj/comparators.o: comparators/comparators.cpp $(Headers)
	g++ -c comparators/comparators.cpp -o obj/comparators.o

obj/file_input_ptrtxt_init.o: file_input_ptrtxt_init/file_input_ptrtxt_init.cpp $(Headers)
	g++ -c file_input_ptrtxt_init/file_input_ptrtxt_init.cpp -o obj/file_input_ptrtxt_init.o

obj/file_output.o: file_output/file_output.cpp $(Headers)
	g++ -c file_output/file_output.cpp -o obj/file_output.o

obj/sort.o: sort/sort.cpp $(Headers)
	g++ -c sort/sort.cpp -o obj/sort.o

obj/useful.o: useful/useful.cpp $(Headers)
	g++ -c useful/useful.cpp -o obj/useful.o


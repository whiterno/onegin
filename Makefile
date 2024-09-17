Headers := src/comparators/comparators.h src/file_input_ptrtxt_init/file_input_ptrtxt_init.h src/file_output/file_output.h src/sort/sort.h src/useful/useful.h src/onegin.h

a.out: obj/main.o obj/comparators.o obj/file_input_ptrtxt_init.o obj/file_output.o obj/sort.o obj/useful.o
	g++ obj/main.o obj/comparators.o obj/file_input_ptrtxt_init.o obj/file_output.o obj/sort.o obj/useful.o

obj/main.o: src/main.cpp $(Headers)
	g++ -c src/main.cpp -o obj/main.o

obj/comparators.o: src/comparators/comparators.cpp $(Headers)
	g++ -c src/comparators/comparators.cpp -o obj/comparators.o

obj/file_input_ptrtxt_init.o: src/file_input_ptrtxt_init/file_input_ptrtxt_init.cpp $(Headers)
	g++ -c src/file_input_ptrtxt_init/file_input_ptrtxt_init.cpp -o obj/file_input_ptrtxt_init.o

obj/file_output.o: src/file_output/file_output.cpp $(Headers)
	g++ -c src/file_output/file_output.cpp -o obj/file_output.o

obj/sort.o: src/sort/sort.cpp $(Headers)
	g++ -c src/sort/sort.cpp -o obj/sort.o

obj/useful.o: src/useful/useful.cpp $(Headers)
	g++ -c src/useful/useful.cpp -o obj/useful.o


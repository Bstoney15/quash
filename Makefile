make:
	gcc src/execute.c -o bin/quash -I ./header

run:
	gcc src/execute.c -o bin/quash -I ./header
	./bin/quash
v: 
	gcc src/execute.c -o bin/quash -I ./header
	valgrind ./bin/quash
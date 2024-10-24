make:
	gcc src/execute.c -o bin/quash -I ./header

run:
	gcc src/execute.c -o bin/quash -I ./header
	./bin/quash
v: 
	gcc src/execute.c -o bin/quash -I ./header
	valgrind valgrind --leak-check=full --track-origins=yes ./bin/quash

g:
	gcc src/execute.c -o bin/quash -I ./header
	gdb ./bin/quash

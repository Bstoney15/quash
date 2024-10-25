make:
	gcc src/execute.c -o quash -I ./header

test:
	gcc src/execute.c -o quash -I ./header
	./quash
v: 
	gcc src/execute.c -o quash -I ./header
	valgrind valgrind --leak-check=full --track-origins=yes ./quash
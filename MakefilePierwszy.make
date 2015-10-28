all: hello
hello: hello.o
	@echo "buduje..."
	qcc hello.o -o hello
hello.o: hello.c
	@echo "kompiluje..."
	qcc -Wall -c hello.c
clean:
	@echo "usuwam..."
	rm -f hello hello.o

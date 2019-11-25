CC=qcc
CFLAGS=-Wall
LFLAGS=-lm
SRC=hello.c
OBJS=hello.o
BINS=hello

all: $(BINS)
$(BINS): $(OBJS)
	@echo "buduje..."
	$(CC) $(LFLAGS) $^ -o $@
$(OBJS): $(SRC)
	@echo "kompiluje..."
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	@echo "usuwam..."
	rm -f $(OBJS) $(BINS)
.PHONY: all clean

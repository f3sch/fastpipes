OBJS	= write.o read.o
SOURCE	= write.c read.c
HEADER	= common.h
OUT	= write read
CC	 = gcc
FLAGS	 = -c -Wall -O3
LFLAGS	 = -O3
# -g option enables debugging mode
# -c flag generates object code for separate files


all: $(OUT)

# create/compile the individual files >>separately<<
write: write.o
	$(CC) $< -o $@ $(LFLAGS)

write.o: write.c
	$(CC) $(FLAGS) write.c -std=c11

read: read.o
	$(CC) $< -o $@ $(LFLAGS)

read.o: read.c
	$(CC) $(FLAGS) read.c -std=c11

fizzbuzz: fizzbuzz.S
	$(CC) -mavx2 -c fizzbuzz.S
	ld -o $@ fizzbuzz.o


# clean house
clean:
	rm -f $(OBJS) $(OUT) fizzbuzz.o fizzbuzz perf.data perf.data.old

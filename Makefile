OBJ = 6.o mylib.o
CFLAGS = -Wall -std=c99 -pedantic
BINARY = 6
all: $(BINARY)

$(BINARY): $(OBJ)
gcc $(CFLAGS) $(OBJ) -o $(BINARY)

%.o : %.c
gcc $(CFLAGS) -c $<

clean:
rm $(BINARY) $(OBJ)

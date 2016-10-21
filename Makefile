CC          = gcc
EXEC        = prog
CFLAGS      = -Wall -Wextra -lm -std=c99 -DDEBUG
LIBFLAGS    = `pkg-config --cflags --libs gtk+-2.0` 

SOURCES     = $(wildcard src/*.c)
OBJS        = $(SOURCES:.c=.o)


all : $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(CFLAGS) $(LIBFLAGS)

src/%.o : src/%.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean :
	rm -f $(OBJS)
	rm -f $(EXEC)


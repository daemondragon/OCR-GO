CC          = gcc
EXEC        = prog
CFLAGS      = -Wall -Wextra -lm -std=c99 -DDEBUG -g
LIBFLAGS    = `pkg-config gtk+-2.0 --cflags --libs`

SOURCES     = $(wildcard src/*.c)
OBJS        = $(SOURCES:.c=.o)


all : $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(CFLAGS) $(LIBFLAGS)

src/%.o : src/%.c
	$(CC) $< -c -o $@ $(CFLAGS) $(LIBFLAGS)

clean :
	rm -f $(OBJS)
	rm -f $(EXEC)
c :
	rm -f $(OBJS)
	rm -f $(EXEC)

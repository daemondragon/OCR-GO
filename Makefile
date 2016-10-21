CC          = gcc
EXEC        = prog
CFLAGS      = -Wall -Wextra -lm -std=c99 -DDEBUG
LIBFLAGS    = 'gtk-config --cflags --libs'

SOURCES     = $(wildcard src/*.c)
OBJS        = $(SOURCES:.c=.o)


all : $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(CFLAGS) $(LIBFLAGS)

src/%.o : src/%.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean :
	rm -f $(OBJS)

mrproper : clean
	rm -f $(EXEC)
	

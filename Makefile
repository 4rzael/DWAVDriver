NAME = touch

CFLAGS += -O2

LDFLAGS += -lm -lX11

all:
	gcc *.c -o $(NAME) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re
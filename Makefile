NAME_CORE = touchDriver

NAME_CALIBRATION = calibrate

MAIN_CORE = touch.c

MAIN_CALIBRATION = calibrate.c

CFLAGS += -O2

LDFLAGS += -lm -lX11

SRC =	input.c \
		mouseHandler.c \
		utils.c \
		XInterfaces.c

all: calibration core

core:
	gcc $(MAIN_CORE) $(SRC) -o $(NAME_CORE) $(CFLAGS) $(LDFLAGS)

calibration:
	gcc $(MAIN_CALIBRATION) $(SRC) -o $(NAME_CALIBRATION) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re

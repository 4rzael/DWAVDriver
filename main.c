#include "touch.h"

// Read the command line and start the driver
int main(int ac, char **av)
{
	t_context sys;
	int touchFile;

	memset(&sys, 0, sizeof(sys));

	// Init X11
	sys.display = XOpenDisplay(NULL);
	if (!sys.display)
	{
		fprintf(stderr, "Cannot open display\n");
		exit(EXIT_FAILURE);
	}
	sys.root = DefaultRootWindow(sys.display);
	XSelectInput(sys.display, sys.root, KeyReleaseMask);

	// Read the command line
	if (ac <= 2) {
		sys.screen.X = T_RES;
		sys.screen.Y = T_RES;
	}
	else {
		sys.screen.X = atoi(av[1]);
		sys.screen.X = sys.screen.X > 0 ? sys.screen.X : 1;
		sys.screen.Y = atoi(av[2]);
		sys.screen.Y = sys.screen.Y > 0 ? sys.screen.Y : 1;
	}

	// Open the touchscreen file. Retry every 10 seconds
	while ((touchFile = open("/dev/usb/hiddev0", O_RDONLY)) <= 0)
	{
		perror("open()");
		sleep(10);
	}

	printf("Screen file opened\n");

	listenInput(&sys, touchFile, &onInput);
}

// Listen for the touch screen
void listenInput(t_context *sys, int touchFile,
				void (*callback)(t_context *))
{
	t_touchInput input;

	memset(&input, 0, sizeof(input));

	while (read(touchFile, &input, sizeof(input)) > -1)
	{
		if (!checkInput(&input)) {
			fprintf(stderr, "error in input\n");
			int i;
			for (i = 0; i < sizeof(input); i++)
			{
				printf("%hhx%c%c", ((char *)(&input))[i],
				                   (i && i % 2 == 0) ? ' ' : '\0',
				                   (i && i % 16 == 0) ? '\n' : '\0');
			}
		}
		else 
		{
			sys->mouse.X = posInScreen(&(input.pointX), sys->screen.X, T_RES);
			sys->mouse.Y = posInScreen(&(input.pointY), sys->screen.Y, T_RES);
			sys->isPressed = input.point.field2;

			callback(sys);
			// One-frame memory
			sys->lastMouse = sys->mouse;
			sys->wasPressed = sys->isPressed;
		}
	}
}

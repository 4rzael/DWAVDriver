#include "touch.h"

#define CALIBRATION_TIME 250

void calibrator(t_context *sys)
{
	static int duration = 0;
	static int minX = INT_MAX - 1;
	static int minY = INT_MAX - 1;
	static int maxX = 0;
	static int maxY = 0;
	int fd;
	char toWrite[128];

	memset(toWrite, 0, sizeof(toWrite));

	if (sys->isPressed)
	{
		minX = (sys->mouse.X <= minX) ? sys->mouse.X : minX;
		minY = (sys->mouse.Y <= minY) ? sys->mouse.Y : minY;
		maxX = (sys->mouse.X >= maxX) ? sys->mouse.X : maxX;
		maxY = (sys->mouse.Y >= maxY) ? sys->mouse.Y : maxY;
	}

	if (duration >= CALIBRATION_TIME)
	{
		printf("calibration done\n");
		printf("saving the results\n");

		if ((fd =
				open("./.calibration",
					O_RDWR | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) <= 0)
			exit(EXIT_FAILURE);

		sprintf(toWrite, "%d\n%d\n%d\n%d\n", minX, minY, maxX, maxY);

		printf("toWrite : \n%s\n", toWrite);

		if (write(fd, toWrite, strlen(toWrite)) == -1)
			exit(EXIT_FAILURE);

		close(fd);
		exit(EXIT_SUCCESS);
	}

	printf("%d/%d\n", duration, CALIBRATION_TIME);

	++duration;
}

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

	sys.screen = Vector2(T_RES,T_RES);

	// Open the touchscreen file. Retry every 10 seconds
	while ((touchFile = open("/dev/usb/hiddev0", O_RDONLY)) <= 0)
	{
		perror("open()");
		sleep(10);
	}

	printf("calibration\n");
	printf("Slide your finger on the 4 edges (and corners) of the screen\n");

	listenInput(&sys, touchFile, &calibrator);
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
			sys->mouse.X =
				(input.pointX.field1 * 255 + input.pointX.field2)
				* sys->screen.X / T_RES;
			sys->mouse.Y =
				(input.pointY.field1 * 255 + input.pointY.field2)
				* sys->screen.Y / T_RES;

			sys->isPressed = input.point.field2;

			callback(sys);
			// One-frame memory
			sys->lastMouse = sys->mouse;
			sys->wasPressed = sys->isPressed;
		}
	}
}

#include "touch.h"

int checkInput(const t_touchInput * const in)
{
	int i;

	// magic numbers
	for (i = 0; i < 11; i++)
	{
		if (((t_touchLine *)(in))[i].magic1 != 0x008C0003)
			return 0;
		if (((t_touchLine *)(in))[i].magic2 != 0x008C0003)
			return 0;
	}

	// pressed, point and multitouch
	if (in->point.field1 != 0x000000AA)
		return 0;
	if (in->multitouch[0].field1 != 0x000000BB)
		return 0;
	if (in->point.field2 & ~1)
		return 0;

	return 1;
}

void printInput(const t_touchInput * const in, t_vec2 screen)
{
	int posX = (in->pointX.field1 * 255 + in->pointX.field2) * screen.X / T_RES;
	int posY = (in->pointY.field1 * 255 + in->pointY.field2) * screen.Y / T_RES;

	posX = posX < screen.X ? posX : screen.X;
	posY = posY < screen.Y ? posY : screen.Y;

	printf("pressed ? %s\n", in->point.field2 ? "yes" : "no");
	printf("posX : %d\n", posX);
	printf("posY : %d\n", posY);
}

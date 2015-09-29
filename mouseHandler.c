#include "touch.h"

void onInput(t_context *sys)
{
	static int isLeftClicked = 0;
	static int isRightClicked = 0;
	// These two are the coords of the point when the user touched the screen
	static int originalPosX = 0;
	static int originalPosY = 0;
	static int timeSinceLastChange = 0;

	// On release
	if (!sys->isPressed)
	{
		isLeftClicked = 0;
		isRightClicked = 0;
		mouseUnclick(sys, Button1);
		mouseUnclick(sys, Button2);
	}

	// On enter
	if (sys->isPressed && !sys->wasPressed)
	{
		originalPosX = sys->mouse.X;
		originalPosY = sys->mouse.Y;
		timeSinceLastChange = 0;
	}

	// If didn't move too much
	if (distance(Vector2(originalPosX, originalPosY), sys->mouse) <=
			CLICK_PRECISION) 
	{

		if (timeSinceLastChange > RIGHT_CLICK_TIME)
		{
			if (!isRightClicked) {
				mouseUnclick(sys, Button1);
				mouseClick(sys, Button3); // Right click
			}

			isRightClicked = 1;
		}
		else if (timeSinceLastChange > LEFT_CLICK_TIME)
		{
			if (!isLeftClicked) {
				mouseClick(sys, Button3); // Left click
			}

			isLeftClicked = 1;
		}

		++timeSinceLastChange;
	}
	// Moved too much, cannot click until release + enter
	else
	{
		originalPosX = -(CLICK_PRECISION + 1);
		originalPosY = -(CLICK_PRECISION + 1);
	}

	// Position refresh
	if (sys->isPressed && distance(sys->lastMouse, sys->mouse) >=
			MOVE_PRECISION)
		mouseMove(sys, sys->mouse);
}
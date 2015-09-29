#include "touch.h"

int calibrated(int min, int max, int number)
{
	return (number - min) * (float)((float)(T_RES) / (float)(max - min));
}

t_vec2 posInScreen(t_context *sys, t_touchInput *input)
{
	return Vector2(
		calibrated(
			sys->calibration_Min.X,
			sys->calibration_Max.X,
			input->pointX.field1 * 255 + input->pointX.field2)
		* sys->screen.X / T_RES,
		
		calibrated(
			sys->calibration_Min.Y,
			sys->calibration_Max.Y,
			input->pointY.field1 * 255 + input->pointY.field2)
		* sys->screen.Y / T_RES		
		);
}

inline int distance(t_vec2 p1, t_vec2 p2)
{
	return (int)(sqrt(pow(p2.X - p1.X, 2) + pow(p2.Y - p1.Y, 2)));
}

t_vec2 Vector2(int x, int y)
{
	t_vec2 v;

	v.X = x;
	v.Y = y;
	return v;
}
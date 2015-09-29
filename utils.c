#include "touch.h"

inline int posInScreen(t_touchLine *line, int screenSize, int touchRes)
{
	return (line->field1 * 255 + line->field2) * screenSize / touchRes;
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
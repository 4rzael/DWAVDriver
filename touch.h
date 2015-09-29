/*
** 
** TOUCHSCREEN HEX FORMAT :
** 
** 0300 8c00 aa00 0000 3000 8C00 AA00 0000
** 0300 8c00 BB00 0000 3000 8C00 CC00 0000
** 0300 8c00 DD00 0000 3000 8C00 EE00 0000
** 
** 0300 8c00 bb00 0000 0300 8c00 0000 0000
** 0300 8c00 0000 0000 0300 8c00 0000 0000
** 0300 8c00 0000 0000 0300 8c00 0000 0000
** 0300 8c00 0000 0000 0300 8c00 0000 0000
** 0300 8c00 0000 0000 0300 8c00 0000 0000
** 0300 8c00 0000 0000 0300 8c00 0000 0000
** 0300 8c00 0000 0000 0300 8c00 0000 0000
** 0300 8c00 0000 0000 0300 8c00 0000 0000
** 
** 
** AA: PRESSED
** 
** BB: POSX
** CC: OFFSETX
** 
** DD: POSY
** EE: OFFSETY
*/

#ifndef TOUCH_H_
# define TOUCH_H_

# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

# include <X11/Xlib.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>

# define T_RES (0x0F * 0xFF)

# define MOVE_PRECISION 5
# define CLICK_PRECISION 30
# define RIGHT_CLICK_TIME 50
# define LEFT_CLICK_TIME 5

struct s_touchLine 
{
	uint32_t magic1;
	uint32_t field1;
	uint32_t magic2;
	uint32_t field2;
} __attribute__((__packed__));

typedef struct s_touchLine t_touchLine;

struct s_touchInput {
	t_touchLine point;
	t_touchLine pointX;
	t_touchLine pointY;

	t_touchLine multitouch[8];

} __attribute__((__packed__));

typedef struct s_touchInput t_touchInput;

typedef struct s_vec2
{
	int X;
	int Y;
} t_vec2;

typedef struct s_context
{
	t_vec2 screen;
	// touch screen
	t_vec2 mouse;
	t_vec2 lastMouse;
	int isPressed;
	int wasPressed;
	// X11
	Window root;
	Display *display;
	XEvent event;
} t_context;



// utils.c
inline int posInScreen(t_touchLine *, int, int);
inline int distance(t_vec2, t_vec2);

// main.c
void listenInput(t_context *, int, void (*)(t_context *));

// input.c
int checkInput(const t_touchInput * const);
void printInput(const t_touchInput * const, t_vec2);
t_vec2 Vector2(int, int);

// mouseHandler.c
void onInput(t_context *);

// XInterfaces.c
void mouseMove(t_context *, t_vec2);
void mouseLeftClick(t_context *);
void mouseRightClick(t_context *);
void mouseClick(t_context *, int);
void mouseUnclick(t_context *, int);

#endif /* TOUCH_H_ */

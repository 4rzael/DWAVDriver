#include "touch.h"

void mouseClick(t_context *sys, int button)
{
    memset(&(sys->event), 0x00, sizeof((sys->event)));

    (sys->event).type = ButtonPress;
    (sys->event).xbutton.button = button;
    (sys->event).xbutton.same_screen = True;

    XQueryPointer(sys->display,
    			  RootWindow(sys->display,
    			  DefaultScreen(sys->display)),
    			  &(sys->event).xbutton.root,
    			  &(sys->event).xbutton.window,
    			  &(sys->event).xbutton.x_root,
    			  &(sys->event).xbutton.y_root,
    			  &(sys->event).xbutton.x,
    			  &(sys->event).xbutton.y,
    			  &(sys->event).xbutton.state);

    (sys->event).xbutton.subwindow = (sys->event).xbutton.window;

    while ((sys->event).xbutton.subwindow)
    {
        (sys->event).xbutton.window = (sys->event).xbutton.subwindow;

        XQueryPointer(sys->display,
        			  (sys->event).xbutton.window,
        			  &(sys->event).xbutton.root,
        			  &(sys->event).xbutton.subwindow,
        			  &(sys->event).xbutton.x_root,
        			  &(sys->event).xbutton.y_root,
        			  &(sys->event).xbutton.x,
        			  &(sys->event).xbutton.y,
        			  &(sys->event).xbutton.state);
    }

    if (XSendEvent(sys->display, PointerWindow, True, 0xfff, &(sys->event)) == 0)
    	fprintf(stderr, "Error\n");

    XFlush(sys->display);
}

void mouseUnclick(t_context *sys, int button)
{
    memset(&(sys->event), 0x00, sizeof((sys->event)));

    (sys->event).type = ButtonRelease;
    (sys->event).xbutton.button = button;
    (sys->event).xbutton.same_screen = True;
    (sys->event).xbutton.state = 0x100;

    XQueryPointer(sys->display,
    			  RootWindow(sys->display,
    			  DefaultScreen(sys->display)),
    			  &(sys->event).xbutton.root,
    			  &(sys->event).xbutton.window,
    			  &(sys->event).xbutton.x_root,
    			  &(sys->event).xbutton.y_root,
    			  &(sys->event).xbutton.x,
    			  &(sys->event).xbutton.y,
    			  &(sys->event).xbutton.state);

    (sys->event).xbutton.subwindow = (sys->event).xbutton.window;

    while ((sys->event).xbutton.subwindow)
    {
        (sys->event).xbutton.window = (sys->event).xbutton.subwindow;

        XQueryPointer(sys->display,
        			  (sys->event).xbutton.window,
        			  &(sys->event).xbutton.root,
        			  &(sys->event).xbutton.subwindow,
        			  &(sys->event).xbutton.x_root,
        			  &(sys->event).xbutton.y_root,
        			  &(sys->event).xbutton.x,
        			  &(sys->event).xbutton.y,
        			  &(sys->event).xbutton.state);
    }

    if(XSendEvent(sys->display, PointerWindow, True, 0xfff, &(sys->event)) == 0)
    	fprintf(stderr, "Error\n");

    XFlush(sys->display);
}

void mouseMove(t_context *sys, t_vec2 pos)
{
	XWarpPointer(sys->display, sys->root, sys->root, 0, 0, 0, 0, pos.X, pos.Y);
	XSync(sys->display, False);
}
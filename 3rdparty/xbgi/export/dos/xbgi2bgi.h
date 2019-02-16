/*
 * Event looper for Borland Graphics Interface on dos < xbgi2bgi.h >
 *
 * Absorption of differences between BGI and enhanced functions in xbgi
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#ifndef _XBGI2BGI_H_
#define _XBGI2BGI_H_
#include <dos.h>
#include <graphics.h>

/*
 * low level functions for key events
 */
static unsigned char _KEY_BUFFER = 0;
static int _kbhit(void)
{
  if (_KEY_BUFFER == 0)
    _KEY_BUFFER = (unsigned char)bdos(0x06, 0xff, 0);
  return (int)_KEY_BUFFER;
}
static int _getch(void)
{
  unsigned char ch;
  
  while (_kbhit() == 0)
    ;
  ch = _KEY_BUFFER;
  _KEY_BUFFER = 0;
  return (int)ch;
}
static int _ungetch(int ch)
{
  if (_KEY_BUFFER)
    return -1;
  _KEY_BUFFER = (unsigned char)ch;
  _KEY_BUFFER = 0;
  return (int)_KEY_BUFFER;
}

/*
 * low level functions for mouse events
 */
static int _STD_MOUSE = 0; /* 0: NEC's mouse.sys, !0: standard mouse.com */
static int _initmouse(void)
{
  union REGS regs;
  int ret;

  regs.x.ax = 0x00;
  int86(0x33, &regs, &regs);
  ret = regs.x.ax;
  
  regs.x.ax = 0x03;
  int86(0x33, &regs, &regs);
  _STD_MOUSE = (regs.x.ax == 0x03); /* mouse.com keeps ax */
  
  return ret;
}
static void _showmousecursor(void)
{
  union REGS regs;
  int i, c;

  regs.x.ax = 0x2A;
  int86(0x33, &regs, &regs);
  c = regs.x.ax;
  for (i=0; i<c; i++) {
    regs.x.ax = 0x01;
    int86(0x33, &regs, &regs);
  }
}
static void _hidemousecursor(void)
{
  union REGS regs;

  regs.x.ax = 0x02;
  int86(0x33, &regs, &regs);
}
static void _closemouse(void)
{
  union REGS regs;

  regs.x.ax = 0x0c;
  regs.x.cx = 0;
  int86(0x33, &regs, &regs);
}
#define MOUSE_MOTION    (1U<<0)
#define BUTTON1_PRESS   (1U<<1)
#define BUTTON1_RELEASE (1U<<2)
#define BUTTON2_PRESS   (1U<<3)
#define BUTTON2_RELEASE (1U<<4)
#define BUTTON3_PRESS   (1U<<5)
#define BUTTON3_RELEASE (1U<<6)
#define BUTTON_PRESS    (BUTTON1_PRESS|BUTTON2_PRESS)
#define BUTTON_RELEASE  (BUTTON1_RELEASE|BUTTON2_RELEASE)
#define MOUSE_EVENT     (MOUSE_MOTION|BUTTON_PRESS|BUTTON_RELEASE)
static void _registermousehandler(unsigned int mask, void (huge *proc)(void))
{
  union REGS regs;
  struct SREGS sregs;

  regs.x.ax = 0x0c;
  regs.x.cx = mask;
  if (mask != 0) {
    sregs.es = FP_SEG(proc);
    regs.x.dx = FP_OFF(proc);
  }
  else {
    sregs.es = 0;
    regs.x.dx = 0;
  }
  int86x(0x33, &regs, &regs, &sregs);
}

/*
 * event definition for event driven procedure
 */
#define MotionNotify  (1U<<0)
#define ButtonPress   (1U<<1)
#define ButtonRelease (1U<<2)
#define KeyPress      (1U<<3)

#define Button1Mask (1U<<0)
#define Button2Mask (1U<<1)
#define Button3Mask (1U<<2)

struct _xmotion {
  int type;
  int state;
  int x, y;
};

struct _xbutton {
  int type;
  int button;
  int x, y;
};

struct _xkey {
  int type;
  int key;
  int x, y;
};

typedef union _XEvent {
  int type;
  struct _xmotion xmotion;
  struct _xbutton xbutton;
  struct _xkey    xkey;
} XEvent;

#define maxXBGIevent 5
static int nXBGIevent = 0, iXBGIevent = 0;
static XEvent XBGIevents[maxXBGIevent];

/*
 * low level functions for event definition
 */
static int _sendevent(XEvent *ev)
{
  if (nXBGIevent >= maxXBGIevent)
    return 0;
  else {
    XBGIevents[(iXBGIevent+nXBGIevent)%maxXBGIevent] = *ev;
    nXBGIevent++;
  }
  return !0;
}
static int _eventsqueued(void)
{
  XEvent ev;

  if (_kbhit()) {
    ev.type = KeyPress;
    ev.xkey.key = _getch();
    _sendevent(&ev);
  }
  return nXBGIevent;
}
static void _nextevent(XEvent *ev)
{
  while (!_eventsqueued())
    ;
  *ev = XBGIevents[iXBGIevent];
  nXBGIevent--;
  iXBGIevent = (iXBGIevent+1)%maxXBGIevent;
}

static int BGI_key_press(int c)
{
  if (c == 'q' || c == 'Q' || c == 0x1b)
    return 0;
  return !0;
}
static int (*_button_press)  (int b, int x, int y) = NULL;
static int (*_button_release)(int b, int x, int y) = NULL;
static int (*_mouse_motion)  (int b, int x, int y) = NULL;
static int (*_key_press)     (int c)               = BGI_key_press;
static int (*_noevent)       (void)                = NULL;
static void set_button_press_handler(int (*proc)(int b, int x, int y))
{
  _button_press = proc;
}
static void set_button_release_handler(int (*proc)(int b, int x, int y))
{
  _button_release = proc;
}
static void set_mouse_motion_handler(int (*proc)(int b, int x, int y))
{
  _mouse_motion = proc;
}
static void set_key_press_handler(int (*proc)(int c))
{
  _key_press = proc;
}
#define set_page_enter_handler(proc) {;}
#define set_page_leave_handler(proc) {;}
#define set_configure_handler(proc) {;}
#define set_expose_handler(proc) {;}
static void set_noevent_handler(int (*proc)(void))
{
  _noevent = proc;
}

static void xbgiloop(void)
{
  XEvent ev;
  int ok_mouse = 0, mask = 0, ret;
  void huge _xbgimousehandler(void);

  if (_mouse_motion || _button_press || _button_release) {
    ok_mouse = _initmouse();
    mask |= (_mouse_motion)?MOUSE_MOTION:0;
    mask |= (_button_press)?BUTTON_PRESS:0;
    mask |= (_button_release)?BUTTON_RELEASE:0;
  }
  if (ok_mouse) {
    _showmousecursor();
    _registermousehandler(mask, _xbgimousehandler);
  }

  ret = !0;
  while (!0) {
    if (_eventsqueued() > 0) {
      _nextevent(&ev);
      switch (ev.type) {
      case ButtonPress:
        if (ok_mouse)
	  _hidemousecursor();
        ret = _button_press(ev.xbutton.button, ev.xbutton.x, ev.xbutton.y);
        if (ok_mouse)
	  _showmousecursor();
        break;
      case ButtonRelease:
        if (ok_mouse)
	  _hidemousecursor();
        ret = _button_release(ev.xbutton.button, ev.xbutton.x, ev.xbutton.y);
        if (ok_mouse)
	  _showmousecursor();
        break;
      case MotionNotify:
        if (ok_mouse)
	  _hidemousecursor();
        ret = _mouse_motion(ev.xmotion.state, ev.xbutton.x, ev.xbutton.y);
        if (ok_mouse)
	  _showmousecursor();
        break;
      case KeyPress:
        if (_key_press) {
          if (ok_mouse)
	    _hidemousecursor();
          ret = _key_press(ev.xkey.key);
          if (ok_mouse)
	    _showmousecursor();
        }
        break;
      }
    }
    else {
      if (_noevent) {
        if (ok_mouse)
	  _hidemousecursor();
        ret = _noevent();
        if (ok_mouse)
	  _showmousecursor();
      }
    }
    if (!ret) {
      if (ok_mouse) {
        _registermousehandler(0, NULL);
        _hidemousecursor();
        _closemouse();
      }
      break;
    }
  }
}

void xflush(void)
{
  ;
}
void xsync(void)
{
#ifdef PC98
  disable();
  while (inp(0x02AB)&32)
    ;
  enable();
#else
  disable();
  while (!(inp(0x03DA)&8))
    ;
  enable();
#endif
}
#define settitle(title) {;}
#define seticonname(name) {;}
#define seticon(filename) {;}
#define setmaxx(x) {;}
#define setmaxy(y) {;}
static void getsizexy(int *xsize, int *ysize)
{
  *xsize = getmaxx() + 1;
  *ysize = getmaxy() + 1;
}
#define setsizexy(xsize, ysize) {;}
#define getgeometry(x, y, width, height) {;}
#define setgeometry(x, y, width, height) {;}
#define setmaxcolor(c) {;}
#define setbackingstore(flg) {;}
static int graphnumber(void) { return 0; }
#define selectgraph(id) {;}
#define termgraph(id) closegraph()
#define savemonographtofile(filename,option) 0
#define savegraphtofile(filename,option) 0
#define saveexposetofile(filename,option) 0

#pragma saveregs
void huge _xbgimousehandler(void)
{
  XEvent ev;

  ev.xbutton.x = _CX;
  ev.xbutton.y = _DX;
  if (_AX&MOUSE_MOTION) {
    ev.type = MotionNotify;
    if (_STD_MOUSE)
      ev.xmotion.state = _BX;
    else
      ev.xmotion.state = (_AX==0)?0:Button1Mask|(_BX==0)?0:Button2Mask;
  }
  else if (_AX&BUTTON_PRESS) {
    ev.type = ButtonPress;
    ev.xbutton.button = (_BX&Button1Mask)?1:(_BX&Button2Mask)?2:3;
  }
  else if (_AX&BUTTON_RELEASE) {
    ev.type = ButtonRelease;
    ev.xbutton.button = (_AX&BUTTON1_RELEASE)?1:(_AX&BUTTON2_RELEASE)?2:3;
  }
  _sendevent(&ev);
}

#undef MOUSE_MOTION
#undef BUTTON1_PRESS
#undef BUTTON1_RELEASE
#undef BUTTON2_PRESS
#undef BUTTON2_RELEASE
#undef BUTTON3_PRESS
#undef BUTTON3_RELEASE
#undef BUTTON_PRESS
#undef BUTTON_RELEASE
#undef MOUSE_EVENT

#endif

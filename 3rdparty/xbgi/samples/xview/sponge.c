/*
 * Sample program with xbgi and XView < sponge.c >
 *
 * Example of xbgi with X tool kit
 *
 * Copyright (C) 1992-1994,1995 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/file.h>
#include <ctype.h>
#include <X11/Xlib.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/tty.h>
#include <xview/termsw.h>
#include <xview/textsw.h>
#include <xview/scrollbar.h>
#include <xview/notice.h>
#include <xview/cms.h>
#include <graphics.h>
#include <graphix.h>
#include <x11.h>
#include <graphp3_.h>
#include "sponge.h"

void XVBGI_driver()
{
  extern xbgi *XBGI;
  extern xbgi_procedures X11_XBGI_PROCEDURES;
  XSetWindowAttributes att;

  *XBGI->inherit_procedures = X11_XBGI_PROCEDURES;
  XBGI->inherit_members = malloc(sizeof(x11_xbgi));
  XBGIDisplay = (Display*)xv_get(BasePanel,XV_DISPLAY);
  XBGIScreen = DefaultScreen(XBGIDisplay);
  XBGIVisual = DefaultVisual(XBGIDisplay, XBGIScreen); /* since version 3.01 */
  XBGIDepth = DefaultDepth(XBGIDisplay, XBGIScreen); /* since version 3.01 */
  XBGIColormap = DefaultColormap(XBGIDisplay, XBGIScreen);
  XBGI->ncolor = 16;
  XBGI->color = 15;
  XBGI->palette.size = (unsigned char)(XBGI->ncolor-1);
  XBGI->bkcolor = 0;
  XBGI->npage = 1;
  XBGI->apage = 0;
  XBGI->vpage = 0;
  XBGI->l10n = !0;
  XBGI->colornames = 0;
  XBGIRoot = XCreateSimpleWindow(XBGIDisplay,
				 RootWindow(XBGIDisplay,XBGIScreen),
				 0, 0, 200, 200, 0,
				 WhitePixel(XBGIDisplay,XBGIScreen),
				 BlackPixel(XBGIDisplay,XBGIScreen));
  XSelectInput(XBGIDisplay, XBGIRoot, ExposureMask|StructureNotifyMask);
  XBGIWins = (Window*)malloc(XBGI->npage*sizeof(Window));
  XBGIWins[0] = XCreateSimpleWindow(XBGIDisplay, XBGIRoot, 0, 0,
                                     200, 200, 0,
                                     WhitePixel(XBGIDisplay,XBGIScreen),
                                     BlackPixel(XBGIDisplay,XBGIScreen));
  att.backing_store = Always;
  XChangeWindowAttributes(XBGIDisplay, XBGIWins[0], CWBackingStore, &att);
  XBGIDrawGC  = XCreateGC(XBGIDisplay, XBGIRoot, 0, NULL);
  XBGIFillGC  = XCreateGC(XBGIDisplay, XBGIRoot, 0, NULL);
  XBGIPixelGC = XCreateGC(XBGIDisplay, XBGIRoot, 0, NULL);
  XBGIImageGC = XCreateGC(XBGIDisplay, XBGIRoot, 0, NULL);

  detectgraph(&(XBGI->gdriver), &(XBGI->gmode));
  setgraphmode(XBGI->gmode);
  graphdefaults();
  
  XMapWindow(XBGIDisplay, XBGIRoot);
  XMapSubwindows(XBGIDisplay, XBGIRoot); 
  XFlush(XBGIDisplay);
  XBGI->gerror = grOk;
}

void sponge(n, x, y, z, l)
int n;
double x, y, z, l;
{
  int i, j, k;
  int c[6];

  if (n < 0)
    return;
  c[0] = c[2] = c[4] = (10+n)%16, c[1] = c[3] = c[5] = (10+n)%16 - 8;
  boxp3_(x+l/6, y+l/6, z+l/6, x-l/6, y-l/6, z-l/6, c);
  for (i=-1; i<2; i+=1)
    for (j=-1; j<2; j+=1)
      for (k=-1; k<2; k+=1)
        if (i!=0 || j!=0 || k!=0)
          sponge(n-1, x+l/3*i, y+l/3*j, z+l/3*k, l/3);
}

double x = 0, y = 0, z = 0, l = 1;
int n = 1, ROTX = -15, ROTY = 10, ROTZ = 0;
double SX = 0.0, SY = 0.0;
double DST = 0.2;

void do_drawing()
{
  int gd = DETECT, gm;
  static int first = !0;

  if (first) {
    registerbgidriver(XVBGI_driver);
    initgraph(&gd, &gm, "-geometry 200x200+200+200");
    first = 0;
  }
  setviewport_(0, 0, getmaxx(), getmaxy(), !0);
  setwindow_(-1.0-SX, 1.0-SY, 1.0-SX, -1.0-SY);
  setrotationport_(-1, -1, -1, 1, 1, 1);
  setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ));
  setdistance_(DST);
  cleardevice();
  sponge(n, x, y, z, l);
  xflush();
}

int main(argc,argv)
int argc;
char *argv[];
{
  int gd = DETECT, gm;

  xv_init(XV_INIT_ARGC_PTR_ARGV,&argc,argv,
#ifdef JLE
          XV_USE_LOCALE, TRUE,
          /******XV_LC_DISPLAY_LANG, "japanese",
            XV_LC_INPUT_LANG, "japanese",******/
#endif
          NULL);
  
  image_pr_1=xv_create(NULL,SERVER_IMAGE,
     XV_WIDTH,16,XV_HEIGHT,16,
     SERVER_IMAGE_DEPTH,1,
     SERVER_IMAGE_BITS,image_src_1,
  NULL);
  image_pr_2=xv_create(NULL,SERVER_IMAGE,
     XV_WIDTH,16,XV_HEIGHT,16,
     SERVER_IMAGE_DEPTH,1,
     SERVER_IMAGE_BITS,image_src_2,
  NULL);
  image_pr_3=xv_create(NULL,SERVER_IMAGE,
     XV_WIDTH,16,XV_HEIGHT,16,
     SERVER_IMAGE_DEPTH,1,
     SERVER_IMAGE_BITS,image_src_3,
  NULL);
  image_pr_4=xv_create(NULL,SERVER_IMAGE,
     XV_WIDTH,16,XV_HEIGHT,16,
     SERVER_IMAGE_DEPTH,1,
     SERVER_IMAGE_BITS,image_src_4,
  NULL);
  BaseFrame = xv_create(NULL,FRAME,
     XV_SHOW,TRUE,
     FRAME_LABEL,"New Frame",
     FRAME_NO_CONFIRM,TRUE,
     XV_X,610,
     XV_Y,160,
     XV_WIDTH,200,
     XV_HEIGHT,200,
  0);
  BasePanel = xv_create(BaseFrame,PANEL,
     XV_X,0,
     XV_Y,0,
     XV_WIDTH,200,
     XV_HEIGHT,200,
  0);
  Button_Left = xv_create(BasePanel,PANEL_BUTTON,
     PANEL_NOTIFY_PROC,Button_Left_Proc,
     PANEL_LABEL_X,90,
     PANEL_LABEL_Y,130,
     PANEL_VALUE_X,136,
     PANEL_VALUE_Y,130,
     PANEL_LABEL_IMAGE,image_pr_3,
  0);
  Button_Right = xv_create(BasePanel,PANEL_BUTTON,
     PANEL_NOTIFY_PROC,Button_Right_Proc,
     PANEL_LABEL_X,150,
     PANEL_LABEL_Y,130,
     PANEL_VALUE_X,196,
     PANEL_VALUE_Y,130,
     PANEL_LABEL_IMAGE,image_pr_4,
  0);
  Button_Up = xv_create(BasePanel,PANEL_BUTTON,
     PANEL_NOTIFY_PROC,Button_Up_Proc,
     PANEL_LABEL_X,120,
     PANEL_LABEL_Y,100,
     PANEL_VALUE_X,166,
     PANEL_VALUE_Y,100,
     PANEL_LABEL_IMAGE,image_pr_1,
  0);
  Button_Down = xv_create(BasePanel,PANEL_BUTTON,
     PANEL_NOTIFY_PROC,Button_Down_Proc,
     PANEL_LABEL_X,120,
     PANEL_LABEL_Y,160,
     PANEL_VALUE_X,166,
     PANEL_VALUE_Y,160,
     PANEL_LABEL_IMAGE,image_pr_2,
  0);
  Button_Quit = xv_create(BasePanel,PANEL_BUTTON,
     PANEL_NOTIFY_PROC,Button_Quit_Proc,
     PANEL_LABEL_X,140,
     PANEL_LABEL_Y,10,
     PANEL_VALUE_X,198,
     PANEL_VALUE_Y,10,
     PANEL_LABEL_STRING,"Quit",
  0);
  Button_Fore = xv_create(BasePanel,PANEL_BUTTON,
     PANEL_NOTIFY_PROC,Button_Fore_Proc,
     PANEL_LABEL_X,10,
     PANEL_LABEL_Y,130,
     PANEL_VALUE_X,68,
     PANEL_VALUE_Y,130,
     PANEL_LABEL_STRING,"Fore",
  0);
  Button_Back = xv_create(BasePanel,PANEL_BUTTON,
     PANEL_NOTIFY_PROC,Button_Back_Proc,
     PANEL_LABEL_X,10,
     PANEL_LABEL_Y,160,
     PANEL_VALUE_X,68,
     PANEL_VALUE_Y,160,
     PANEL_LABEL_STRING,"Back",
  0);
  Button_Draw = xv_create(BasePanel,PANEL_BUTTON,
     PANEL_NOTIFY_PROC,Button_Draw_Proc,
     PANEL_LABEL_X,10,
     PANEL_LABEL_Y,10,
     PANEL_VALUE_X,68,
     PANEL_VALUE_Y,10,
     PANEL_LABEL_STRING,"Draw",
  0);
  window_fit(BaseFrame);

  ok_to_notify=TRUE;
  
  xv_main_loop(BASE_FRAME);
  return 0;
}

int Button_Left_Proc(item,event)
Panel_item item;
Event *event;
{
  ROTY += 5; ROTY = (ROTY+360)%360;
  do_drawing();
  auto_connect(item,event);
}

int Button_Right_Proc(item,event)
Panel_item item;
Event *event;
{
  ROTY -= 5; ROTY = (ROTY+360)%360;
  do_drawing();
  auto_connect(item,event);
}

int Button_Up_Proc(item,event)
Panel_item item;
Event *event;
{
  ROTX += 5; ROTX = (ROTX+360)%360;
  do_drawing();
  auto_connect(item,event);
}

int Button_Down_Proc(item,event)
Panel_item item;
Event *event;
{
  ROTX -= 5; ROTX = (ROTX+360)%360;
  do_drawing();
  auto_connect(item,event);
}

int Button_Quit_Proc(item,event)
Panel_item item;
Event *event;
{
  auto_connect(item,event);
  exit(0);
}

int Button_Fore_Proc(item,event)
Panel_item item;
Event *event;
{
  DST *= 0.9;
  do_drawing();
  auto_connect(item,event);
}

int Button_Back_Proc(item,event)
Panel_item item;
Event *event;
{
  DST *= 1.1;
  do_drawing();
  auto_connect(item,event);
}

int Button_Draw_Proc(item,event)
Panel_item item;
Event *event;
{
  do_drawing();
  auto_connect(item,event);
}

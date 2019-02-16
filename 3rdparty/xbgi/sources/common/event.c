/*
 * Source File < common/event.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * event looper for simple event programing
 */
void xbgiloop( void )
{
  XBGI->inherit_procedures->xbgiloop();
}
/*
 * is event
 */
int isevent( void )
{
  return XBGI->inherit_procedures->isevent();
}

/*
 * following functions are customizing of xbgiloop
 */
void set_button_press_handler( int (*proc)( int b, int x, int y ) )
{
  XBGI->inherit_procedures->button_press_handler = proc;
}
void set_button_release_handler( int (*proc)( int b, int x, int y ) )
{
  XBGI->inherit_procedures->button_release_handler = proc;
}
void set_mouse_motion_handler( int (*proc)( int b, int x, int y ) )
{
  XBGI->inherit_procedures->mouse_motion_handler = proc;
}
void set_page_enter_handler( int (*proc)( int p ) )
{
  XBGI->inherit_procedures->page_enter_handler = proc;
}
void set_page_leave_handler( int (*proc)( int p ) )
{
  XBGI->inherit_procedures->page_leave_handler = proc;
}
void set_key_press_handler( int (*proc)( int c ) )
{
  XBGI->inherit_procedures->key_press_handler = proc;
}
void set_configure_handler( int (*proc)( void ) )
{
  XBGI->inherit_procedures->configure_handler = proc;
}
void set_expose_handler( int (*proc)( void ) )
{
  XBGI->inherit_procedures->expose_handler = proc;
}
void set_noevent_handler( int (*proc)( void ) )
{
  XBGI->inherit_procedures->noevent_handler = proc;
}






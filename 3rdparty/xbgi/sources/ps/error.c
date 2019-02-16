/*
 * Source File < ps/error.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions of error messenger
 */
int graphresult( void )
{
  return XBGI->gerror;
}
char *grapherrormsg( int errorcode )
{
  static char *errormsgs[] = {
    "Graphic: Ok                 ",
    "Graphic: No Init Graph      ",
    "Graphic: Not Detected       ",
    "Graphic: File Not Found     ",
    "Graphic: Invalid Driver     ",
    "Graphic: No Load Memory     ",
    "Graphic: No Scan Memory     ",
    "Graphic: No Flood Memory    ",
    "Graphic: Font Not Found     ",
    "Graphic: No Font Memory     ",
    "Graphic: Invalid Mode       ",
    "Graphic: Error              ",
    "Graphic: IO error           ",
    "Graphic: Invalid Font       ",
    "Graphic: Invalid Font Number",
    "Graphic: No Entry Error Code",
    "Graphic: No Entry Error Code",
    "Graphic: No Entry Error Code",
    "Graphic: Invalid Version    ",
  };
  
  switch ( errorcode ){
    case grOk            :
    case grNoInitGraph   :
    case grNotDetected   :
    case grFileNotFound  :
    case grInvalidDriver :
    case grNoLoadMem     :
    case grNoScanMem     :
    case grNoFloodMem    :
    case grFontNotFound  :
    case grNoFontMem     :
    case grInvalidMode   :
    case grError         :
    case grIOerror       :
    case grInvalidFont   :
    case grInvalidFontNum:
    case grInvalidVersion:
    return errormsgs[-errorcode];
  }
  return NULL;
}









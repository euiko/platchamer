/*
 * Private Include File < common/common_p.h >
 *
 * Macros and Definitions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _COMMON_P_H_
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dos.h"
#include "coniox.h"
#include "conio.h"
#include "graphix.h"
#include "graphics.h"
#include "bgiutl.h"

#ifndef XBGI_DEFAULT_DRIVER
#define x11_driver
#endif

/*
 * the header of XBGI to stack
 */
extern xbgi *XBGIS;

/*
 * the current XBGI
 */
extern xbgi *XBGI;

/*
 * the current XBGI driver
 */
extern void (*XBGI_CURRENT_DRIVER)( void );

/*
 * the various macros and definitions
 */
#define minmax(a,x,b) ((((a)<=(x))&&((x)<=(b)))?(x):(((x)<(a))?(a):(b)))

#define eprintf(fp,fmt,err) do{ fprintf(fp,fmt,err); exit( 1 ); }while(0)

#define FatalError(err)     eprintf(stderr,"XBGI: fatal error: %s.\n",err)
#define Warning(err)        fprintf(stderr,"XBGI: warning: %s.\n",err)
#define ReservedFuture(err) fprintf(stderr,"XBGI: reserved future: %s.\n",err)
#define NotSupported(err)   fprintf(stderr,"XBGI: not supported: %s.\n",err)
#define Notice(msg)         fprintf(stderr,"XBGI: notice: %s.\n",msg)

#endif /* _COMMON_P_H_ */






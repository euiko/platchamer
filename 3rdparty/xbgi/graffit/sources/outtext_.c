/*
 * Text drawing service in graffit library < outtext_.c >
 *
 * Outtext Function with Format for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdarg.h>
#include <graffit.h>

#define hr __HR
#define sg __SG

void outtextxyf_(double x, double y, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(wvx(x), wvy(y), str);
  va_end(argptr);
}
void outtextxyprintf_(double x, double y, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(wvx(x), wvy(y), str);
  va_end(argptr);
}

void outtextxyfl2_(double x, double y, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(lxtox(wvx(x)), lytoy(wvy(y)), str);
  va_end(argptr);
}
void outtextxyprintfl2_(double x, double y, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(lxtox(wvx(x)), lytoy(wvy(y)), str);
  va_end(argptr);
}

void outtextxyflx_(double x, double y, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(lxtox(wvx(x)), wvy(y), str);
  va_end(argptr);
}
void outtextxyprintflx_(double x, double y, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(lxtox(wvx(x)), wvy(y), str);
  va_end(argptr);
}

void outtextxyfly_(double x, double y, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(wvx(x), lytoy(wvy(y)), str);
  va_end(argptr);
}
void outtextxyprintfly_(double x, double y, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(wvx(x), lytoy(wvy(y)), str);
  va_end(argptr);
}

void outtextxyfr3_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(wvx(r3tox(x,y,z)), wvy(r3toy(x,y,z)), str);
  va_end(argptr);
}
void outtextxyprintfr3_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(wvx(r3tox(x,y,z)), wvy(r3toy(x,y,z)), str);
  va_end(argptr);
}

void outtextxyfp3_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(wvx(p3tox(x,y,z)), wvy(p3toy(x,y,z)), str);
  va_end(argptr);
}
void outtextxyprintfp3_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(wvx(p3tox(x,y,z)), wvy(p3toy(x,y,z)), str);
  va_end(argptr);
}

void outtextxyfsl_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(wvx(sltox(x,y,z)), wvy(sltoy(x,y,z)), str);
  va_end(argptr);
}
void outtextxyprintfsl_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(wvx(sltox(x,y,z)), wvy(sltoy(x,y,z)), str);
  va_end(argptr);
}

void outtextxyfsr_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(wvx(srtox(x,y,z)), wvy(srtoy(x,y,z)), str);
  va_end(argptr);
}
void outtextxyprintfsr_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(wvx(srtox(x,y,z)), wvy(srtoy(x,y,z)), str);
  va_end(argptr);
}

void outtextxyfs3_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  sg.start();
  sg.left();
  outtextxy(wvx(sltox(x,y,z)), wvy(sltoy(x,y,z)), str);
  sg.right();
  outtextxy(wvx(srtox(x,y,z)), wvy(srtoy(x,y,z)), str);
  sg.end();
  va_end(argptr);
}
void outtextxyprintfs3_(double x, double y, double z, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  sg.start();
  sg.left();
  outtextxyprintf(wvx(sltox(x,y,z)), wvy(sltoy(x,y,z)), str);
  sg.right();
  outtextxyprintf(wvx(srtox(x,y,z)), wvy(srtoy(x,y,z)), str);
  sg.end();
  va_end(argptr);
}

void outtextxyfrn_(double *x, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  rntov(x, hr.x);
  outtextxy(wvx(r3tox(hr.x[0],hr.x[1],hr.x[2])),
	    wvy(r3toy(hr.x[0],hr.x[1],hr.x[2])), str);
  va_end(argptr);
}
void outtextxyprintfrn_(double *x, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxyprintf(wvx(r3tox(hr.x[0],hr.x[1],hr.x[2])),
		  wvy(r3toy(hr.x[0],hr.x[1],hr.x[2])), str);
  va_end(argptr);
}

void outtextxyfpn_(double *x, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  rntov(x, hr.x);
  outtextxy(wvx(p3tox(hr.x[0],hr.x[1],hr.x[2])),
	    wvy(p3toy(hr.x[0],hr.x[1],hr.x[2])), str);
  va_end(argptr);
}
void outtextxyprintfpn_(double *x, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  rntov(x, hr.x);
  outtextxyprintf(wvx(p3tox(hr.x[0],hr.x[1],hr.x[2])),
		  wvy(p3toy(hr.x[0],hr.x[1],hr.x[2])), str);
  va_end(argptr);
}

void outtextxyfsn_(double *x, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  sg.start();
  sg.left();
  outtextxy(wvx(sltox(hr.x[0],hr.x[1],hr.x[2])),
	    wvy(sltoy(hr.x[0],hr.x[1],hr.x[2])), str);
  sg.right();
  outtextxy(wvx(srtox(hr.x[0],hr.x[1],hr.x[2])),
	    wvy(srtoy(hr.x[0],hr.x[1],hr.x[2])), str);
  sg.end();
  va_end(argptr);
}
void outtextxyprintfsn_(double *x, char *form, ...)
{
  va_list argptr;
  char str[1024];
  
  va_start(argptr, form);
  vsprintf(str, form, argptr);
  sg.start();
  sg.left();
  outtextxyprintf(wvx(sltox(hr.x[0],hr.x[1],hr.x[2])),
		  wvy(sltoy(hr.x[0],hr.x[1],hr.x[2])), str);
  sg.right();
  outtextxyprintf(wvx(srtox(hr.x[0],hr.x[1],hr.x[2])),
		  wvy(srtoy(hr.x[0],hr.x[1],hr.x[2])), str);
  sg.end();
  va_end(argptr);
}

#undef hr
#undef sg

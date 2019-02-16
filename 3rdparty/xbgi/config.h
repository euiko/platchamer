/*
 * Configuration file for Imakefiles < config.h >
 *
 * Borland Graphics Interface libraries for X11, PostScript
 *
 * Copyright (C) 1992-1994,1995 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */

/*
 * All C programs are written in ANSI-C,
 * so it is difficult to build by old C compiler.
 * If you do nothing here, the compiler which compiled X is used.
 */
CC = gcc
/*CXX = g++*/

/*
 * If you are not super user, please define InstallHome.
 */
/*#define InstallHome*/

#ifdef InstallHome
#define IncSubdir xbgi
LOCALDIR = $(HOME)/bin
LOCALINC = $(HOME)/include
LOCALLIB = $(HOME)/lib
LOCALMAN = $(HOME)/man/man3
INSTINCFLAGS = -m 0644
INSTMANFLAGS = -m 0644
XBGIBINDIR = $(LOCALDIR)
XBGIINCDIR = Concat($(LOCALINC)/,IncSubdir)
XBGILIBDIR = $(LOCALLIB)
XBGIMANDIR = $(LOCALMAN)
#else
#define IncSubdir xbgi
XBGIBINDIR = $(BINDIR)
XBGIINCDIR = Concat($(INCDIR)/,IncSubdir)
XBGILIBDIR = $(USRLIBDIR)
XBGIMANDIR = $(MANDIR)
#endif

XBGILIBREV = 3.02

/*
 * If you have no Xpm library, please uncomment.
 * Xpm library is used in xbgiloop() and savegraphtofile().
 */
#define EnableXpmlib

#ifdef EnableXpmlib
XPMLIB_DEFINE = -DENABLE_XPMLIB
XPMLIB = -lXpm
#else
XPMLIB_DEFINE = /**/
XPMLIB = /**/
#endif

/*
 * If you don't want to draw text in bi-lingual or multi-lingual,
 * please don't define both EnableBilingual and EnableMultilingual.
 * Bi-lingual method supports only japanese in this present version.
 * Multi-lingual method uses X11R5-6's XmbDrawText.
 * If your system works on i18n (internationalization),
 * please define EnableMultilingual.
 */
#define EnableBilingual japanese
/*#define EnableMultilingual*/

#if defined(EnableBilingual) && defined(EnableMultilingual)
#undef EnableBilingual
#endif
#ifdef EnableBilingual
LINGUAL_DEFINE = -DENABLE_BILINGUAL=EnableBilingual
#endif
#ifdef EnableMultilingual
LINGUAL_DEFINE = -DENABLE_MULTILINGUAL
#endif

/*
 * If you want to build concatenated library which links all graphic devices,
 * please define BuildConcatenatedLib.
 * If you want to build stand-alone libraries which work each graphic device,
 * please define BuildStandaloneLibs.
 * This version can not allow con-currently building both concatenated library
 * and stand-alone libraries.
 */
#define BuildConcatenatedLib
/*#define BuildStandaloneLibs*/

#if defined(BuildConcatenatedLib) && defined(BuildStandaloneLibs)
#undef BuildStandaloneLibs
#endif
#if defined(BuildConcatenatedLib)
GRAFFITLIB = -lgraffit
XBGILIB = -lxbgi
#endif

/*
 * If you defined BuildConcatenatedLib mentioned above,
 * you must determine concatenated drivers by CONCATENATED_DRIVERS and
 * select a default driver in CONCATENATED_DRIVERS.
 */
#if defined(BuildConcatenatedLib)
CONCATENATED_DRIVERS = x11 ps
DefaultDriver = x11
DRIVER_DEFINE = -DXBGI_DEFAULT_DRIVER=$(DefaultDriver)_driver
#endif

/*
 * If you defined BuildStandaloneLibs mentioned above,
 * you must determine stand-alone libraries by BUILD_STANDALONE_LIBS and
 * hasten to select a default stand-alone library in BUILD_STANDALONE_LIBS.
 * The selected default stand-alone library is only used in sample makefiles
 * to compile your xbgi programs, automatically generated in samples/mkfiles.
 */
#if defined(BuildStandaloneLibs)
BUILD_STANDALONE_LIBS = x11 ps
DefaultStandaloneLib = x11
#endif

#if defined(BuildStandaloneLibs)
GRAFFITLIB = -lgraffit
XBGILIB = -lxbgi_common -lxbgi_$(DefaultStandaloneLib) -lxbgi_misc
#endif

/*
 * This definition is used in building concatenated library,
 * depending upon SharedLibraryTarget in X11/config/<os>Library.rule.
 */
#if (ProjectX < 6)
#define DownDir shared
#define UnsharedDownDir .
#define SharedDownDir DownDir
#else /* (ProjectX < 6) */
#define DownDir unshared
#define UnsharedDownDir DownDir
#define SharedDownDir .
#endif /* (ProjectX < 6) */

/*
 * If your system has shared library, you can use libxbgi*.so* libgraffit.so*.
 * Your lib/X11/config/* has to support the method of building shared library.
 */
#ifndef DoSharedLib
#define DoSharedLib (HasSharedLibraries && \
		     !defined(cygwinArchitecture) && \
		     !(defined(SGIArchitecture) && !SystemV4))
#endif
#ifndef DoNormalLib
#define DoNormalLib YES
#endif

/*
 * Normally, you don't have to edit below.
 */
DEFINES = -Wall $(LINGUAL_DEFINE) $(XPMLIB_DEFINE) $(DRIVER_DEFINE)
#ifdef InstallHome
EXTRA_LOAD_FLAGS = -lm -L$(XBGILIBDIR) -L$(USRLIBDIR)
#else
EXTRA_LOAD_FLAGS = -lm -L$(XBGILIBDIR)
#endif
LOCAL_LIBRARIES = $(GRAFFITLIB) $(XBGILIB) $(XTOOLLIB) $(XPMLIB) $(XLIB)

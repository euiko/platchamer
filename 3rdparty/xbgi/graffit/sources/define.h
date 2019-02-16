GRAFFIT_HEADERS =\
 coloring.h\
 graphr2_.h\
 gturtle_.h\
 graphl2_.h\
 outtext.h\
 outtext_.h\
 axes.h\
 axes_.h\
 axisutil.h\
 graffit.h\
 graphr3_.h\
 graphp3_.h\
 graphs3_.h\
 graphrn_.h\
 graphpn_.h\
 graphsn_.h\
 grafplot.h\
 intext.h
/* gsave.h\*/ /* it's unsupported since version 3.02 */
GRAFFIT_SRCS =\
 coloring.c\
 graphr2_.c\
 gturtle_.c\
 graphl2_.c\
 outtext.c \
 outtext_.c\
 axes.c\
 axes_.c\
 axisutil.c\
 graphr3_.c\
 graphp3_.c\
 graphs3_.c\
 graphrn_.c\
 graphpn_.c\
 graphsn_.c\
 grafplot.c\
 intext.c
/* gsave.c\*/ /* it's unsupported since version 3.02 */
GRAFFIT_OBJS = $(GRAFFIT_SRCS:.c=.o)

COMMON_HEADERS =\
 bgiutl.h\
 conio.h\
 coniox.h\
 graphics.h\
 graphix.h
COMMON_SRCS =\
 misc.c\
 bgiutl.c\
 graphix.c\
 graphics.c\
 event.c\
 request.c\
 config.c\
 driver.c\
 init.c\
 id.c\
 util.c\
 error.c\
 page.c\
 viewport.c\
 lineinfo.c\
 writeops.c\
 move.c\
 line.c\
 rect.c\
 poly.c\
 arcinfo.c\
 arc.c\
 fillinfo.c\
 fillrect.c\
 fillpoly.c\
 fillarc.c\
 flood.c\
 pixel.c\
 image.c\
 point.c\
 textinfo.c\
 text.c\
 color.c\
 palette.c\
 coniox.c\
 conio.c\
 getch.c\
 kbhit.c
COMMON_OBJS = $(COMMON_SRCS:.c=.o)


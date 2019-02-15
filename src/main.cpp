extern "C" {
    #include <graphics.h>
}
#include <iostream>

int main(void)
{
    /* request autodetection */
    int gdriver = DETECT, gmode = X11_WXGA, errorcode;
    int midx, midy, radius = 100;
    initwindow(1366, 768);
    errorcode = graphresult();
    if (errorcode != grOk) {   /* an error occurred */
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        exit(1);               /* terminate with an error code */
    }

    int i = 5;
    midx = 0;
    midy = getmaxy() / 2;

    setcolor(getmaxcolor());
    while(!kbhit()) {
        cleardevice();
        midx += i;
        circle(midx, midy, radius);
        delay(15);
    }
    closegraph();
    return 0;
}
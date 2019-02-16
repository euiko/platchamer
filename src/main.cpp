extern "C" {
    #include <common/graphix.h>
    #include <misc/dos.h>
}
#include <iostream>
#include "libs/stb_image.h"
#include <x11/x11.h> 
#include <X11/X.h> 
#include <vector> 


int main(void)
{
    /* request autodetection */
    int gd = DETECT, gm, errorcode;
    int midx, midy, radius = 100;
    
    xbgi* XBGI = creategraph(&gd, &gm, "-geometry 1366x768 -direct-color");
    int width, height, channels, channelCount = STBI_rgb_alpha;
    unsigned char* raw = stbi_load("logo.png", &width, &height, &channels, channelCount);
    if(raw == NULL)
    {
        std::cout << "Image cannot be opened";
        return 1;
    }
    
    // std::vector<unsigned char> image;
    // image.assign(raw, raw+(width*height*4));
    
    // uint32_t bitmap[width*height];
    // int pixelIndex = 0;
    // for(int x = 0; x < width; x++) {
    //     for(int y = 0; y < height; y++) {
    //         unsigned char* pixelOffset = image + (x + height * y) * channelCount;
    //         unsigned char r = pixelOffset[0];
    //         unsigned char g = pixelOffset[1];
    //         unsigned char b = pixelOffset[2];
    //         unsigned char a = channelCount >= 4 ? pixelOffset[3] : 0xff;
    //         // unsigned char a = 0x00;
    //         uint32_t color = (((a << 24) + (r << 16)) + (g << 8)) + b;
    //         bitmap[pixelIndex++] = color;
    //         // bgi::putpixel( 100 + x, 100 + y, color);
    //     }
    // }

    // int max = DefaultDepthOfScreen(DefaultScreenOfDisplay(dpy));

    // Display* d = XBGIDisplay;
    // Visual* v = XBGIVisual;
    // bgi_image img;
    // img.height = height;
    // img.width = width;
    // Pixmap pix = XCreatePixmap(dpy, drawable, 16, 16, 24);
    XImage* img = XCreateImage(XBGIDisplay, CopyFromParent, 24, ZPixmap, 0, (char*) raw, width, height, 32, width*4);
    // img.pixmap = pix;
    // image.insert(image.begin(), height);
    // image.insert(image.begin(), width);
    // setcolor(getmaxcolor());
    int x = 10; int i = 1;
    while(!kbhit()) {
        cleardevice();
        XPutImage(XBGIDisplay, XBGIWins[XBGI->apage], DefaultGC(XBGIDisplay, XBGIScreen), img, 0,0,0,0, width, height);
        x+= (i * 5);
        if(x > getmaxx() || x < 0)
            i *= -1;
        delay(15);
    }

    XDestroyImage( img );

    // XFreePixmap(dpy, img.pixmap);

    closegraph();
    return 0;
}
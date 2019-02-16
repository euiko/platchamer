extern "C" {
    #include <graphics.h>
}
#include <iostream>
// #include "utils/stb_image.h"
#include <X11/bitmaps/xlogo16> 

int main(void)
{
    /* request autodetection */
    int gd = DETECT, gm, errorcode;
    int midx, midy, radius = 100;
    
    initgraph(&gd, &gm, "-geometry 400x400");


    // int width, height, channels, channelCount = utils::STBI_rgb_alpha;
    // unsigned char* image = utils::stbi_load("player_01.png", &width, &height, &channels, channelCount);
    // if(image == NULL)
    // {
    //     std::cout << "Image cannot be opened";
    //     return 1;
    // }
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

    // bgi_image img;
    // img.height = height;
    // img.width = width;
    // Pixmap pix = XCreatePixmap(dpy, drawable, 16, 16, 24);
    // XImage* image = XCreateImage(dpy, CopyFromParent, 24, ZPixmap, 0, (char*) image,);
    // img.pixmap = pix;

    // setcolor(getmaxcolor());
    // while(!kbhit()) {
    //     cleardevice();
    //     putimage(50, 50, (void*)&img, COPY_PUT);
    //     delay(15);
    // }
    // XFreePixmap(dpy, img.pixmap);

    closegraph();
    return 0;
}
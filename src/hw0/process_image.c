#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    x = MAX(0, MIN(im.w-1, x));
    y = MAX(0, MIN(im.h-1, y));
    c = MAX(0, MIN(im.c-1, c));

    int index = ( im.w * im.h * c ) + y * im.w + x;
    return im.data[index];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if ( x > im.w-1 || y > im.h-1 || c > im.c-1 ) { return; }

    int index = ( im.w * im.h * c ) + y * im.w + x;
    im.data[index] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    copy.w = im.w;
    copy.h = im.h;
    copy.c = im.c;
    for (int i=0; i<im.w*im.h*im.c; i+=1 ) {
        copy.data[i] = im.data[i];
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);

    int i,j;
    for(j = 0; j < im.h; ++j){
        for(i = 0; i < im.w; ++i){
            float R = im.data[ i + im.w*j + im.w*im.h*0 ];
            float G = im.data[ i + im.w*j + im.w*im.h*1 ];
            float B = im.data[ i + im.w*j + im.w*im.h*2 ];
            gray.data[i + gray.w*j] = 0.299 * R + 0.587 * G + .114 * B;

        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{   /**
    Function: shift all colors in channel c by value v
    Args:
        im: strut contains images shape(weight, height, and channels)(im.w, im.h, im,c) and image pixels (im.data)
        v: float refers to the shifted pixel value
    */
    int i,j;
    for(j = 0; j < im.h; ++j){
        for(i = 0; i < im.w; ++i){
            int index = ( im.w * im.h * c ) + j * im.w + i;
            im.data[index] += v;
        }
    }

}

float clamp_float(float a, float min, float max)
{
    if ( a > max ) return max;
    if ( a < min ) return min;
    return a;
}

void clamp_image(image im)
{
    /*
    make sure image values are between 0 and 1
    */
    for (int i=0; i<im.w*im.h*im.c; i+=1 ) {
        im.data[i] = clamp_float(im.data[i], 0, 1);
    }

}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    int i,j;
    float R,G,B, V,m,C,S,Hdash,H;
    for(j = 0; j < im.h; ++j){
        for(i = 0; i < im.w; ++i){

            R = get_pixel(im, i, j, 0);
            G = get_pixel(im, i, j, 1);
            B = get_pixel(im, i, j, 2);

            V = three_way_max(R,G,B);

            m = three_way_min(R,G,B);
            C = V - m;
            if ( V !=0 ) { S = C / V; } else { S = 0; }

            if      ( C==0 ) { Hdash = 0; }
            else if ( V==R ) { Hdash = (G-B)/C; }
            else if ( V==G ) { Hdash = (B-R)/C + 2; }
            else if ( V==B ) { Hdash = (R-G)/C + 4; }

            if ( Hdash < 0 ) { H = Hdash/6 + 1; }
            else { H = Hdash/6; }

            set_pixel(im, i, j, 0, H);
            set_pixel(im, i, j, 1, S);
            set_pixel(im, i, j, 2, V);


        }
    }
}

void hsv_to_rgb(image im)
{
    int i,j;
    float H,S,V,max,min,Hdash;
    float R,G,B;
    for(j = 0; j < im.h; ++j){
        for(i = 0; i < im.w; ++i){
            
            H = get_pixel(im, i, j, 0);
            S = get_pixel(im, i, j, 1);
            V = get_pixel(im, i, j, 2);

            max = V;
            min = V*(1-S);

            Hdash = H*6;
            if ( Hdash < 1 ) {
                R = max;
                G = (max-min)*Hdash + min;
                B = min;
            }
            else if ( Hdash < 2 ) {
                R = max + (min-max)*(Hdash-1);
                G = max;
                B = min;
            }
            else if ( Hdash < 3 ) {
                G = max;
                R = min;
                B = min + (max-min)*(Hdash-2);
            }
            else if ( Hdash < 4 ) {
                B = max;
                R = min;
                G = B + (R-B)*(Hdash-3);
            }
            else if ( Hdash < 5 ) {
                B = max;
                G = min;
                R = G + (B-G)*(Hdash-4);
            }
            else if ( Hdash < 6 ) {
                R = max;
                G = min;
                B = R + (G-R)*(Hdash-5);
            }

            set_pixel(im, i, j, 0, R);
            set_pixel(im, i, j, 1, G);
            set_pixel(im, i, j, 2, B);

        }
    }
}

void scale_image(image im, int c, float v)
{   /**
    Function: scale image channel c by value v
    Args:
        im: struct contains images shape(weight, height, and channels)(im.w, im.h, im,c) and image pixels (im.data)
        c: int refers to channel number
        v: float refers to scale value
    */
    if(c <0 || c >= im.c)
        return;
    float pixel; 
    for(int y=0; y<im.h; y++)
        for(int x=0; x<im.w; x++){
            pixel = get_pixel(im, x, y, c);
            set_pixel(im, x, y, c, pixel * v);
        }
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    float sum = 0;
    for(int i = 0; i < im.w*im.h*im.c; ++i){
        sum += im.data[i];
    }
    printf("l1_normalize\n");
    for(int i = 0; i < im.w*im.h*im.c; ++i){
        im.data[i] /= sum;
        printf("%f ", im.data[i]);
    }


}

image make_box_filter(int w)
{
    image im = make_image(w,w,1);
    for (int i=0; i<im.w*im.h*im.c; ++i){
        im.data[i] = 1.0/w/w;

    }

    // printf("make_box_filter\n");
    // for(int y = 0; y < im.h; ++y){
    // for(int x = 0; x < im.w; ++x){
    //     printf("%f ", get_pixel(im,x,y,1));
    // }
    // printf("\n");
    // }

    return im;
}

image convolve_image(image im, image filter, int preserve)
{
    // Assume that the filter has an odd side length
    assert(filter.c == im.c || filter.c == 1);


    int r = (int)(filter.w / 2);

    // There's three options
    // If filter.c == im.c then produce an image with 1 channel
    // unless preserve = 1 then produce an image with the original number of channels
    // unless filter has only one channel. then we apply the same filter to all the different channels or sum them into one 
    // depending on whether preserve is set.

    // make a filter with same number of channels as the image
    image filter2 = make_image(filter.w, filter.h, im.c);
    for(int y = 0; y < im.h; ++y){
        for(int x = 0; x < im.w; ++x){
            for(int c = 0; c < im.c; ++c){
                set_pixel(filter2, x,y,c, get_pixel(filter,x,y,1) );
            }
        }
    }

    // do the convolution
    image convolution = make_image(im.w, im.h, im.c);
    for(int c = 0; c < im.c; ++c){
        for(int y = 0; y < im.h; ++y){
            for(int x = 0; x < im.w; ++x){

                float v = 0;
                for(int j = 0; j < filter.h; ++j){
                    for(int i = 0; i < filter.w; ++i){

                        v += get_pixel(im,x-r+i,y-r+j,c) * get_pixel(filter,i,j,c);
                    }
                }
                set_pixel(convolution, x,y,c,v);
            }
        }
    }

    if (preserve == 1){
        return convolution;
    }

    // if preserve = 0 then sum the convolved channels
    image single_channel_convolution = make_image(im.w, im.h, 1);
    for(int y = 0; y < im.h; ++y){
        for(int x = 0; x < im.w; ++x){
            float v = 0;
            for(int c = 0; c < im.c; ++c){
                v += get_pixel(convolution,x,y,c);
            }
            set_pixel(single_channel_convolution, x,y,1,v);
        }
    }
    return single_channel_convolution;

                        
}

image make_highpass_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_sharpen_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_emboss_filter()
{
    // TODO
    return make_image(1,1,1);
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}

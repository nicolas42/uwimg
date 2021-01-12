
// make -f nicks_makefile ; ./nicks_main

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "image.h"


int main(int argc, char** argv)
{
    printf("woo\n");


    // # 1. Getting and setting pixels
    image im = load_image("data/dog.jpg");
    for (int row=0; row<im.h; ++row){
        for (int col=0; col<im.w; ++col){
            set_pixel(im, col, row, 0, 0);
        }
    }
    save_image(im, "dog_no_red");


    // # 3. Grayscale image
    im = load_image("data/colorbar.png");
    image graybar = rgb_to_grayscale(im);
    save_image(graybar, "graybar");

    // # 4. Shift Image
    im = load_image("data/dog.jpg");
    shift_image(im, 0, .4);
    shift_image(im, 1, .4);
    shift_image(im, 2, .4);
    save_image(im, "overflow");

    // # 5. Clamp Image
    clamp_image(im);
    save_image(im, "doglight_fixed");

    // # 6-7. Colorspace and saturation
    im = load_image("data/dog.jpg");
    rgb_to_hsv(im);
    shift_image(im, 1, .2);
    clamp_image(im);
    hsv_to_rgb(im);
    save_image(im, "dog_saturated");

    // # Scale image 
    im = load_image("data/dog.jpg");
    rgb_to_hsv(im);
    scale_image(im, 1, 2);
    clamp_image(im);
    hsv_to_rgb(im);
    save_image(im, "dog_scale_saturated");


    return 0;
}


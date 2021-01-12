#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    return get_pixel(im, round(x), round(y), c);
}

image nn_resize(image im, int w, int h)
{
    image im2 = make_image(w,h,im.c);
    
    for(int j = 0; j < im2.h; ++j){
        for(int i = 0; i < im2.w; ++i){
            for(int c = 0; c < im2.c; ++c){                
                
                // From the new image (im2) pixel we add 0.5 to the coordinates to move into continuous 2D space,  
                // then we apply the scaling transformation, then we go back to pixel space by subtracting 0.5.

                // In continuous 2D space it makes sense to think of being in the middle of the pixel.

                float v = nn_interpolate(im, (float)((i+0.5) * im.w / im2.w - 0.5), (float)((j+0.5) * im.h / im2.h -0.5), c );
                set_pixel(im2,i,j,c,v);
            }
        }
    }
    return im2;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    int left = floorf(x);
    int right = ceilf(x);
    int top = floorf(y);
    int bottom = ceilf(y);

    // top < y < bottom
    // because of the way that pixels are arranged in the array the values of top, y, and bottom actually
    // sort in the reverse order of what their names suggest 
    // so to get positive values we use (bottom-y) and (y-top)

    float q1 = (bottom-y)*get_pixel(im, left,top,c) + (y-top)*get_pixel(im, left,bottom,c);
    
    float q2 = (bottom-y)*get_pixel(im, right,top,c) + (y-top)*get_pixel(im, right,bottom,c);

    return q1*(right-x) + q2*(x - left);
}

image bilinear_resize(image im, int w, int h)
{
        image im2 = make_image(w,h,im.c);
    
    for(int j = 0; j < im2.h; ++j){
        for(int i = 0; i < im2.w; ++i){
            for(int c = 0; c < im2.c; ++c){                
                
                // From the new image (im2) pixel we add 0.5 to the coordinates to move into continuous 2D space,  
                // then we apply the scaling transformation, then we go back to pixel space by subtracting 0.5.

                // In continuous 2D space it makes sense to think of being in the middle of the pixel.

                float v = bilinear_interpolate(im, (float)((i+0.5) * im.w / im2.w - 0.5), (float)((j+0.5) * im.h / im2.h -0.5), c );
                set_pixel(im2,i,j,c,v);
            }
        }
    }
    return im2;

}


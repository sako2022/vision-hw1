#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    // TODO
    for (int c = 0; c < im.c; c++)
    {
        for (int y = 0; y < im.h; y++)
        {
            for (int x = 0; x < im.w; x++)
            {
                float val = 1.0 / (im.w * im.h);
                set_pixel(im, x, y, c, val);
            }
        }
    }
}

image make_box_filter(int w)
{
    // TODO
    image im = make_image(w, w, 1);
    l1_normalize(im);
    return im;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    float c_step = 0;

    if (preserve == 1)
        c_step = im.c;
    else
        c_step = 1;
    
    image convolve_img = make_image(im.w, im.h, c_step);

    for (int c = 0; c < c_step; c++)
    {
        for (int y = 0; y < im.h; y++)
        {
            for (int x = 0; x < im.w; x++)
            {
                int step = filter.h;
                float result = 0;
                for (int i = -step / 2; i < step / 2 + 1; i++)
                {
                    for (int j = -step / 2; j < step / 2 + 1; j++)
                    {
                        float filter_val = get_pixel(filter,j + step / 2, i + step / 2, c);
                        float im_val = get_pixel(im, x + j, y + i, c);
                        result += (filter_val * im_val);
                    }
                }
                set_pixel(convolve_img, x, y, c, result);
            }
        }
    }
    
    return convolve_img;
}

image make_highpass_filter()
{    
    // TODO
    image high_filter = make_image(3, 3, 1);

    high_filter.data[1] = -1;
    high_filter.data[3] = -1;
    high_filter.data[4] = 4;
    high_filter.data[5] = -1;
    high_filter.data[7] = -1;
    
    return high_filter;
}

image make_sharpen_filter()
{
    // TODO
    image sharpen_filter = make_image(3, 3, 1);

    sharpen_filter.data[1] = -1;
    sharpen_filter.data[3] = -1;
    sharpen_filter.data[4] = 5;
    sharpen_filter.data[5] = -1;
    sharpen_filter.data[7] = -1;

    return sharpen_filter;
}

image make_emboss_filter()
{
    // TODO
    image emboss_filter = make_image(3, 3, 1);

    emboss_filter.data[0] = -2;
    emboss_filter.data[1] = -1;
    emboss_filter.data[3] = -1;
    emboss_filter.data[4] = 1;
    emboss_filter.data[5] = 1;
    emboss_filter.data[7] = 1;
    emboss_filter.data[8] = 2;

    return emboss_filter;
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

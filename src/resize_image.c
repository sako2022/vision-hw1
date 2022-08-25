#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    float val = get_pixel(im, round(x), round(y), c);
    return val;
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image img = make_image(w, h, im.c);
    float ax = (float)im.w / w;
    float bx = 0.5 * ax - 0.5;
    float ay = (float)im.h / h;
    float by = 0.5 * ay - 0.5;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            float r = nn_interpolate(im, ax * j + bx, ay * i + by, 0);
            float g = nn_interpolate(im, ax * j + bx, ay * i + by, 1);
            float b = nn_interpolate(im, ax * j + bx, ay * i + by, 2);
            set_pixel(img, j, i, 0, r);
            set_pixel(img, j, i, 1, g);
            set_pixel(img, j, i, 2, b);
        }
    }
    return img;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    float V1 = get_pixel(im, floorf(x), floorf(y), c);
    float V2 = get_pixel(im, ceilf(x), floorf(y), c);
    float V3 = get_pixel(im, floorf(x), ceilf(y), c);
    float V4 = get_pixel(im, floorf(x) + 1, ceilf(y), c);

    float d1 = x - floorf(x);
    float d2 = ceilf(x) - x;
    float d3 = y - floorf(y);
    float d4 = ceilf(y) - y;

    float A1 = d2 * d4;
    float A2 = d1 * d4;
    float A3 = d2 * d3;
    float A4 = d1 * d3;

    float q = V1 * A1 + V2 * A2 + V3 * A3 + V4 * A4;

    return q;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    image img = make_image(w, h, im.c);
    float ax = (float)im.w / w;
    float bx = 0.5 * ax - 0.5;
    float ay = (float)im.h / h;
    float by = 0.5 * ay - 0.5;
    
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            float r = bilinear_interpolate(im, ax * j + bx, ay * i + by, 0);
            float g = bilinear_interpolate(im, ax * j + bx, ay * i + by, 1);
            float b = bilinear_interpolate(im, ax * j + bx, ay * i + by, 2);
            set_pixel(img, j, i, 0, r);
            set_pixel(img, j, i, 1, g);
            set_pixel(img, j, i, 2, b);
        }
    }
    return img;
}


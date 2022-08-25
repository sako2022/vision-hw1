#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    if (y >= im.h)
        y = im.h - 1;
    else if (y < 0)
        y = 0;
    if (x >= im.w)
        x = im.w - 1;
    else if (x < 0)
        x = 0;
    if (c >= im.c)
        c = im.c - 1;
    else if (c < 0)
        c = 0;
    float pixel =  im.data[im.w * ((im.h * c) + y) + x];

    return pixel;
    //return 0;
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    int valid_y = (y < im.h) && (y >= 0);
    int valid_x = (x < im.w) && (x >= 0);
    int valid_c = (c < im.c) && (c >= 0);
    int valid_v = (v <= 255) && (v >= 0);
    if (valid_y && valid_x && valid_c && valid_v)
        // im.data[im.c * (im.h * (im.w * y) + x) + c] = v;
        im.data[im.w * ((im.h * c) + y) + x] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    memcpy(copy.data, im.data, im.c * im.h * im.w * sizeof(float));
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    for (int i = 0; i < im.h; i++)
    {
        for (int j = 0; j < im.w; j++)
        {
                int r = get_pixel(im, j, i, 0);
                int g = get_pixel(im, j, i, 1);
                int b = get_pixel(im, j, i, 2);
                float luma = 0.299 * r + 0.587 * g + 0.114 * b;
                set_pixel(gray, j, i, 0, luma);
        }
            
    }        

    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for (int i = 0; i < im.h; i++)
    {
        for (int j = 0; j < im.w; j++)
        {
            // im.data[im.w * ((im.h * c) + i) + j] += v;
            float val = get_pixel(im, j, i, c);
            set_pixel(im, j, i, c, val + v);
        }
    }   
}

void clamp_image(image im)
{
    // TODO Fill this in
    for (int i = 0; i < im.h; i++)
    {
        for (int j = 0; j < im.w; j++)
        {
            for (int k = 0; k < im.c; k++)
            {
                float val = get_pixel(im, j, i, k);
                if (val < 0)
                    set_pixel(im, j, i, k, 0);
                else if (val > 1)
                    set_pixel(im, j, i, k, 1);
            }
        }
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
    // TODO Fill this in
    for (int i = 0; i < im.h; i++)
    {
        for (int j = 0; j < im.w; j++)
        {
            float R = get_pixel(im, j, i, 0);
            float G = get_pixel(im, j, i, 1);
            float B = get_pixel(im, j, i, 2);

            float V = three_way_max(R, G, B);
            float m = three_way_min(R, G, B);
            float C = V - m;

            float S = 0;
            if (V != 0)
                S = C / V;

            float H_ = 0;
            if (C != 0)
            {
                if (V == R)
                    H_ = (G - B) / C;
                else if (V == G)
                    H_ = ((B - R) / C) + 2;
                else if (V == B)
                    H_ = ((R - G) / C) + 4;
            }

            float H = 0;
            if (H_ < 0)
                H = (H_ / 6) + 1;
            else
                H = H_ / 6;

            set_pixel(im, j, i, 0, H);
            set_pixel(im, j, i, 1, S);
            set_pixel(im, j, i, 2, V);
        }
    } 
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
    for (int i = 0; i < im.h; i++)
    {
        for (int j = 0; j < im.w; j++)
        {
            float H = get_pixel(im, j, i, 0);
            float S = get_pixel(im, j, i, 1);
            float V = get_pixel(im, j, i, 2);

            float C = S * V;
            float m = 0;
            if (V != C)
                m = V - C;
            float H_ = 6 * H;

            float R = V;
            float G = V;
            float B = V;

            if ((H_ > 0) && (H_ < 1))
            {
                R = V;
                B = m;
                G = H_ * C + m;
            }
            else if (H_ == 1)
            {
                R = V;
                G = V;
                B = m;
            }
            else if ((H_ > 1) && (H_ < 2))
            {
                G = V;
                B = m;
                R = (((H_ - 2) * C) - m) * -1;
            }
            else if (H_ == 2)
            {
                R = m;
                G = V;
                B = m;
            }
            else if ((H_ > 2) && (H_ < 3))
            {
                R = m;
                G = V;
                B = (H_ - 2) * C + m;
            }
            else if (H_ == 3)
            {
                R = m;
                G = V;
                B = V;
            }
            else if ((H_ > 3) && (H_ < 4))
            {
                R = m;
                B = V;
                G = (((H_ - 4) * C) - m) * -1;
            }
            else if (H_ == 4)
            {
                R = m;
                G = m;
                B = V;
            }
            else if ((H_ > 4) && (H_ < 5))
            {
                G = m;
                B = V;
                R = (H_ - 4) * C + m;
            }
            else if (H_ == 5)
            {
                R = V;
                G = m;
                B = V;
            }
            else if ((H_ > 5) && (H_ < 6))
            {
                R = V;
                B = m;
                G = ((((H_ / 6) - 1) * 6 * C) - m) * -1;
            }
            else
            {
                R = V;
                G = m;
                B = m;
            }
            set_pixel(im, j, i, 0, R);
            set_pixel(im, j, i, 1, G);
            set_pixel(im, j, i, 2, B);
        }
    }
}
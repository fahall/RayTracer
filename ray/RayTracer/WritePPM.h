//
//  WritePPM.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef RayTracer_WritePPM_h
#define RayTracer_WritePPM_h

// WritePPM() from http://rosettacode.org/wiki/Bitmap/Write_a_PPM_file

#include <vector>

inline float clampf(float f, float min, float max)
{
    if(f < min)
        f = min;
    if(f > max)
        f = max;
    return f;
}

inline void WritePPM(int dimx, int dimy, const char* fileName, const std::vector<nv::vec3f>& pixels)
{
    int i, j;
    FILE *fp = fopen(fileName, "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    for (j = dimy-1; j >= 0; --j)
    {
        for (i = 0; i < dimx; ++i)
        {
            static unsigned char color[3];
            color[0] = clampf(pixels[j*dimx + i].x, 0, 1) * 255; /* red */
            color[1] = clampf(pixels[j*dimx + i].y, 0, 1) * 255; /* green */
            color[2] = clampf(pixels[j*dimx + i].z, 0, 1) * 255; /* blue */
            (void) fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
}

#endif

//
//  utils.h
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef RayTracer_utils_h
#define RayTracer_utils_h

#include "nvMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define RT_RAND_MAX (4294967296)

inline nv::vec3f vecMin(const nv::vec3f& a, const nv::vec3f& b)
{
    return nv::vec3f(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

inline nv::vec3f vecMax(const nv::vec3f& a, const nv::vec3f& b)
{
    return nv::vec3f(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

inline float determ3x3(float elem[])
{
    return elem[0]*elem[4]*elem[8]+elem[2]*elem[3]*elem[7]+elem[1]*elem[5]*elem[6]-
    elem[2]*elem[4]*elem[6]-elem[0]*elem[5]*elem[7]-elem[1]*elem[3]*elem[8];
}

inline unsigned int randu(unsigned int& seed)
{
    // Take the current seed and generate a new value from it
    // Due to our use of large constants and overflow, it would be
    // very hard for someone to predict what the next number is
    // going to be from the previous one.
    seed = (8253729 * seed + 1099087573);
    
    // Take the seed and return a value between 0 and RT_RAND_MAX-1
    return seed % RT_RAND_MAX;
}

inline float rand(unsigned int& seed)
{
    return float(randu(seed)) / RT_RAND_MAX;
}

inline nv::vec3f rand_hs_cosn(unsigned int& seed, nv::vec3f normal, int n)
{
    float theta = 2 * M_PI * rand(seed);
    float phi;
    phi = (n==1) ? acosf(sqrt(rand(seed))) : acosf(powf(rand(seed), 1/float(n+1)));
    nv::vec3f u = (fabs(normal.y) > 0.99) ? nv::vec3f(1, 0, 0) : nv::vec3f(0, 1, 0);
    nv::vec3f v = normalize(cross(normal, u));
    u = cross(normal, v);
    return normalize((normal*cos(phi))+(u*sin(phi)*cos(theta))+(v*sin(phi)*sin(theta)));
}

inline nv::vec3f rand_hs_cos(unsigned int& seed, nv::vec3f normal)
{
    return rand_hs_cosn(seed, normal, 1);
}

inline nv::vec3f rand_hs(unsigned int& seed, nv::vec3f normal)
{
    return rand_hs_cosn(seed, normal, 0);
}

template<unsigned int N> static inline
unsigned int tea(unsigned int val0, unsigned int val1)
{
    unsigned int v0 = val0;
    unsigned int v1 = val1;
    unsigned int s0 = 0;
    
    for(unsigned int n = 0; n < N; n++)
    {
        s0 += 0x9e3779b9;
        v0 += ((v1<<4)+0xa341316c)^(v1+s0)^((v1>>5)+0xc8013ea4);
        v1 += ((v0<<4)+0xad90777d)^(v0+s0)^((v0>>5)+0x7e95761e);
    }
    
    return v0;
}

#endif

//
//  Sphere.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Sphere.h"
#include "utils.h"

HitInfo Sphere::intersect(const Ray& ray)
{
    HitInfo info;
    nv::vec3f ro2c = center - ray.orig;
    nv::vec3f dir_ro2c = normalize(ro2c);
    float len_ro2c = length(ro2c);
    float cos_theta = dot(dir_ro2c, ray.dir);
    float delta = len_ro2c * len_ro2c * cos_theta * cos_theta -
        len_ro2c * len_ro2c + radius * radius;
    if(delta < 0)
        return info;
    float d_min = len_ro2c * cos_theta - sqrt(delta);
    float d_max = len_ro2c * cos_theta + sqrt(delta);
    if(d_max < MIN_DIST)
        return info;
    
    if(d_min < MIN_DIST)
    {
        info.normal = normalize(ray.dir * d_max - ro2c);
        info.dist = d_max;
        return info;
    }
    
    info.normal = normalize(ray.dir * d_min - ro2c);
    info.dist = d_min;
    return info;
}

Ray Sphere::sampleOnSurface(unsigned &seed) const
{
    Ray ray;
    nv::vec3f dir = rand_hs(seed, nv::vec3f(0, 0, 1));
    if(rand(seed) < 0.5)
        dir = -dir;
    ray.orig = center+dir*radius;
    ray.origSampleType = RAY_SAMPLE_RANDOM;
    ray.normal = dir;
    return ray;
}

float Sphere::surfaceSampleProb(const Ray& ray) const
{
    return 1/(4*M_PI*radius*radius);
}
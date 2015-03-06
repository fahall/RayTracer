//
//  Parallelogram.cpp
//  RayTracer
//
//  Created by Weilun Sun on 3/2/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Parallelogram.h"
#include "utils.h"

HitInfo Parallelogram::intersect(const Ray& ray)
{
    nv::vec3f vertices[] = {center, center+v0, center+v1};
    HitInfo info;
    nv::vec3f rhs = ray.orig - vertices[0];
    nv::vec3f dir[2] = {vertices[1]-vertices[0], vertices[2]-vertices[0]};
    float mat[] = {   dir[0].x, dir[1].x, -ray.dir.x,
        dir[0].y, dir[1].y, -ray.dir.y,
        dir[0].z, dir[1].z, -ray.dir.z  };
    float mat_v01[] = {   rhs.x, dir[1].x, -ray.dir.x,
        rhs.y, dir[1].y, -ray.dir.y,
        rhs.z, dir[1].z, -ray.dir.z  };
    float mat_v02[] = {   dir[0].x, rhs.x, -ray.dir.x,
        dir[0].y, rhs.y, -ray.dir.y,
        dir[0].z, rhs.z, -ray.dir.z  };
    float mat_t[] = {     dir[0].x, dir[1].x, rhs.x,
        dir[0].y, dir[1].y, rhs.y,
        dir[0].z, dir[1].z, rhs.z  };
    float det = determ3x3(mat);
    if(det == 0)
        return info;
    float d01 = determ3x3(mat_v01) / det;
    float d02 = determ3x3(mat_v02) / det;
    float t = determ3x3(mat_t) / det;
    if(d01 < 0 || d02 < 0 || t < MIN_DIST)
        return info;
    info.dist = t;
    info.normal = getNormal();
    return info;
}

Ray Parallelogram::sampleOnSurface(unsigned &seed) const
{
    float d01 = rand(seed);
    float d02 = rand(seed);
    Ray ray;
    ray.dir = rand_hs_cos(seed, getNormal());
    ray.orig = center+d01*v0+d02*v1;
    ray.origSampleType = RAY_SAMPLE_RANDOM;
    ray.normal = getNormal();
    return ray;
}

float Parallelogram::surfaceSampleOriginProb(const Ray& ray) const
{
    return 1/fabs(length(cross(v0, v1)));
}

nv::vec3f Parallelogram::getLowerBound() const
{
    nv::vec3f vertices[] = {center, center+v0, center+v1, center+v0+v1};
    return vecMin(vecMin(vecMin(vertices[0], vertices[1]), vertices[2]), vertices[3]);
}

nv::vec3f Parallelogram::getUpperBound() const
{
    nv::vec3f vertices[] = {center, center+v0, center+v1, center+v0+v1};
    return vecMax(vecMax(vecMax(vertices[0], vertices[1]), vertices[2]), vertices[3]);
}

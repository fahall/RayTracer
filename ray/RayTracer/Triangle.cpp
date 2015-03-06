//
//  Triangle.cpp
//  RayTracer
//
//  Created by Weilun Sun on 3/2/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Triangle.h"
#include "utils.h"

HitInfo Triangle::intersect(const Ray& ray)
{
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
    if(d01 < 0 || d02 < 0 || d01+d02 > 1 || t < MIN_DIST)
        return info;
    info.dist = t;
    info.normal = getNormal(d01, d02);
    info.texCoord = getTexCoord(d01, d02);
    return info;
}

Ray Triangle::sampleOnSurface(unsigned &seed) const
{
    float d01 = rand(seed);
    float d02 = rand(seed);
    if(d01+d02>1)
    {
        d01 = 1-d01;
        d02 = 1-d02;
    }
    Ray ray;
    ray.dir = rand_hs_cos(seed, getNormal(d01, d02));
    ray.orig = vertices[0]+d01*(vertices[1]-vertices[0])+d02*(vertices[2]-vertices[0]);
    ray.origSampleType = RAY_SAMPLE_RANDOM;
    ray.normal = getNormal(d01, d02);
    return ray;
}

float Triangle::surfaceSampleOriginProb(const Ray& ray) const
{
    return 1/(fabs(length(cross(vertices[1]-vertices[0], vertices[2]-vertices[0])))*0.5);
}

nv::vec3f Triangle::getLowerBound() const
{
    return vecMin(vecMin(vertices[0], vertices[1]), vertices[2]);
}

nv::vec3f Triangle::getUpperBound() const
{
    return vecMax(vecMax(vertices[0], vertices[1]), vertices[2]);
}

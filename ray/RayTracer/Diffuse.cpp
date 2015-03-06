//
//  Diffuse.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "utils.h"
#include "Diffuse.h"

Ray Diffuse::scatter(const Ray& inRay, const HitInfo& hitInfo)
{
    Ray outRay = inRay;
    nv::vec3f newDir = rand_hs_cos(outRay.seed, hitInfo.normal);
    outRay.dir = newDir;
    outRay.orig = inRay.dir * hitInfo.dist + inRay.orig;
    outRay.importance = getBRDF(inRay, outRay) * inRay.importance / (1 / M_PI * rrProb());
    outRay.normal = hitInfo.normal;
    outRay.contactObject = object;
    outRay.dirSampleType = RAY_SAMPLE_RANDOM;
    outRay.origSampleType = RAY_SAMPLE_DEFINITE;
    if(rrProb() < rand(outRay.seed))
        outRay.status = RAY_STATUS_TERMINATED;
    return outRay;
}

nv::vec3f Diffuse::getBRDF(const Ray& inRay, const Ray& outRay)
{
    return color / M_PI;
}
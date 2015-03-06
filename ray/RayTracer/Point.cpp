//
//  Point.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Point.h"

HitInfo Point::intersect(const Ray& ray)
{
    return HitInfo();
}

Ray Point::sampleOnSurface(unsigned &seed) const
{
    Ray ray;
    ray.orig = center;
    ray.origSampleType = RAY_SAMPLE_DEFINITE;
    return ray;
}
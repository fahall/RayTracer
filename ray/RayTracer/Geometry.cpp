//
//  Geometry.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Geometry.h"
#include <limits.h>

HitInfo Geometry::intersect(const Ray& ray)
{
    HitInfo info;
    return info;
}

Ray Geometry::sampleOnSurface(unsigned& seed) const
{
    return Ray();
}

float Geometry::surfaceSampleOriginProb(const Ray& ray) const
{
    return 1;
}

float Geometry::surfaceSampleDirProb(const Ray& ray) const
{
    return 1/(M_PI); // cos sampling by default
}

nv::vec3f Geometry::getLowerBound() const { return nv::vec3f(); }
nv::vec3f Geometry::getUpperBound() const { return nv::vec3f(); }
//
//  Parallelogram.h
//  RayTracer
//
//  Created by Weilun Sun on 3/2/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Parallelogram__
#define __RayTracer__Parallelogram__

#include <stdio.h>
#include "Geometry.h"

class Parallelogram : public Geometry
{
public:
    nv::vec3f center, v0, v1;
    nv::vec3f getNormal() const
    {
        return normalize(cross(v0, v1));
    }
    
    Parallelogram(Object* object) : Geometry(object) {}
    virtual HitInfo intersect(const Ray& ray);
    virtual Ray sampleOnSurface(unsigned &seed) const;
    virtual float surfaceSampleOriginProb(const Ray& ray) const;
    virtual nv::vec3f getLowerBound() const;
    virtual nv::vec3f getUpperBound() const;
};

#endif /* defined(__RayTracer__Parallelogram__) */

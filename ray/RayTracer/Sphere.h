//
//  Sphere.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Sphere__
#define __RayTracer__Sphere__

#include <stdio.h>
#include "Geometry.h"

class Sphere : public Geometry
{
protected:
    nv::vec3f center;
    float radius;
public:
    Sphere(Object* object) : Geometry(object) {}
    void setCenter(const nv::vec3f& center) { this->center = center; }
    void setRadius(float radius) { this->radius = radius; }
    virtual HitInfo intersect(const Ray& ray);
    virtual Ray sampleOnSurface(unsigned &seed) const;
    virtual float surfaceSampleProb(const Ray& ray) const;
    virtual nv::vec3f getLowerBound() const
    {
        return center - nv::vec3f(radius, radius, radius);
    }
    virtual nv::vec3f getUpperBound() const
    {
        return center + nv::vec3f(radius, radius, radius);
    }
};

#endif /* defined(__RayTracer__Sphere__) */

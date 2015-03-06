//
//  Geometry.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Geometry__
#define __RayTracer__Geometry__

#include <stdio.h>
#include "HitInfo.h"
#include "Object.h"

class Object;

class Geometry
{
protected:
    Object* object;
public:
    Geometry(Object* object) { this->object = object; }
    virtual Ray sampleOnSurface(unsigned& seed) const;
    virtual float surfaceSampleOriginProb(const Ray& ray) const;
    virtual float surfaceSampleDirProb(const Ray& ray) const;
    virtual HitInfo intersect(const Ray& ray);
    virtual ~Geometry() {}
    virtual nv::vec3f getLowerBound() const;
    virtual nv::vec3f getUpperBound() const;
};

#endif /* defined(__RayTracer__Geometry__) */

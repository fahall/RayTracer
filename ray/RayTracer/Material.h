//
//  Material.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Material__
#define __RayTracer__Material__

#include <stdio.h>
#include "Geometry.h"
#include "Object.h"

class Object;

class Material
{
protected:
    Object* object;
public:
    Material(Object* object) { this->object = object; }
    virtual float getDirProb(const Ray& ray) const { return 1.0; }
    virtual float getOriginProb(const Ray& ray) const { return 1.0; }
    virtual nv::vec3f getRadiance() const { return nv::vec3f(0, 0, 0); }
    virtual nv::vec3f getBRDF(const Ray& inRay, const Ray& outRay);
    virtual Ray scatter(const Ray& inRay, const HitInfo& hitInfo) { return Ray(); }
    virtual ~Material() {}
};

#endif /* defined(__RayTracer__Material__) */

//
//  AreaLight.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__AreaLight__
#define __RayTracer__AreaLight__

#include <stdio.h>
#include "Material.h"

class AreaLight : public Material
{
protected:
    nv::vec3f radiance;
public:
    void setRadiance(const nv::vec3f& radiance) { this->radiance = radiance; }
    AreaLight(Object* object) : Material(object) {}
    virtual Ray scatter(const Ray& inRay, const HitInfo& hitInfo);
    virtual nv::vec3f getRadiance() const { return radiance; }
    virtual nv::vec3f getBRDF(const Ray& inRay, const Ray& outRay)
    {
        return dot(outRay.dir, outRay.normal) > 0 ? 1.0 : 0.0;
    }
    virtual float getDirProb(const Ray& ray) const { return object->surfaceSampleDirProb(ray); }
    virtual float getOriginProb(const Ray& ray) const { return object->surfaceSampleOriginProb(ray); }
};

#endif /* defined(__RayTracer__AreaLight__) */

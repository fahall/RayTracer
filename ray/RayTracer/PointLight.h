//
//  PointLight.h
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__PointLight__
#define __RayTracer__PointLight__

#include "Material.h"

class PointLight : public Material
{
protected:
    nv::vec3f radiance;
public:
    void setRadiance(const nv::vec3f& radiance) { this->radiance = radiance; }
    PointLight(Object* object) : Material(object) {}
    virtual Ray scatter(const Ray& inRay, const HitInfo& hitInfo);
    virtual nv::vec3f getRadiance() const { return radiance; }
};

#endif /* defined(__RayTracer__PointLight__) */
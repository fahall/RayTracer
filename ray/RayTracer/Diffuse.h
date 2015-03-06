//
//  Diffuse.h
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Diffuse__
#define __RayTracer__Diffuse__

#include "Material.h"

class Diffuse : public Material
{
protected:
    nv::vec3f color;
    float rrProb() const
    {
        return std::max(color.x, std::max(color.y, color.z));
    }
public:
    void setColor(const nv::vec3f& color) { this->color = color; }
    Diffuse(Object* object) : Material(object) {}
    virtual Ray scatter(const Ray& inRay, const HitInfo& hitInfo);
    virtual nv::vec3f getBRDF(const Ray& inRay, const Ray& outRay);
    virtual float getDirProb(const Ray& ray) const { return rrProb() * (1 / M_PI); }
};

#endif /* defined(__RayTracer__Diffuse__) */

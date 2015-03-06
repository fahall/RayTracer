//
//  Point.h
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Point__
#define __RayTracer__Point__

#include "Geometry.h"

class Point : public Geometry
{
protected:
    nv::vec3f center;
public:
    Point(Object* object) : Geometry(object) {}
    void setCenter(const nv::vec3f& center) { this->center = center; }
    virtual HitInfo intersect(const Ray& ray);
    virtual Ray sampleOnSurface(unsigned &seed) const;
};

#endif /* defined(__RayTracer__Point__) */

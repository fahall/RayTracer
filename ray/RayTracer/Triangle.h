//
//  Triangle.h
//  RayTracer
//
//  Created by Weilun Sun on 3/2/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Triangle__
#define __RayTracer__Triangle__

#include <stdio.h>
#include "Geometry.h"

class Triangle : public Geometry
{
public:
    nv::vec3f vertices[3], normals[3], texCoord[3];
    nv::vec3f getNormal(float d01, float d02) const
    {
        if(length(normals[0]) < 0.5)
            return normalize(cross(vertices[1]-vertices[0], vertices[2]-vertices[1]));
        return normals[0]+d01*normals[1]+d02*normals[2];
    }
    nv::vec3f getTexCoord(float d01, float d02) const
    {
        return texCoord[0]+d01*texCoord[1]+d02*texCoord[2];
    }
    Triangle(Object* object) : Geometry(object) {}
    virtual HitInfo intersect(const Ray& ray);
    virtual Ray sampleOnSurface(unsigned &seed) const;
    virtual float surfaceSampleOriginProb(const Ray& ray) const;
    virtual nv::vec3f getLowerBound() const;
    virtual nv::vec3f getUpperBound() const;
};


#endif /* defined(__RayTracer__Triangle__) */

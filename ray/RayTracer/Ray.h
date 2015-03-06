//
//  Ray.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef RayTracer_Ray_h
#define RayTracer_Ray_h

#include "nvMath.h"
#include <stdlib.h>

#define RAY_STATUS_TRACING 0
#define RAY_STATUS_TERMINATED 1

#define RAY_SAMPLE_DEFINITE 0
#define RAY_SAMPLE_RANDOM 1

class Object;

struct Ray
{
    Object* contactObject;
    unsigned seed;
    nv::vec3f normal;
    nv::vec3f orig, dir;
    nv::vec3f radiance, importance;
    float prob;
    unsigned origSampleType;
    unsigned dirSampleType;
    unsigned status;
    Ray()
    {
        contactObject = NULL;
        status = RAY_STATUS_TRACING;
        prob = 1;
        importance = nv::vec3f(1, 1, 1);
    }
    nv::vec3f getOrig() const{ return orig; }
    nv::vec3f getDir() const{ return dir; }
    float getOriginProb() const;
};

#endif

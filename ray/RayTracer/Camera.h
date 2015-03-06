//
//  Camera.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Camera__
#define __RayTracer__Camera__

#include <stdio.h>
#include <vector>
#include "Ray.h"
#include "Tracer.h"

class Tracer;

class Camera
{
protected:
    Tracer* tracer;
public:
    Camera(Tracer* tracer) { this->tracer = tracer; }
    virtual std::vector<Ray> generateRays();
    virtual ~Camera() {}
};

#endif /* defined(__RayTracer__Camera__) */

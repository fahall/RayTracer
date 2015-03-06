//
//  PinholeCamera.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__PinholeCamera__
#define __RayTracer__PinholeCamera__

#include <stdio.h>
#include "Camera.h"

class PinholeCamera : public Camera
{
protected:
    nv::vec3f orig, up, focus;
    float focalLength;
public:
    void place(const nv::vec3f& orig, const nv::vec3f& up, const nv::vec3f& focus)
    {
        this->orig = orig;
        this->up = up;
        this->focus = focus;
    }
    void setFovx(float fovx) { focalLength = 0.5 * tanf(fovx * M_PI / 360); }
    PinholeCamera(Tracer* tracer) : Camera(tracer) {}
    std::vector<Ray> generateRays();
    std::vector<float> generateRays2();
};

#endif /* defined(__RayTracer__PinholeCamera__) */

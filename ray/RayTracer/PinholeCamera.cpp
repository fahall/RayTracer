//
//  PinholeCamera.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "PinholeCamera.h"
#include "utils.h"


std::vector<Ray> PinholeCamera::generateRays()
{
    unsigned nPixels = tracer->getWidth() * tracer->getHeight();
    std::vector<Ray> rays(nPixels);
    
    float rz = focalLength;
    
    nv::vec3f front, relUp, right;
    front = normalize(focus - orig);
    right = cross(front, up);
    right = normalize(right);
    relUp = cross(right, front);
    
    float rx, ry;
    float jx = 0, jy = 0;
    
    for(unsigned pi=0; pi<nPixels; pi++)
    {
        rays[pi].seed = tea<4>(pi, tracer->getNumSamples());
        
        // jittering
        jx = rand(rays[pi].seed);
        jy = rand(rays[pi].seed);
        
        rx = float((pi) % tracer->getWidth() + jx) / tracer->getWidth() - 0.5;
        ry = float((pi) / tracer->getWidth() + jy) / tracer->getWidth();
        ry -= 0.5 * (tracer->getHeight()) / float(tracer->getWidth());
        rays[pi].orig = orig;
        rays[pi].dir = normalize(rx * right + ry * relUp + rz * front);
    }
    return rays;
}
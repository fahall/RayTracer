//
//  HitInfo.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef RayTracer_HitInfo_h
#define RayTracer_HitInfo_h

#include "nvMath.h"
#include <limits>

#define MIN_DIST (1e-3)

class HitInfo
{
public:
    unsigned index;
    nv::vec3f normal, texCoord;
    float dist;
    
    bool isHit()
    {
        return !(dist == std::numeric_limits<float>::infinity());
    }
    HitInfo()
    {
        dist = std::numeric_limits<float>::infinity();
    }
};

#endif

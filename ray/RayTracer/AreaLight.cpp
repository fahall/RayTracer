//
//  AreaLight.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "AreaLight.h"

Ray AreaLight::scatter(const Ray& inRay, const HitInfo& hitInfo)
{
    Ray outRay = inRay;
    if(length(hitInfo.normal) < 0.5 || dot(hitInfo.normal, inRay.dir) < 0)
        outRay.radiance = radiance;
    outRay.status = RAY_STATUS_TERMINATED;
    outRay.normal = hitInfo.normal;
    return outRay;
}
//
//  PointLight.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "PointLight.h"

Ray PointLight::scatter(const Ray& inRay, const HitInfo& hitInfo)
{
    Ray outRay = inRay;
    outRay.radiance = radiance;
    outRay.status = RAY_STATUS_TERMINATED;
    return outRay;
}
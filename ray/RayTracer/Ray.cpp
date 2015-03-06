//
//  Ray.cpp
//  RayTracer
//
//  Created by Weilun Sun on 3/6/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Ray.h"
#include "Object.h"

float Ray::getOriginProb() const
{
    if(contactObject)
        return contactObject->getOriginProb(*this);
    return 1.0;
}

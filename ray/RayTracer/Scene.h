//
//  Scene.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Scene__
#define __RayTracer__Scene__

#include <stdio.h>
#include "Object.h"
#include "KDTree.h"
#include "Tracer.h"
#include "HitInfo.h"
#include "Ray.h"
#include <vector>

class Tracer;
class Object;

class Scene
{
protected:
    KDTree<Ray, Object*> kdTree;
    std::vector<Object*> lightSources;
    Tracer* tracer;
    virtual HitInfo intersect(const Ray& inRay);
public:
    
    std::vector<Ray> generateLightRays(unsigned& seed);
    nv::vec3f connect(const Ray& eyeRay, const Ray& lightRay);
    Scene(Tracer* tracer) { this->tracer = tracer; }
    std::vector<Object*> objects;
    std::vector<Object*> getLightSources() const { return lightSources; }
    void build();
    virtual Ray scatter(const Ray& inRay);
    virtual ~Scene();
};

#endif /* defined(__RayTracer__Scene__) */

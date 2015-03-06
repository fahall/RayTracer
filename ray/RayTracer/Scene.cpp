//
//  Scene.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Scene.h"

std::vector<Ray> Scene::generateLightRays(unsigned& seed)
{
    std::vector<Ray> lightRays(lightSources.size());
    for(unsigned i=0; i<lightSources.size(); i++)
    {
        Ray lightRay = lightSources[i]->sampleOnSurface(seed);
        lightRay.radiance = lightSources[i]->materials.front()->getRadiance();
        lightRays[i] = lightRay;
    }
    return lightRays;
}

nv::vec3f Scene::connect(const Ray& eyeRay, const Ray& lightRay)
{
    if(!eyeRay.contactObject)
        return nv::vec3f(0, 0, 0);
    
    float r = length(lightRay.orig - eyeRay.orig);
    Ray connectEyeRay = eyeRay;
    Ray connectLightRay = lightRay;
    connectEyeRay.dir = normalize(lightRay.orig - eyeRay.orig);
    connectLightRay.dir = -connectEyeRay.dir;
    
    // test visibility
    HitInfo info = intersect(connectLightRay);
    
    if(info.dist + MIN_DIST < r)
        return nv::vec3f(0, 0, 0);
    
    nv::vec3f color;
    color = eyeRay.importance * connectEyeRay.contactObject->getBRDF(eyeRay, connectEyeRay);
    color *= fabs(dot(connectEyeRay.dir, connectEyeRay.normal)) * fabs(dot(connectLightRay.normal, connectLightRay.dir));
    color *= lightRay.radiance * lightRay.importance * connectLightRay.contactObject->getBRDF(lightRay, connectLightRay);
    color /= r*r;
    float prob = lightRay.getOriginProb();
    color /= prob;
    return color;
}

void Scene::build()
{
    for(unsigned i=0; i<objects.size(); i++)
    {
        if(length(objects[i]->materials[0]->getRadiance()) > 0)
            lightSources.push_back(objects[i]);
        objects[i]->build();
    }
    kdTree.build(objects);
}

HitInfo Scene::intersect(const Ray& inRay)
{
    return kdTree.intersect(inRay);
}

Ray Scene::scatter(const Ray& inRay)
{
    HitInfo geoInfo = intersect(inRay);
    
    Ray outRay;
    if(!geoInfo.isHit())
    {
        outRay.status = RAY_STATUS_TERMINATED;
        return outRay;
    }
    
    outRay = objects[geoInfo.index]->scatter(inRay, geoInfo);
    
    return outRay;
}

Scene::~Scene()
{
    for(unsigned i=0; i<objects.size(); i++)
        delete objects[i];
}
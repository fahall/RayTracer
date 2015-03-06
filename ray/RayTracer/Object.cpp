//
//  Object.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Object.h"

float Object::getOriginProb(const Ray& ray) const
{
    return materials.front()->getOriginProb(ray);
}

float Object::getDirProb(const Ray& ray) const
{
    return materials.front()->getDirProb(ray);
}

nv::vec3f Object::getBRDF(const Ray& inRay, const Ray& outRay)
{
    return materials.front()->getBRDF(inRay, outRay);
}

Ray Object::sampleOnSurface(unsigned& seed) const
{
    Ray ray = geometries[0]->sampleOnSurface(seed);
    ray.contactObject = (Object*)this;
    return ray;
}

float Object::surfaceSampleOriginProb(const Ray& ray) const
{
    return geometries[0]->surfaceSampleOriginProb(ray);
}

float Object::surfaceSampleDirProb(const Ray& ray) const
{
    return geometries[0]->surfaceSampleDirProb(ray);
}

HitInfo Object::intersect(const Ray& inRay)
{
    return kdTree.intersect(inRay);
}

Ray Object::scatter(const Ray& inRay, const HitInfo& geoInfo)
{
    Ray outRay;
    outRay = materials[0]->scatter(inRay, geoInfo);
    return outRay;
}

void Object::build()
{
    kdTree.build(geometries, 4);
    bounds[0] = kdTree.getLowerBound();
    bounds[1] = kdTree.getUpperBound();
}

Object::~Object()
{
    for(unsigned i=0; i<materials.size(); i++)
        delete materials[i];
    for(unsigned i=0; i<geometries.size(); i++)
        delete geometries[i];
}

//
//  Object.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Object__
#define __RayTracer__Object__

#include <vector>
#include <stdio.h>
#include "Ray.h"
#include "Scene.h"
#include "Material.h"
#include "Geometry.h"
#include "KDTree.h"

class Scene;
class Material;
class Geometry;

class Object
{
protected:
    Scene* scene;
    nv::vec3f bounds[2];
    KDTree<Ray, Geometry*> kdTree;
public:
    std::vector<Material*> materials;
    std::vector<Geometry*> geometries;
    Object(Scene* scene) { this->scene = scene; }
    
    // build KDTree
    void build();
    
    virtual Ray sampleOnSurface(unsigned& seed) const;
    virtual float getOriginProb(const Ray& ray) const;
    virtual float getDirProb(const Ray& ray) const;
    virtual float surfaceSampleOriginProb(const Ray& ray) const;
    virtual float surfaceSampleDirProb(const Ray& ray) const;
    virtual nv::vec3f getBRDF(const Ray& inRay, const Ray& outRay);
    virtual HitInfo intersect(const Ray& inRay);
    virtual Ray scatter(const Ray& inRay, const HitInfo& geoInfo);
    virtual nv::vec3f getLowerBound() const { return bounds[0]; }
    virtual nv::vec3f getUpperBound() const { return bounds[1]; };
    virtual ~Object();
};

#endif /* defined(__RayTracer__Object__) */

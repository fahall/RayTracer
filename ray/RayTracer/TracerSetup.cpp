//
//  TracerSetup.cpp
//  RayTracer
//
//  Created by Weilun Sun on 3/6/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include <stdio.h>
#include "Tracer.h"
#include "PinholeCamera.h"
#include "AreaLight.h"
#include "Sphere.h"
#include "Point.h"
#include "Diffuse.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "macros.h"

void Tracer::setupTracer()
{
// Cornell Box
    PinholeCamera *pinholeCamera = new PinholeCamera(this);
    pinholeCamera->setFovx(120);
    pinholeCamera->place(nv::vec3f(0, 0, 2.5), nv::vec3f(0, 1, 0), nv::vec3f(0, 0, 0));
    
    camera = pinholeCamera;
    
    scene = new Scene(this);
    
    Object* light = new Object(scene);
    
    Triangle* triangle = new Triangle(light);
    triangle->vertices[0] = nv::vec3f(-0.1, 0.9, 0.1);
    triangle->vertices[1] = nv::vec3f(0.1, 0.9, -0.1);
    triangle->vertices[2] = nv::vec3f(0.1, 0.9, 0.1);
    
    Parallelogram *para = new Parallelogram(light);
    para->center = nv::vec3f(-0.1, 0.99, -0.1);
    para->v0 = nv::vec3f(0.2, 0, 0);
    para->v1 = nv::vec3f(0, 0, 0.2);
    
    Sphere* sphere = new Sphere(light);
    sphere->setCenter(nv::vec3f(0, 0.8, 0));
    sphere->setRadius(0.1);
    
    AreaLight* areaLight = new AreaLight(light);
    areaLight->setRadiance(nv::vec3f(250, 250, 250));
    light->materials.push_back(areaLight);
    light->geometries.push_back(para);
    
    scene->objects.push_back(light);
    
    // diffuse balls
    {
        Object* diffuseSphere = new Object(scene);
        Diffuse* diffuse = new Diffuse(diffuseSphere);
        diffuse->setColor(nv::vec3f(0.75, 0.75, 0.25));
        
        unsigned len = 1;
        for(unsigned x=0; x<len; x++)
            for(unsigned y=0; y<len; y++)
                for(unsigned z=0; z<len; z++)
                {
                    Sphere* sphere = new Sphere(diffuseSphere);
                    sphere->setCenter(nv::vec3f(float(x+0.5)/len-0.5, float(y+0.5)/len-0.5, float(z+0.5)/len-0.5));
                    sphere->setRadius(0.4 / len);
                    diffuseSphere->geometries.push_back(sphere);
                }
        
        diffuseSphere->materials.push_back(diffuse);
        scene->objects.push_back(diffuseSphere);
    }
    
    // left wall
    {
        Object* wall = new Object(scene);
        Diffuse* diffuse = new Diffuse(wall);
        diffuse->setColor(nv::vec3f(0.75, 0.25, 0.25));
        
        Parallelogram *para = new Parallelogram(light);
        para->center = nv::vec3f(-1, -1, 1);
        para->v0 = nv::vec3f(0, 0, -2);
        para->v1 = nv::vec3f(0, 2, 0);
        wall->geometries.push_back(para);
        
        wall->materials.push_back(diffuse);
        scene->objects.push_back(wall);
    }
    
    // right wall
    {
        Object* wall = new Object(scene);
        Diffuse* diffuse = new Diffuse(wall);
        diffuse->setColor(nv::vec3f(0.25, 0.75, 0.25));
        
        Parallelogram *para = new Parallelogram(light);
        para->center = nv::vec3f(1, -1, 1);
        para->v0 = nv::vec3f(0, 2, 0);
        para->v1 = nv::vec3f(0, 0, -2);
        wall->geometries.push_back(para);
        
        wall->materials.push_back(diffuse);
        scene->objects.push_back(wall);
    }
    
    // floor
    {
        Object* wall = new Object(scene);
        Diffuse* diffuse = new Diffuse(wall);
        diffuse->setColor(nv::vec3f(0.5, 0.5, 0.5));
        
        Parallelogram *para = new Parallelogram(light);
        para->center = nv::vec3f(-1, -1, 1);
        para->v0 = nv::vec3f(2, 0, 0);
        para->v1 = nv::vec3f(0, 0, -2);
        wall->geometries.push_back(para);
        
        wall->materials.push_back(diffuse);
        scene->objects.push_back(wall);
    }
    
    // ceiling
    {
        Object* wall = new Object(scene);
        Diffuse* diffuse = new Diffuse(wall);
        diffuse->setColor(nv::vec3f(0.5, 0.5, 0.5));
        
        Parallelogram *para = new Parallelogram(light);
        para->center = nv::vec3f(-1, 1, 1);
        para->v0 = nv::vec3f(0, 0, -2);
        para->v1 = nv::vec3f(2, 0, 0);
        wall->geometries.push_back(para);
        
        wall->materials.push_back(diffuse);
        scene->objects.push_back(wall);
    }
    
    // back wall
    {
        Object* wall = new Object(scene);
        Diffuse* diffuse = new Diffuse(wall);
        diffuse->setColor(nv::vec3f(0.5, 0.5, 0.5));
        
        Parallelogram *para = new Parallelogram(light);
        para->center = nv::vec3f(-1, 1, -1);
        para->v0 = nv::vec3f(0, -2, 0);
        para->v1 = nv::vec3f(2, 0, 0);
        wall->geometries.push_back(para);
        
        wall->materials.push_back(diffuse);
        scene->objects.push_back(wall);
    }
    
    scene->build();
}

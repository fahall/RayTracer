//
//  Tracer.h
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef __RayTracer__Tracer__
#define __RayTracer__Tracer__

#include <stdio.h>
#include "Ray.h"
#include "Scene.h"
#include "Camera.h"
#include "WritePPM.h"

class Scene;
class Camera;

class Tracer
{
protected:
    Camera *camera;
    Scene *scene;
    unsigned width, height;
    std::vector<nv::vec3f> pixels;
    unsigned maxDepth;
    std::vector<Ray> sampleEyePath(const Ray& eyeRay);
    unsigned nSamples;
    float gamma;
    unsigned nPassesPerSample;
    unsigned passNum;
public:
    std::vector<nv::vec3f> getPixels() const;
    std::vector<nv::vec3f> getPixelsOriginal() const { return pixels; }
    unsigned getWidth() const { return width; }
    unsigned getHeight() const { return height; }
    unsigned getNumSamples() const { return nSamples; }
    void setImageSize(unsigned w, unsigned h)
    {
        width = w;
        height = h;
        pixels.resize(w*h, nv::vec3f(0, 0, 0));
    }
    void traceRange(const std::vector<Ray>& camRays, unsigned startIdx, unsigned endIdx);
    Tracer();
    void setupTracer();
    virtual void trace();
    virtual ~Tracer();
};

#endif /* defined(__RayTracer__Tracer__) */

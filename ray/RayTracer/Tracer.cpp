//
//  Tracer.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "Tracer.h"
#include "PinholeCamera.h"
#include "AreaLight.h"
#include "Sphere.h"
#include "Point.h"
#include "Diffuse.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "macros.h"

#if USE_TBB

#include <tbb/parallel_for.h>

class tbb_parallel_task
{
private:
    static Tracer* tracer;
    static std::vector<Ray>* pixelRays;
public:
    static void set_values (Tracer* t, std::vector<Ray>& p)
    {
        tracer = t;
        pixelRays = &p;
    }
    
    void operator()( const tbb::blocked_range<size_t>& r ) const
    {
        int begin = (int)r.begin();            //! capture lower range number for this chunk
        int end = (int)r.end();                //! capture upper range number for this chunk
        tracer->traceRange(*pixelRays, begin, end);
    }
    
    tbb_parallel_task() {}
};

Tracer* tbb_parallel_task::tracer;
std::vector<Ray>* tbb_parallel_task::pixelRays;

#endif

Tracer::Tracer()
{
    passNum = 0;
    nSamples = 0;
    maxDepth = 4;
    gamma = 2.2;
    nPassesPerSample = 8;
    setupTracer();
}

std::vector<nv::vec3f> Tracer::getPixels() const
{
    std::vector<nv::vec3f> gammaPixels = pixels;
    for(unsigned i=0; i<gammaPixels.size(); i++)
    {
        gammaPixels[i].x = powf(pixels[i].x, 1.0/gamma);
        gammaPixels[i].y = powf(pixels[i].y, 1.0/gamma);
        gammaPixels[i].z = powf(pixels[i].z, 1.0/gamma);
    }
    return gammaPixels;
}

std::vector<Ray> Tracer::sampleEyePath(const Ray& eyeRay)
{
    Ray currentRay = eyeRay;
    std::vector<Ray> rays;
    while(currentRay.status == RAY_STATUS_TRACING)
    {
        rays.push_back(currentRay);
        currentRay = scene->scatter(currentRay);
        if(rays.size() >= maxDepth)
            currentRay.status = RAY_STATUS_TERMINATED;
    }
    rays.push_back(currentRay);
    return rays;
}

void Tracer::traceRange(const std::vector<Ray>& camRays, unsigned startIdx, unsigned endIdx)
{
    endIdx = endIdx < width*height ? endIdx : width*height;
    for(int pi=startIdx; pi<endIdx; pi++)
    {
        std::vector<Ray> rays = sampleEyePath(camRays[pi]);
        nv::vec3f sampleColor(0, 0, 0);
#if !USE_CONNECTION
        sampleColor = rays.back().importance * rays.back().radiance;
#else
        unsigned seed = rays.back().seed;
        for(unsigned ri=1; ri<rays.size(); ri++)
        {
            Ray inRay = rays[ri];
            inRay.dir = rays[ri-1].dir;
            inRay.importance = rays[ri-1].importance;
            std::vector<Ray> lightRays = scene->generateLightRays(seed);
            for(unsigned li=0; li<lightRays.size(); li++)
            {
                if(length(inRay.radiance) == 0)
                    sampleColor += scene->connect(inRay, lightRays[li]);
            }
        }
        if(rays.size() <= 2 || rays[rays.size()-2].dirSampleType == RAY_SAMPLE_DEFINITE)
            sampleColor += rays.back().importance * rays.back().radiance;
#endif
        pixels[pi] = (pixels[pi] * nSamples + sampleColor)  / float(nSamples+1);
    }
}

void Tracer::trace()
{
    std::vector<Ray> pixelRays = camera->generateRays();
    
#if USE_TBB
    tbb_parallel_task::set_values(this, pixelRays);
    parallel_for(tbb::blocked_range<size_t> (0, width*height, 1024), tbb_parallel_task());
    nSamples++;
#else
    unsigned step = ceil(width*height/double(nPassesPerSample));
    unsigned index = passNum * step;
    traceRange(pixelRays, index, index+step);
    passNum++;
    if(passNum == nPassesPerSample)
    {
        nSamples++;
        passNum = 0;
    }
#endif
    
}

Tracer::~Tracer()
{
    delete scene;
    delete camera;
}
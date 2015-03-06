//
//  main.cpp
//  RayTracer
//
//  Created by Weilun Sun on 2/20/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#include "macros.h"
#include "Tracer.h"

#if !USE_GL

int main(int argc, const char * argv[]) {
    unsigned width = 700;
    unsigned height = 700;
    
    Tracer tracer;
    tracer.setImageSize(width, height);
    tracer.trace();
    WritePPM(width, height, "out.ppm", tracer.getPixels());
    
    return 0;
}

#else

#include <GLUT/GLUT.h>
#include <cstdlib>
#include <sys/time.h>

unsigned width = 512;
unsigned height = 512;

Tracer tracer;

timeval ts, te;

unsigned nFrames = 0;
double fps;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(width, height, GL_RGB, GL_FLOAT, (float*)tracer.getPixels().data());
    glutSwapBuffers();
}

void update()
{
    tracer.trace();
    nFrames++;
    if(nFrames == 5)
    {
        gettimeofday(&te, NULL);
        fps = nFrames / double((te.tv_sec-ts.tv_sec)*1e6 + te.tv_usec - ts.tv_usec) * 1e6;
        gettimeofday(&ts, NULL);
        char title[128];
        sprintf(title, "Ray Tracer (%0.1ffps)", fps);
        glutSetWindowTitle(title);
        nFrames = 0;
    }
    glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
        case 's':
            WritePPM(width, height, "out.ppm", tracer.getPixels());
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    tracer.setImageSize(width, height);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Ray Tracer");
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyPress);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gettimeofday(&ts, NULL);
    glutMainLoop();
}

#endif

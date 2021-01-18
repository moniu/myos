#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "terminal.h"
#include "math.h"

struct g_point
{
    float x,y,z;
};

struct g_triangle
{
    struct g_point p[3];
    char color;
};

struct matrix4x4
{
    float m[4][4];
};

void graphic_function(float angle);

void plot_line(int x0, int y0, int x1, int y1, uint8_t color);
void plot(int x, int y, uint8_t color);

void MultiplyMatrixVector();
void DrawTriangle(struct g_triangle t);
void FillTriangle(struct g_triangle t);

uint8_t get_fill(float a);

#endif
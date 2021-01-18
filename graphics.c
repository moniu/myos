#include "graphics.h"
#include "serial.h"
#include "terminal.h"
#include "vga.h"

#define SCREEN_WIDTH (VGA_SCREEN_WIDTH)
#define SCREEN_HEIGHT (VGA_SCREEN_HEIGHT)

void graphic_function(float angle)
{
    struct g_triangle mesh[] = {
        { {{-0.2675, -0.1491, 0.0}, {-0.2675, 0.1466, 0.0, }, {0.2699, 0.1466, 0.0, }}, 48 },
        { {{0.2699, 0.1466, 0.0}, {0.2699, -0.1491, 0.0, }, {-0.2675, -0.1491, 0.0, }}, 48 },
        { {{-0.2675, -0.1491, 1.0}, {0.2699, -0.1491, 1.0, }, {0.2699, 0.1466, 1.0, }}, 48 },
        { {{0.2699, 0.1466, 1.0}, {-0.2675, 0.1466, 1.0, }, {-0.2675, -0.1491, 1.0, }}, 48 },
        { {{-0.2675, -0.1491, 0.0}, {0.2699, -0.1491, 0.0, }, {0.2699, -0.1491, 1.0, }}, 48 },
        { {{0.2699, -0.1491, 1.0}, {-0.2675, -0.1491, 1.0, }, {-0.2675, -0.1491, 0.0, }}, 48 },
        { {{0.2699, -0.1491, 0.0}, {0.2699, 0.1466, 0.0, }, {0.2699, 0.1466, 1.0, }}, 48 },
        { {{0.2699, 0.1466, 1.0}, {0.2699, -0.1491, 1.0, }, {0.2699, -0.1491, 0.0, }}, 48 },
        { {{0.2699, 0.1466, 0.0}, {-0.2675, 0.1466, 0.0, }, {-0.2675, 0.1466, 1.0, }}, 48 },
        { {{-0.2675, 0.1466, 1.0}, {0.2699, 0.1466, 1.0, }, {0.2699, 0.1466, 0.0, }}, 48 },
        { {{-0.2675, 0.1466, 0.0}, {-0.2675, -0.1491, 0.0, }, {-0.2675, -0.1491, 1.0, }}, 48 },
        { {{-0.2675, -0.1491, 1.0}, {-0.2675, 0.1466, 1.0, }, {-0.2675, 0.1466, 0.0, }}, 48 },
        { {{-0.1455, -0.1499, 0.8963}, {-0.1455, -0.1499, 0.8192, }, {-0.0724, -0.1499, 0.8963, }}, 144 },
        { {{-0.0724, -0.1499, 0.8192}, {-0.0724, -0.1499, 0.8963, }, {-0.1455, -0.1499, 0.8192, }}, 144 },
        { {{0.0961, -0.1504, 0.8963}, {0.0961, -0.1504, 0.8232, }, {0.1691, -0.1504, 0.8963, }}, 144 },
        { {{0.1691, -0.1504, 0.8232}, {0.1691, -0.1504, 0.8963, }, {0.0961, -0.1504, 0.8232, }}, 144 },
        { {{-0.1049, -0.1504, 0.658}, {-0.1208, -0.1504, 0.6423, }, {0.001, -0.1504, 0.5515, }}, 16 },
        { {{-0.0149, -0.1504, 0.5358}, {0.001, -0.1504, 0.5515, }, {-0.1208, -0.1504, 0.6423, }}, 16 },
        { {{-0.0237, -0.1504, 0.5464}, {-0.0094, -0.1504, 0.532, }, {0.0897, -0.1504, 0.6597, }}, 16 },
        { {{0.1041, -0.1504, 0.6454}, {0.0897, -0.1504, 0.6597, }, {-0.0094, -0.1504, 0.532, }}, 16 },



    };


    float fNear = 0.1f;
	float fFar = 100.0f;
	float fFov = 30.0f;
	float fAspectRatio = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
	float fFovRad = 0.5f / tan(fFov * 0.5f / 180 * MATH_PI);

    float dp, l;

    struct g_point vCamera={0,-1,0};

    struct matrix4x4 matProj;

    matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.5f;
	matProj.m[3][3] = 0.0f;

    struct matrix4x4 matRotZ, matRotX;

		// Rotation Z
    matRotZ.m[0][0] = cos(angle);
    matRotZ.m[0][1] = sin(angle);
    matRotZ.m[1][0] = -sin(angle);
    matRotZ.m[1][1] = cos(angle);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;

    // Rotation X
    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = cos(2+sin(angle)/3);
    matRotX.m[1][2] = sin(2+sin(angle)/3);
    matRotX.m[2][1] = -sin(2+sin(angle)/3);
    matRotX.m[2][2] = cos(2+sin(angle)/3);
    matRotX.m[3][3] = 1;

    int i;
    struct g_triangle tri, triProjected, triTranslated, triRotatedZ, triRotatedZX;
    struct g_point normal, line1, line2, light_direction;
    for (i=0;i<20;i++)
    {
        tri = mesh[i];


        // Rotate in Z-Axis
        MultiplyMatrixVector(&tri.p[0], &triRotatedZ.p[0], &matRotZ);
        MultiplyMatrixVector(&tri.p[1], &triRotatedZ.p[1], &matRotZ);
        MultiplyMatrixVector(&tri.p[2], &triRotatedZ.p[2], &matRotZ);

        // Rotate in X-Axis
        MultiplyMatrixVector(&triRotatedZ.p[0], &triRotatedZX.p[0], &matRotX);
        MultiplyMatrixVector(&triRotatedZ.p[1], &triRotatedZX.p[1], &matRotX);
        MultiplyMatrixVector(&triRotatedZ.p[2], &triRotatedZX.p[2], &matRotX);

        // Offset into the screen
        triTranslated = triRotatedZX;
        triTranslated.p[0].z = triRotatedZX.p[0].z + 2.0f;
        triTranslated.p[1].z = triRotatedZX.p[1].z + 2.0f;
        triTranslated.p[2].z = triRotatedZX.p[2].z + 2.0f;

        triTranslated.p[0].y = triRotatedZX.p[0].y + 0.5f;
        triTranslated.p[1].y = triRotatedZX.p[1].y + 0.5f;
        triTranslated.p[2].y = triRotatedZX.p[2].y + 0.5f;

		line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
		line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
		line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

		line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
		line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
		line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

		normal.x = line1.y * line2.z - line1.z * line2.y;
		normal.y = line1.z * line2.x - line1.x * line2.z;
		normal.z = line1.x * line2.y - line1.y * line2.x;

        // It's normally normal to normalise the normal
        l = sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
        normal.x /= l; normal.y /= l; normal.z /= l;

        //if (normal.z < 0)
        if(normal.x * (triTranslated.p[0].x - vCamera.x) + 
            normal.y * (triTranslated.p[0].y - vCamera.y) +
            normal.z * (triTranslated.p[0].z - vCamera.z) < 0.0f )
        {

            light_direction.x=0.0f;
            light_direction.y=0.0f;
            light_direction.z=-1.0f;
            l = sqrtf(light_direction.x*light_direction.x + light_direction.y*light_direction.y + light_direction.z*light_direction.z);
            light_direction.x /= l; light_direction.y /= l; light_direction.z /= l;

            dp = normal.x * light_direction.x + normal.y * light_direction.y + normal.z * light_direction.z;

            triTranslated.color = (char)(tri.color+dp*8.0+8);

            // Project triangles from 3D --> 2D
            MultiplyMatrixVector(&triTranslated.p[0], &triProjected.p[0], &matProj);
            MultiplyMatrixVector(&triTranslated.p[1], &triProjected.p[1], &matProj);
            MultiplyMatrixVector(&triTranslated.p[2], &triProjected.p[2], &matProj);
            
            triProjected.color = triTranslated.color;

            // Scale into view
            triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
            triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
            triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
            triProjected.p[0].x *= 0.5f * (float)SCREEN_WIDTH;
            triProjected.p[0].y *= 0.5f * (float)SCREEN_HEIGHT;
            triProjected.p[1].x *= 0.5f * (float)SCREEN_WIDTH;
            triProjected.p[1].y *= 0.5f * (float)SCREEN_HEIGHT;
            triProjected.p[2].x *= 0.5f * (float)SCREEN_WIDTH;
            triProjected.p[2].y *= 0.5f * (float)SCREEN_HEIGHT;

            // Rasterize triangle
            FillTriangle(triProjected);

        }
    }



}

void plot_line(int x0, int y0, int x1, int y1, uint8_t color)
{
    int dx =  abs(x1-x0);
    int sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0);
    int sy = y0<y1 ? 1 : -1;
    int err = dx+dy;  /* error value e_xy */
    int e2;
    while (true)   /* loop */
    {

        plot(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2*err;
        if (e2 >= dy) /* e_xy+e_x > 0 */
        {
            err += dy;
            x0 += sx;
        } 
        if (e2 <= dx) /* e_xy+e_y < 0 */
        {
            err += dx;
            y0 += sy;
        }
    }
}

void plot(int x, int y, uint8_t color)
{
    if (x<0 || x>=SCREEN_WIDTH || y<0 || y>=SCREEN_HEIGHT) 
        return;
    else
    {
        //serial_printf("%d %d\n",x,y);
        vga_write_pixel(x,y,color);
    }
}

void MultiplyMatrixVector(struct g_point *i, struct g_point *o, struct matrix4x4 *m)
{
    o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
    o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
    o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
    float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

    if (w != 0.0f)
    {
        o->x /= w; o->y /= w; o->z /= w;
    }
}

void DrawTriangle(struct g_triangle t)
{
    plot_line(t.p[0].x, t.p[0].y, t.p[1].x, t.p[1].y, t.color);
    plot_line(t.p[0].x, t.p[0].y, t.p[2].x, t.p[2].y, t.color);
    plot_line(t.p[2].x, t.p[2].y, t.p[1].x, t.p[1].y, t.color);
}

void FillTriangle(struct g_triangle t)
{
    //struct g_triangle frame = t;
    //frame.color=0;
    //frame.fill='#';
    int x0 = round(t.p[0].x);
    int x1 = round(t.p[1].x);
    int x2 = round(t.p[2].x);
    int y0 = round(t.p[0].y);
    int y1 = round(t.p[1].y);
    int y2 = round(t.p[2].y);
    int dx =  abs(x1-x0);
    int sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0);
    int sy = y0<y1 ? 1 : -1;
    int err = dx+dy;  /* error value e_xy */
    int e2;
    while (true)   /* loop */
    {

        plot_line(x0, y0, x2, y2, t.color);
        if (x0 == x1 && y0 == y1)break;
        e2 = 2*err;
        if (e2 >= dy) /* e_xy+e_x > 0 */
        {
            err += dy;
            x0 += sx;
        } 
        if (e2 <= dx) /* e_xy+e_y < 0 */
        {
            err += dx;
            y0 += sy;
        }
    };
    //DrawTriangle(frame);
}

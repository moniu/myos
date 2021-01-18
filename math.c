#include "math.h"

int max(int a, int b)
{
    if (a>b) return a;
    return b;
}
float maxf(float a, float b)
{
    if (a>b) return a;
    return b;
}
int min(int a, int b)
{
    if (a<b) return a;
    return b;
}
float minf(float a, float b)
{
    if (a<b) return a;
    return b;
}




int abs(int a)
{
    return a>=0?a:-a;
}
float fabs(float a)
{
    return a>=0.0?a:-a;
}
int pow(int a, int e)
{
    int result = 1;
    while(e--!=0)
        result*=a;
    return result;
}
float powf(float a, int e)
{
    float result = 1;
    while(e--!=0)
        result*=a;
    return result;
}
int sign(int a)
{
    if(a==0) return 0;
    return a>0?1:-1;
}

int factorial(int x)
{
    int result = 1;
    for (int i=1;i<=x;i++)
        result *= i;
    return result;
}
float factorialf(int x)
{
    int result = 1;
    for (int i=1;i<=x;i++)
        result *= i;
    return result;
}


float ceil(float a)
{
    if (a==(int)a) return floor(a);
    else return floor(a+1);
}
float floor(float a)
{
    return (float)((int)a);
}
float round(float a)
{
    if (a-floor(a) < ceil(a)-a) return floor(a);
    else return ceil(a);
}

/*
float sin(float a)
{
    while (a>=360) a-=360;
    while (a<0) a+=360;
    if (a>=180)
    {
        a-=180;
        return -(4*a*(180-a))/(40500-a*(180-a));
    }
        
    else
        return (4*a*(180-a))/(40500-a*(180-a));
}*/
float sin(float a)
{
    while (a>=MATH_PI) a-=MATH_PI*2;
    while (a<-MATH_PI) a+=MATH_PI*2;
    float sum;
    float frac;
    sum = 0;
    sum += a;
    frac = (a/6)*(a*a);
    sum -= frac;
    frac *= (a*a)/20;
    sum += frac;
    frac *= (a*a)/49;
    sum -= frac;
    return sum;
}
/*
float cos(float a)
{
    while (a>=360) a-=360;
    while (a<0) a+=360;
    if (a>=180)
    {
        a-=180;
        return -(32400-4*a*a)/(32400+a*a);
    }
    else
        return (32400-4*a*a)/(32400+a*a);
}
*/

float cos(float a)
{
    while (a>=MATH_PI) a-=MATH_PI*2;
    while (a<-MATH_PI) a+=MATH_PI*2;
    float sum;
    float frac;
    sum = 1;
    frac = (a/2)*a;
    sum -= frac;
    frac *= (a*a)/12;
    sum += frac;
    frac *= (a*a)/30;
    sum -= frac;
    return sum;
}


float tan(float a)
{
    return sin(a)/cos(a);
}

float sqrtf(float n) 
{
      float an = (float)n/2.0, 

            anplus1 = (an + (float)n/an ) / 2.0;

      float EPS = 0.00001;

      while( (fabs(an - anplus1)) >= EPS) {

            an = anplus1;

            anplus1 = (an + (float)n/an ) / 2.0;
      }                

   return anplus1;
}
#include "SimFunctions.h"
#include <math.h>

SimFunctions::SimFunctions()
{
    //ctor
}

SimFunctions::~SimFunctions()
{
    //dtor
}

/*
THIS IS WHERE THE NEW VELOCITY OF THE FALLER GOES
THIS IS HOW EVERYTHING WORKS
OH YES
*/
float SimFunctions::delS(float t, float v)
{
    return 0;
}

float SimFunctions::fallFactor(Pitch& p)
{
    return (2*p.getd())/p.getL();
}

float SimFunctions::baseTension(Pitch& p)
{
    float g = 9.8;
    return sqrt(2*p.getk()*fallFactor(p)*p.getM()*g);
}




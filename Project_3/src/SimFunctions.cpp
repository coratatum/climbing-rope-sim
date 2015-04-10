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
double SimFunctions::delS(double t, double v)
{
    return 0;
}

double SimFunctions::fallFactor(Pitch& p)
{
    return (2*p.getd())/p.getL();
}

double SimFunctions::baseTension(Pitch& p)
{
    double g = 9.8;
    return sqrt(2*p.getk()*fallFactor(p)*p.getM()*g);
}

Eigen::VectorXd calcTensionRatios(Pitch& p)
{

}

Eigen::VectorXd calcIncrementalSlips(Pitch& p)
{

}

Eigen::VectorXd calcIncrementalStrains(Pitch& p)
{

}

Eigen::MatrixXd createC()
{

}




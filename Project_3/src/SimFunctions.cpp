#include "SimFunctions.h"
#include <math.h>

#define E 2.718218
#define G 9.8

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
*/
double SimFunctions::delS(double t, double v, Pitch& p)
{
    //for last runner
    double Sn = v*t;

    //for first runner, use special belay device case??

    return 0;
}

double SimFunctions::fallFactor(Pitch& p)
{
    return (2*p.getd())/p.getL();
}

double SimFunctions::baseTension(Pitch& p)
{
    //double g = 9.8;
    return sqrt(2*p.getk()*fallFactor(p)*p.getM()*G);
}

Eigen::VectorXd SimFunctions::calcTensionRatios(Pitch& p)
{
    //let coeff of friction be set here:
    double coeffFriction = 0.2;

    Eigen::VectorXd lap = p.calcLapAngles();
    Eigen::VectorXd exponent = lap*coeffFriction;

    int entriesCount = exponent.rows();
    Eigen::VectorXd ret(entriesCount);


    //loop through all but last value
    for(std::size_t i = 0; i < entriesCount; ++i)
    {
        ret[i] = exp(exponent[i]);
    }

    return ret;

}

Eigen::VectorXd SimFunctions::calcIncrementalSlips(Pitch& p)
{

}

Eigen::VectorXd SimFunctions::calcIncrementalStrains(Pitch& p)
{

}

Eigen::MatrixXd SimFunctions::createC()
{

}

double SimFunctions::calcCEntry()
{

}

Eigen::MatrixXd SimFunctions::createK(Pitch& p)
{

}

Eigen::VectorXd SimFunctions::createDelT(Pitch& p)
{

}

Eigen::VectorXd SimFunctions::calcSlipConditions(Pitch& p)
{
    //special case for belay

}

Eigen::VectorXd SimFunctions::createDelT0(Pitch& p)
{

}



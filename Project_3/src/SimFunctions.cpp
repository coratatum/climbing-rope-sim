#include "SimFunctions.h"
#include <math.h>

#define E 2.718218
#define G 9.80665

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
double SimFunctions::calcDelS(double v, Pitch& p)
{
    //for last runner
    double Sn = v*tInc;

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
    delS = (-1*L*(Ti+delT0)) * (L*K*C);
    return delS;
}

Eigen::VectorXd SimFunctions::calcIncrementalStrains(Pitch& p)
{
    delE = C*delS;
    return delE;
}

Eigen::MatrixXd SimFunctions::createC()
{
    Eigen::VectorXd mainD(delE.rows());
    Eigen::VectorXd upperD(delE.rows()+1);

    Eigen::MatrixXd ret(mainD.rows(),upperD.rows());
    ret.diagonal() = mainD;
    ret.diagonal(1) = upperD;
}

double SimFunctions::calcCEntry()
{

}

Eigen::MatrixXd SimFunctions::createK(Pitch& p)
{
    Eigen::MatrixXd i(delT0.rows(),delT0.rows());
    i.setIdentity(delT0.rows(),delT0.rows());
    K = p.k1 * i;
    return K;
}

Eigen::VectorXd SimFunctions::createDelT(Pitch& p)
{
    /*
    if(delT0 == null){
        createDelT0(p);
    }
    */
    delT = (p.k1*delE) + delT0;
    return delT;
}

Eigen::VectorXd SimFunctions::calcSlipConditions(Pitch& p)
{
    //special condition for belay device
    //EXTENSION
    double slipCond0;
    if(Ti[1] == critValue){
        int chance = 4;
        bool flag = true;
        while(flag){
            //random number generated in range of 1-chance
            //if mod 0, then "increase" chance and loop again
            //else, no more slip -> stop loop
            bool flag = false;
        }
        slipCond0 = 1;

    }
    //use delT
    //tensionRatios
    Eigen::VectorXd temp(Ti.rows());
    temp[0] = slipCond0;
    for(std::size_t i = 1; i < Ti.rows()-1; i++){
        if(Ti[i] == tensionRatios[i]*Ti[i+1]){
            //slip condition is -1
            temp[i] = -1;
            delT[i] = tensionRatios[i]*delT[i+1];
        } else if(Ti[i] == Ti[i+1]/tensionRatios[i]){
            temp[i] = 1;
            delT[i] = delT[i+1]/tensionRatios[i];
        } else {
            //slip condition is 0
            temp[i] = 0;
        }
    }

    slipConditions = temp;
    return temp;
}

Eigen::VectorXd SimFunctions::createDelT0(Pitch& p)
{
    double temp = (tInc/p.lambda);
    int n = Ei.rows();
    Eigen::VectorXd ret(n);
    ret = ((p.k1*p.k2)*Ei) - (Ti*(p.k1+p.k2));
    ret = ret * temp;

    //set delT0??
    delT0 = ret;

    return ret;
}

Eigen::VectorXd SimFunctions::incrementalBaseTension()
{
    /*
    this.T;
    incT;
    */

}



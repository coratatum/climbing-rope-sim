#include "SimFunctions.h"
#include <math.h>
#include <iostream>

#define E 2.718218
#define G 9.80665

//using namespace Eigen;

SimFunctions::SimFunctions()
{
    //ctor
}

SimFunctions::SimFunctions(Pitch& p)
{
    //set the critical slip value (to arbitrary value)
    critValue = 10;
    tInc = .01; //time interval set to some arbitrary number
    tInc = .01; //time interval set to some arbitrary number

    T = baseTension(p);

    Ei = Eigen::VectorXd::Zero(p.calcLapAngles().rows()+1);
    Si = Eigen::VectorXd::Zero(p.calcLapAngles().rows()+1);
    //CHANGE:
    Ti = createTi(p);
    //
    delT0 = createDelT0(p);
    tensionRatios = calcTensionRatios(p);
    C = createC(p);
    L = createL(p);
    K = createK(p);


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
    //between .18 and .22 for rope on steel, according to the paper
    //he used .22 in experiments
    double coeffFriction = 0.22;

    Eigen::VectorXd lap = p.calcLapAngles();
    //std::cout<< lap;
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
    //uhhhhhhhhh nooooo..... this is all wrong -> solve system to get proper things
    //delS = (-1*L*(Ti+delT0)) * (L*K*C);
    return delS;
}

Eigen::VectorXd SimFunctions::calcIncrementalStrains(Pitch& p)
{
    delE = C*delS;
    return delE;
}

Eigen::MatrixXd SimFunctions::createC(Pitch& p)
{
    int s = p.getLapAngles().rows()+1; //number of carabiners
    //s++;

    Eigen::VectorXd mainD;
    mainD = Eigen::VectorXd::Zero(s);
    Eigen::VectorXd upperD;
    upperD = Eigen::VectorXd::Zero(s);



    mainD[0] = (-1-Ei[0])/(p.Li[0]-Si[0]);
    upperD[0] = (1+Ei[0])/(p.Li[0]-Si[0]);

    for(std::size_t i = 1; i < s; ++i)
    {
        mainD[i] = (-1-Ei[i])/(p.Li[i]+Si[i-1]-Si[i]);
        upperD[i] = (1+Ei[i])/(p.Li[i]+Si[i-1]-Si[i]);
        //std::cout <<(-1-Ei[i])<<'\n';
    }

    Eigen::MatrixXd ret(s,s+1);
    ret = Eigen::MatrixXd::Zero(s, s+1);
    ret.diagonal() = mainD;
    ret.diagonal(1) = upperD;
   // std::cout << "main: " <<'\n'<< mainD <<'\n';
   // std::cout << "upper: " << '\n'<< upperD <<'\n';

    return ret;
}

Eigen::MatrixXd SimFunctions::createL(Pitch& p)
{
    int s = p.getLapAngles().rows()+1;
    Eigen::VectorXd mainD;
    mainD = Eigen::VectorXd::Zero(s);
    Eigen::VectorXd upperD;
    upperD = Eigen::VectorXd::Zero(s-1); //??

    //case for 0 spot: uhm...
    if(Ti[0] >= critValue){
       // mainD[0] = 1;
       // upperD[0] = 1;

    } //else slip is 0, do nothing

    for(std::size_t i = 0; i < s-1; i++)
    {
        if(Ti[i] <= ((Ti[i+1])/(tensionRatios[i]))){
            mainD[i] = 1;
            upperD[i] = -1/tensionRatios[i];
        } else if(Ti[i] >= ((Ti[i+1])*(tensionRatios[i]))){
            mainD[i] = -1;
            upperD[i] = -1*tensionRatios[i];
        } //else { between, do nothing}
    }

    Eigen::MatrixXd ret(s,s);
    ret = Eigen::MatrixXd::Zero(s,s);
    ret.diagonal() = mainD;
    ret.diagonal(1) = upperD;

    return ret;
}

Eigen::MatrixXd SimFunctions::createK(Pitch& p)
{
    Eigen::MatrixXd i(delT0.rows(),delT0.rows());
    i.setIdentity(delT0.rows(),delT0.rows());
    Eigen::MatrixXd ret = p.k1 * i;
    return ret;
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

/*
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
*/

Eigen::VectorXd SimFunctions::createDelT0(Pitch& p)
{
    double temp = (tInc/p.lambda);
    int n = Ei.rows();
    Eigen::VectorXd ret(n);
    ret = ((p.k1*p.k2)*Ei) - (Ti*(p.k1+p.k2));
    ret = ret * temp;

    //set delT0??
    //delT0 = ret;

    return ret;
}

Eigen::VectorXd SimFunctions::incrementalBaseTension()
{
    /*
    this.T;
    incT;
    */

}

Eigen::VectorXd SimFunctions::createTi(Pitch& p)
{
    int n = p.getRopeSegments().rows();
    Eigen::VectorXd ret = Eigen::VectorXd::Zero(n);
   // Eigen::VectorXd segments = p.getRopeSegments();
    double l = p.getL();
    for(int i = 0; i < n; i++){
        ret[i] = (p.Li[i]/l) * T;
    }

    return ret;


}

Eigen::VectorXd SimFunctions::getEi()
{
    return Ei;
}

Eigen::VectorXd SimFunctions::getSi()
{
    return Si;
}

Eigen::VectorXd SimFunctions::getTensionRatios()
{
    return tensionRatios;
}

Eigen::MatrixXd SimFunctions::getC()
{
    return C;
}

Eigen::VectorXd SimFunctions::getTi()
{
    return Ti;
}

Eigen::VectorXd SimFunctions::getDelT0()
{
    return delT0;
}

Eigen::MatrixXd SimFunctions::getL()
{
    return L;
}

Eigen::MatrixXd SimFunctions::getK()
{
    return K;
}


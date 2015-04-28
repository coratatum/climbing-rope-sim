#include <Eigen/Core>
#include <iostream>
#include <Pitch.h>
#include <SimFunctions.h>
#include <math.h>
#include<Eigen/LU>

#define PI 3.14159265
using namespace std;
using namespace Eigen;

/**
Testing 1,2,3
*/


int main(){
    Pitch p = Pitch();
    cout << "Len: " << p.getL() << '\n';

    SimFunctions test = SimFunctions(p);
/*
    cout << "Ei: " << '\n';
    cout << test.getEi() <<'\n';
    cout << "Si: " << '\n';
    cout << test.getSi() <<'\n';
    cout << "Tension Ratios: " << '\n';
    cout << test.getTensionRatios() <<'\n';

    cout << "C: " << '\n';
    cout << test.getC() <<'\n';

    //std::cout << Ti;
    cout << "Ti: " << '\n';
    cout << test.getTi()<<'\n';

    cout << "L: " << '\n';
    cout << test.getL() <<'\n';

    cout << "K: " << '\n';
    cout << test.getK() <<'\n';

    cout << test.getL()*test.getK()*test.getC() << '\n';
    cout << "asdf: " << '\n';
    cout <<test.getDelT0() << endl;

    //Matrix<float,2,3> m = Matrix<float,2,3>::Random();
    MatrixXd m = test.getL()*test.getK()*test.getC();
    MatrixXd y = (-1)*(test.getL())*(test.getTi()+test.getDelT0());
    cout << "Here is the matrix m:" << endl << m << endl;
    cout << "Here is the matrix y:" << endl << y << endl;
    MatrixXd x = m.fullPivLu().solve(y);
    if((m*x).isApprox(y))
    {
        cout << "Here is a solution x to the equation mx=y:" << endl << x << endl;
    }
    else
        cout << "The equation mx=y does not have any solution." << endl;

    //have proper "slip" x:
    //calculate del E
    VectorXd delE1 = test.getC()*x;
    //VectorXd delE1 = VectorXd::Constant(y.rows(), 0);
    //delE1[0] = .05;
    cout << "delE1: " << '\n';
    cout << delE1 << endl;
    //now get delT
    VectorXd delT1 = (test.getK()*delE1) + test.getDelT0();
    cout << "delT1: " << '\n';
    cout << delT1 << endl;

    VectorXd newTi = delT1+test.getTi();
    cout << "newTi: " << '\n';
    cout << newTi << endl;


    test.Ei = delE1;
    test.
*/
    // mini sim test of some n rounds
    double time = 0;
    double vel = 9.8;
    for(int i = 0; i < 20; i++){
        MatrixXd m = test.getL()*test.getK()*test.getC();
        MatrixXd y = (-1)*(test.getL())*(test.getTi()+test.getDelT0());
        cout << "Here is the matrix m:" << endl << m << endl;
        cout << "Here is the matrix y:" << endl << y << endl;
        MatrixXd x = m.fullPivLu().solve(y);
        if((m*x).isApprox(y))
        {
            cout << "Here is a solution x to the equation mx=y:" << endl << x << endl;
        }
        else
            cout << "The equation mx=y does not have any solution." << endl;
        VectorXd delE1 = test.getC()*x;
        VectorXd delT1 = (test.getK()*delE1) + test.getDelT0();
        cout << "delT1: " << '\n';
        cout << delT1 << endl;
        //VectorXd newTi = delT1+test.getTi();

        int n = x.rows();
        cout << n << endl;
        VectorXd asdf = Eigen::VectorXd::Zero(n);
        asdf[n-1] = vel*test.tInc;
        x += asdf;
        test.setSi(x);
        test.setEi(delE1);
        test.incrementTi(delT1);
        test.createC(p);
        test.createL(p);
        time += test.tInc;
        vel = test.calcNewVelocity(vel,p);

        for(int i = 0; i < test.getTi().rows(); i++)
        {
            if (test.getTi()[i] < 0){
                //cout << "before: " << '\n';
                //cout << test.getTi()[i] << endl;
                double temp = test.getTi()[i];
                VectorXd z = Eigen::VectorXd::Zero(test.getTi().rows());
                z[i] = -1*temp;
                test.incrementTi(z);
                //cout << "after: " << '\n';
                //cout << test.getTi()[i] << endl;
            }
        }

        cout << "time: " << '\n';
        cout << time << endl;
        cout << "newTi: " << '\n';
        cout << test.getTi() << endl;
        cout << "velocity: " << vel << endl;
    }

    //std::cout << p.Li;

    return 0;
}

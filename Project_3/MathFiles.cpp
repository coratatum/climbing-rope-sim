#include <Eigen/Core>
#include <iostream>
#include <Pitch.h>
#include <SimFunctions.h>
#include <math.h>
#include<Eigen/LU>

#define PI 3.14159265
#define G 9.80665
using namespace std;
using namespace Eigen;

/**
Testing 1,2,3
*/


int main(){
    Pitch p = Pitch();
    cout << "Len: " << p.getL() << '\n';

    SimFunctions test = SimFunctions(p);

    //Simulation set up
    double time = 0;
    double vel = sqrt(2*G*p.getd())/2.0;
    for(int i = 0; i < 50; i++){
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

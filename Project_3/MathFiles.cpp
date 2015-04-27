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


    //std::cout << p.Li;

    return 0;
}

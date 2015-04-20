#include <Eigen/Core>
#include <iostream>
#include <Pitch.h>
#include <SimFunctions.h>
#include <math.h>

#define PI 3.14159265

/**
Testing 1,2,3
*/


int main(){
    Pitch p = Pitch();
    std::cout << "Len: " << p.getL() << '\n';

    SimFunctions test = SimFunctions(p);

    std::cout << "Ei: " << '\n';
    std::cout << test.getEi() <<'\n';
    std::cout << "Si: " << '\n';
    std::cout << test.getSi() <<'\n';
    std::cout << "Tension Ratios: " << '\n';
    std::cout << test.getTensionRatios() <<'\n';

    std::cout << "C: " << '\n';
    std::cout << test.getC() <<'\n';

    //std::cout << Ti;
    std::cout << "Ti: " << '\n';
    std::cout << test.getTi()<<'\n';

    std::cout << "L: " << '\n';
    std::cout << test.getL() <<'\n';

    //std::cout << p.Li;

    return 0;
}

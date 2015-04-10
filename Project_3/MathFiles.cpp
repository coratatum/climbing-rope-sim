#include <Eigen/Core>
#include <iostream>
#include <Pitch.h>
#include <math.h>

#define PI 3.14159265

/**
Testing 1,2,3
*/


int main(){
    std::cout << "hello" << " " << "world" <<'\n';
    std::cout << "line 2" << '\n';
    Pitch p = Pitch();
   // std::cout << std::fixed << std::setprecision(2) << 4.00 << '\n';
    std::cout << p.getL() << '\n';
    tuple<float,float> p1{0,0};
    tuple<float,float> p2{0,1};
    tuple<float,float> p3{0,2};
    std::cout<<p.lawOfCosines(p1,p2,p3)<<'\n';
    //std::cout<<(PI/2) << '\n';
    return 0;
}

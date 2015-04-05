#include <Eigen/Core>
#include <iostream>
#include <Pitch.h>


/*
float fallFactor(float d, float L){
    return (2*d)/L;
}

float baseTension(float F, float k, float M){
    float g = 9.80665; //gravity, m/s^2
    return sqrt(2*k*F*M*g);
}

array getSegmentLengths(std::array<> carabiners){
    //get dist b/w each pair of coords
    //put each Len in a matrix

    //do a similar process to get the angle between each segment
}

array angles(){

}

float maxTensionRatio(){

}

float getAngle(){
    //get angle between two things
    //input two lines??
    //4 points eh??

}

Matrix getIncrementalTenstion(){

}

Matrix calcStrain(){
    vector dS = -L(T+dT)/(LKC);
}
*/



int main(){
    std::cout << "hello" << " " << "world" <<'\n';
    std::cout << "line 2" << '\n';
    Pitch p = Pitch();
   // std::cout << std::fixed << std::setprecision(2) << 4.00 << '\n';
    std::cout << p.getRopeLength() << '\n';
    return 0;
}

#include "Pitch.h"
#include <Eigen/Core>

#include <math.h>

//has a matrix of carabiner spots
//has a k constant for rope
//has crit val for belay slip
//can calc new crit val for belay slip

//make a func to make a randomly generated pitch??


Pitch::Pitch()
{
    //ctor
    //Pitch::pitchGeometry = {{1,2},{1,2}};
    //Pitch::L = 4;
    pitchGeometry.push_back(make_tuple(1,2));

    //get the length of the live rope from the geometry
    //once this works, move and use to make the segment list
    //then sum the segment list to get the length
    double l = 0;
    tuple<double,double> prev;
    tuple<double,double> curr;
    vector<tuple<double,double>>::iterator it = pitchGeometry.begin();
    for(it; it != pitchGeometry.end(); ++it){
           l += get<0>((*it));
    }
    L = l;
}

Pitch::~Pitch()
{
    //dtor
}

vector<tuple<double,double>> Pitch::getPitchGeometry()
{
    //return pitch geo
    return Pitch::pitchGeometry;
}

vector<double> Pitch::getRopeSegments()
{
    vector<double> lengths;
    //return a vector of rope segment lengths
    tuple<double,double> prev {0,0}; //start at origin
    std::vector<tuple<double,double>>::iterator it;

    for(it = pitchGeometry.begin(); it != pitchGeometry.end(); ++it){
        /*
        double x = std::get<0>(*it) - std::get<0>(prev);
        double y = std::get<1>(*it) - std::get<1>(prev);
        double l = sqrt(x*x + y*y);
        */
        double l = distanceFormula(prev, *it);
        lengths.push_back(l);
        prev = *it; //reassign prev to curr coords for next iteration
    }
}

vector<double> Pitch::getRopeSegmentAngles()
{
    //get the angles
    //given 3 points, or two segments, get the angle between them
}

Eigen::VectorXd Pitch::calcLapAngles()
{
    //get the angles
    //given 3 points, or two segments, get the angle between them
}

double Pitch::calcRopeLength()
{
    double len = 0;
    //calculate from the pitch geometry
    return len;
}

double Pitch::getd()
{
    return d;
}

double Pitch::getk()
{
    return k;
}

double Pitch::getL()
{
    return L;
}

double Pitch::getM()
{
    return M;
}


/*
Private helper functions
*/

double Pitch::distanceFormula(tuple<double,double> p1, tuple<double,double> p2)
{
    double a = std::get<0>(p2) - std::get<0>(p1);
    double b = std::get<1>(p2) - std::get<1>(p1);
    double d = sqrt(a*a + b*b);
    return d;
}

double Pitch::lawOfCosines(tuple<double,double> p1, tuple<double,double> p2, tuple<double,double> p3)
{
    double a = distanceFormula(p2,p3);
    double b = distanceFormula(p1,p2);
    double c = distanceFormula(p1,p3);

    double numerator = (a*a) + (b*b) - (c*c);
    double denominator = 2*a*b;
    return acos(numerator/denominator);
}


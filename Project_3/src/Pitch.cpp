#include "Pitch.h"

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
    float l = 0;
    tuple<float,float> prev;
    tuple<float,float> curr;
    vector<tuple<float,float>>::iterator it = pitchGeometry.begin();
    for(it; it != pitchGeometry.end(); ++it){
           l += get<0>((*it));
    }
    L = l;
}

Pitch::~Pitch()
{
    //dtor
}

vector<tuple<float,float>> Pitch::getPitchGeometry()
{
    //return pitch geo
    return Pitch::pitchGeometry;
}

vector<float> Pitch::getRopeSegments()
{
    vector<float> lengths;
    //return a vector of rope segment lengths
    tuple<float,float> prev {0,0}; //start at origin
    std::vector<tuple<float,float>>::iterator it;

    for(it = pitchGeometry.begin(); it != pitchGeometry.end(); ++it){
        /*
        float x = std::get<0>(*it) - std::get<0>(prev);
        float y = std::get<1>(*it) - std::get<1>(prev);
        float l = sqrt(x*x + y*y);
        */
        float l = distanceFormula(prev, *it);
        lengths.push_back(l);
        prev = *it; //reassign prev to curr coords for next iteration
    }
}

vector<float> Pitch::getRopeSegmentAngles()
{
    //get the angles
    //given 3 points, or two segments, get the angle between them
}

float Pitch::calcRopeLength()
{
    float len = 0;
    //calculate from the pitch geometry
    return len;
}

float Pitch::getd()
{
    return d;
}

float Pitch::getk()
{
    return k;
}

float Pitch::getL()
{
    return L;
}

float Pitch::getM()
{
    return M;
}


/*
Private helper functions
*/

float Pitch::distanceFormula(tuple<float,float> p1, tuple<float,float> p2)
{
    float a = std::get<0>(p2) - std::get<0>(p1);
    float b = std::get<1>(p2) - std::get<1>(p1);
    float d = sqrt(a*a + b*b);
    return d;
}

float Pitch::lawOfCosines(tuple<float,float> p1, tuple<float,float> p2, tuple<float,float> p3)
{
    float a = distanceFormula(p2,p3);
    float b = distanceFormula(p1,p2);
    float c = distanceFormula(p1,p3);

    float numerator = (a*a) + (b*b) - (c*c);
    float denominator = 2*a*b;
    return acos(numerator/denominator);
}

#include "Pitch.h"


//has a matrix of carabiner spots
//has a k constant for rope
//has crit val for belay slip
//can calc new crit val for belay slip

//make a func to make a randomly generated pitch??




Pitch::Pitch()
{
    //ctor
    //Pitch::pitchGeometry = {{1,2},{1,2}};
    Pitch::L = 4;
}

Pitch::~Pitch()
{
    //dtor
}

std::vector<std::tuple<float>> Pitch::getPitchGeometry()
{
    //return pitch geo
    return Pitch::pitchGeometry;
}

std::vector<float> Pitch::getRopeSegments()
{
    //return a vector of rope segment lengths
}

std::vector<float> Pitch::getRopeSegmentAngles()
{
    //get the angles
}

float Pitch::getRopeLength()
{
    //calculate from the pitch geometry
    return Pitch::L;
}



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
    //Pitch::L = 4;
    pitchGeometry.push_back(std::make_tuple(1,2));

    //get the length of the live rope from the geometry
    //once this works, move and use to make the segment list
    //then sum the segment list to get the length
    float l = 0;
    std::tuple<float,float> prev;
    std::tuple<float,float> curr;
    std::vector<std::tuple<float,float>>::iterator it = pitchGeometry.begin();
    for(it; it != pitchGeometry.end(); ++it){
           l += std::get<0>((*it));
    }
    L = l;
}

Pitch::~Pitch()
{
    //dtor
}

std::vector<std::tuple<float,float>> Pitch::getPitchGeometry()
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
    //given 3 points, or two segments, get the angle between them
}

float Pitch::getRopeLength()
{
    //calculate from the pitch geometry
    return Pitch::L;
}



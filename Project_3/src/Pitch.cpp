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
    //return a vector of rope segment lengths
}

vector<float> Pitch::getRopeSegmentAngles()
{
    //get the angles
    //given 3 points, or two segments, get the angle between them
}

float Pitch::getRopeLength()
{
    //calculate from the pitch geometry
    return Pitch::L;
}



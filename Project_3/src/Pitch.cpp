#include "Pitch.h"
#include <Eigen/Core>

#include <math.h>

#define PI 3.14159265

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
    //implicit belay at 0,0
    /*Trial 1 */
    /*
    pitchGeometry.push_back(make_tuple(0,1));
    pitchGeometry.push_back(make_tuple(0,2));
    pitchGeometry.push_back(make_tuple(0,3));
    pitchGeometry.push_back(make_tuple(0,4));
    */
    /* Trial 2 */
    /*
    pitchGeometry.push_back(make_tuple(0,1));
    pitchGeometry.push_back(make_tuple(0,2));
    pitchGeometry.push_back(make_tuple(1,3));
    pitchGeometry.push_back(make_tuple(1,5));
    pitchGeometry.push_back(make_tuple(2,7));
    pitchGeometry.push_back(make_tuple(4,7.5));
    pitchGeometry.push_back(make_tuple(3,9));
    */
    /* Trial 3 */
    pitchGeometry.push_back(make_tuple(0,2));
    pitchGeometry.push_back(make_tuple(0,3));
    pitchGeometry.push_back(make_tuple(1,4));
    pitchGeometry.push_back(make_tuple(2,5));
    pitchGeometry.push_back(make_tuple(2,4));
    pitchGeometry.push_back(make_tuple(1,6));
    pitchGeometry.push_back(make_tuple(2,7));

    //get the length of the live rope from the geometry
    //once this works, move and use to make the segment list
    //then sum the segment list to get the length
    /*double l = 0;
    tuple<double,double> prev;
    tuple<double,double> curr;*/
    L = calcRopeLength();
    Li = getRopeSegments();
    M = 40; //kg
    k = 1;
    k1 = 35.0; //from paper
    k2 = 20.0; //from paper
    lambda = 3.0; //from paper
    lapAngles = calcLapAngles();
    d = calculateD();

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

Eigen::VectorXd Pitch::getRopeSegments()
{
    vector<double> lengths;
    //return a vector of rope segment lengths
    tuple<double,double> prev {0,0}; //start at origin
    std::vector<tuple<double,double>>::iterator it;
    int entriesCount = 0;

    for(it = pitchGeometry.begin(); it != pitchGeometry.end(); ++it){
        double l = distanceFormula(prev, *it);
        lengths.push_back(l);
        prev = *it; //reassign prev to curr coords for next iteration
        entriesCount++;
        //n++;
    }
    //Li = lengths;

    double* ptr = &lengths[0];
    Eigen::Map<Eigen::VectorXd> ret(ptr,entriesCount);
    return ret;
}

Eigen::VectorXd Pitch::calcLapAngles()
{
    //get the angles
    //given 3 points, or two segments, get the angle between them
    double angle = 0;
    int entriesCount = 0;
    std::vector<double> temp;

    //loop through all but last value
    for(std::size_t i = 0; i != pitchGeometry.size() - 1; ++i)
    {
        tuple<double,double> p1{0,0};
        tuple<double,double> p2;
        tuple<double,double> p3;

        if(i != 0){
           p1 = pitchGeometry[i-1];
        }
        p2 = pitchGeometry[i];
        p3 = pitchGeometry[i+1];

        angle = PI - lawOfCosines(p1,p2,p3);
        temp.push_back(angle);
        entriesCount++;
    }

    //Eigen::VectorXd ret(entriesCount);
    double* ptr = &temp[0];
    Eigen::Map<Eigen::VectorXd> ret(ptr,entriesCount);
    return ret;

    //"first" and last points are not carabiners and thus do not need angles associated with them
    //"first" is (0,0) to represent belayer
    //last point is the climber
    //all others need a coeff of friction, and this a lap angle

}

double Pitch::calcRopeLength()
{
    double len = 0;
    //calculate from the pitch geometry
    tuple<double,double> prev {0,0}; //start at origin
    std::vector<tuple<double,double>>::iterator it;

    for(it = pitchGeometry.begin(); it != pitchGeometry.end(); ++it){
        double l = distanceFormula(prev, *it);
        len += l;
        prev = *it; //reassign prev to curr coords for next iteration
        //n++;
    }

    return len;
}

double Pitch::calculateD()
{
    tuple<double,double> l = (pitchGeometry.back());
    tuple<double,double> l2 = (pitchGeometry.rbegin()[1]);

    return std::get<1>(l) - std::get<1>(l2);
}

/*
Eigen::VectorXd Pitch::incrementalBaseTension()
{

}
*/

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

Eigen::VectorXd Pitch::getLapAngles()
{
    return lapAngles;
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


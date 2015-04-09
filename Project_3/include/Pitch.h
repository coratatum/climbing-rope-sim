#ifndef PITCH_H
#define PITCH_H

#include <vector>
#include <tuple>

using namespace std;
/**
Holds all the info a climbing pitch might have
Most of the user input data is here
Should also do stuff like calculate the length of rope segments from the pitch geometry
*/

class Pitch
{
    public:
        Pitch();
        virtual ~Pitch();
        virtual vector<tuple<float,float>> getPitchGeometry();
        virtual vector<float> getRopeSegments();
        virtual vector<float> getRopeSegmentAngles();
        virtual float calcRopeLength();
        //new, implement
        virtual float getd();
        virtual float getk();
        virtual float getM();
        virtual float getL();

        virtual float lawOfCosines(tuple<float,float> p1, tuple<float,float> p2, tuple<float,float> p3);
        virtual float distanceFormula(tuple<float,float> p1, tuple<float,float> p2);


    protected:
    private:
        float M; //mass of leader
        float k; //
        float r; //runner radius

        float k1; //
        float k2; //
        float lambda; //
        vector<tuple<float,float>> pitchGeometry;
        //calculated from various other givens:

        float L; //total length of rope
        float d; //vert dist above last runner

        vector<float> tensionRatios;
        vector<float> lapAngles;
        vector<int> slipConditions;



};

#endif // PITCH_H

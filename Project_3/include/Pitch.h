#ifndef PITCH_H
#define PITCH_H

#include <vector>
#include <tuple>
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
        virtual std::vector<std::tuple<float,float>> getPitchGeometry();
        virtual std::vector<float> getRopeSegments();
        virtual std::vector<float> getRopeSegmentAngles();
        virtual float getRopeLength();

    protected:
    private:
        float M; //mass of leader
        float k; //
        float r; //runner radius

        float k1; //
        float k2; //
        float lambda; //
        std::vector<std::tuple<float,float>> pitchGeometry;
        //calculated from various other givens:

        float L; //total length of rope
        float d; //vert dist above last runner

        std::vector<float> tensionRatios;
        std::vector<float> lapAngles;
        std::vector<int> slipConditions;

};

#endif // PITCH_H

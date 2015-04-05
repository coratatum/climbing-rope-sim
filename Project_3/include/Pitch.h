#ifndef PITCH_H
#define PITCH_H

#include <vector>
#include <tuple>

class Pitch
{
    public:
        Pitch();
        virtual ~Pitch();
        virtual std::vector<std::tuple<float>> getPitchGeometry();
        virtual std::vector<float> getRopeSegments();
        virtual std::vector<float> getRopeSegmentAngles();
        virtual float getRopeLength();

    protected:
    private:
        float k; //
        float k1; //
        float k2; //
        std::vector<std::tuple<float>> pitchGeometry;
        float L; //total length of rope



        //array of tuples
        //for carabiners

};

#endif // PITCH_H

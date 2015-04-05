#ifndef PITCH_H
#define PITCH_H


class Pitch
{
    public:
        Pitch();
        virtual ~Pitch();
        virtual std::vector<std::array<float>> getPitchGeometry();
        virtual std::vector<float> getRopeSegments();
        virtual std::vector<float> getRopeSegmentAngles();

    protected:
    private:
        float k; //
        float k1; //
        float k2; //
        std::vector<std::array<float>> pitchGeometry;



        //array of tuples
        //for carabiners

};

#endif // PITCH_H

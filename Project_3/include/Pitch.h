#ifndef PITCH_H
#define PITCH_H

#include <vector>
#include <tuple>
#include <Eigen/Core>

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
        virtual vector<tuple<double,double>> getPitchGeometry();
        virtual vector<double> getRopeSegments();
        //virtual vector<double> getRopeSegmentAngles();
        virtual double calcRopeLength();
        virtual Eigen::VectorXd calcLapAngles();
        //uhmmmmm
        //virtual Eigen::VectorXd calcFrictionCoeffs();
        virtual double getd();
        virtual double getk();
        virtual double getM();
        virtual double getL();

        //virtual Eigen::VectorXd incrementalBaseTension();

        //helper funcs
        virtual double lawOfCosines(tuple<double,double> p1, tuple<double,double> p2, tuple<double,double> p3);
        virtual double distanceFormula(tuple<double,double> p1, tuple<double,double> p2);


    protected:
    private:
        double M; //mass of leader
        double k; //
        double r; //runner radius

        double k1; //
        double k2; //
        double lambda; //
        vector<tuple<double,double>> pitchGeometry;
        //calculated from various other givens:

        double L; //total length of rope
        double d; //vert dist above last runner

        vector<double> tensionRatios;
        vector<double> lapAngles;
        vector<int> slipConditions;

        double S; //crit tension
        //int numCarabiners; //number of carabiners (size of several arrays)



};

#endif // PITCH_H

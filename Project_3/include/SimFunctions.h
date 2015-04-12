#ifndef SIMFUNCTIONS_H
#define SIMFUNCTIONS_H

#include <Pitch.h>
#include <Eigen/Core>


/**
Will hold the functions that the simulation uses
Matrix calculations, etc.
Takes in a Pitch and its info to create the simulation
*/

class SimFunctions
{
    public:
        SimFunctions();
        virtual ~SimFunctions();
        virtual double fallFactor(Pitch& p);
        virtual double baseTension(Pitch& p);
       // virtual Matrix incrementalSlips(Pitch &p);
        virtual double delS(double t, double v, Pitch& p);
        virtual Eigen::VectorXd calcTensionRatios(Pitch& p);
        virtual Eigen::VectorXd calcIncrementalSlips(Pitch& p);
        virtual Eigen::VectorXd calcIncrementalStrains(Pitch& p);
        virtual Eigen::MatrixXd createC();

        //implement
        virtual Eigen::MatrixXd createK(Pitch& p);
        virtual Eigen::VectorXd createDelT(Pitch& p);
        virtual Eigen::VectorXd createDelT0(Pitch& p);

        virtual Eigen::VectorXd calcSlipConditions(Pitch& p);

        //private??
        virtual double calcCEntry();

    protected:
    private:
       // Pitch p; //have a pitch in the thing??
       double tInc; //how much to increase time at each time step
       Eigen::VectorXd tensionRatios;
       Eigen::VectorXd sIncs;
       Eigen::VectorXd eIncs;
       Eigen::MatrixXd C;

       Eigen::MatrixXd K;
       Eigen::VectorXd delT0;
       Eigen::VectorXd delT;

       Eigen::VectorXd slipConditions;



};

#endif // SIMFUNCTIONS_H

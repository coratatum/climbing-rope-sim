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
        SimFunctions(Pitch& p);
        virtual ~SimFunctions();
        virtual double fallFactor(Pitch& p);
        virtual double baseTension(Pitch& p);
        virtual Eigen::VectorXd incrementalBaseTension();
       // virtual Matrix incrementalSlips(Pitch &p);
        virtual double calcDelS(double v, Pitch& p);
        virtual Eigen::VectorXd calcTensionRatios(Pitch& p);
        virtual Eigen::VectorXd calcIncrementalSlips(Pitch& p);
        virtual Eigen::VectorXd calcIncrementalStrains(Pitch& p);
        virtual Eigen::MatrixXd createC(Pitch& p);
        virtual Eigen::MatrixXd createL(Pitch& p);

       // virtual


        //implement
        virtual Eigen::MatrixXd createK(Pitch& p);
        virtual Eigen::VectorXd createDelT(Pitch& p);
        virtual Eigen::VectorXd createDelT0(Pitch& p);

        //virtual Eigen::VectorXd calcSlipConditions(Pitch& p);

        //private??
        //virtual double calcCEntry();


        virtual Eigen::VectorXd getEi();
        virtual Eigen::VectorXd getSi();
        virtual Eigen::VectorXd getTensionRatios();
        virtual Eigen::MatrixXd getC();
        virtual Eigen::VectorXd getTi();
        virtual Eigen::MatrixXd getL();


    protected:
    private:
       // Pitch p; //have a pitch in the thing??
       double tInc; //how much to increase time at each time step
       Eigen::VectorXd tensionRatios;
       Eigen::VectorXd Si;
       Eigen::VectorXd Ei;
       Eigen::MatrixXd C;

       Eigen::MatrixXd K;
       Eigen::VectorXd delT0;
       Eigen::VectorXd delT;

       Eigen::VectorXd slipConditions;
       //Eigen::VectorXd incT; //incremental Tensions
       double T; //base tension
       Eigen::VectorXd delS;
       Eigen::VectorXd delE;
       Eigen::VectorXd Ti;
       Eigen::MatrixXd L;
       double critValue;



};

#endif // SIMFUNCTIONS_H

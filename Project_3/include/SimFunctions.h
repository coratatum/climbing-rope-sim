#ifndef SIMFUNCTIONS_H
#define SIMFUNCTIONS_H

#include <Pitch.h>


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
        virtual float fallFactor(Pitch& p);
        virtual float baseTension(Pitch& p);
       // virtual Matrix incrementalSlips(Pitch &p);
        virtual float delS(float t, float v);
    protected:
    private:
       // Pitch p; //have a pitch in the thing??
       float tInc; //how much to increase time at each time step

};

#endif // SIMFUNCTIONS_H

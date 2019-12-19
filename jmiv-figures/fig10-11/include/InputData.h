#ifndef EXPERIMENTS_INPUTDATA_H
#define EXPERIMENTS_INPUTDATA_H

#include <string>

#include "SCaBOliC/Core/model/ODRModel.h"


struct InputData
{
    enum Method{Simple,Probe};
    enum Mode{Concavities,Convexities};

    typedef SCaBOliC::Core::ODRModel::LevelDefinition LevelDefinition;


    InputData()
    {
        radius=5;
        gridStep=0.5;
        sqTermWeight=1.0;
        excludeOptPointsFromAreaComputation=false;
        repeatedImprovement=false;

        levels=1;
        iterations=10;
        optInApplication=false;
        ld = LevelDefinition::LD_CloserFromCenter;

        method = Probe;
        mode = Concavities;
    }

    std::string outputFolder;
    Method method;
    Mode mode;

    int iterations;
    bool optInApplication;
    int levels;
    LevelDefinition ld;


    double radius;
    double gridStep;
    double sqTermWeight;
    bool excludeOptPointsFromAreaComputation;
    bool repeatedImprovement;
};

#endif //EXPERIMENTS_INPUTDATA_H

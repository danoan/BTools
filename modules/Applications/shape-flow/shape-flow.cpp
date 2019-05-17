#include "model/InputReader.h"
#include "model/Types.h"
#include "control/FlowControl.h"



using namespace ShapeFlow;

int main(int argc, char* argv[])
{
    InputReader::InputData id = InputReader::readInput(argc,argv);

    FlowControl::BCConfigInput bcInput(id.radius,
                                       id.dtWeight,
                                       id.sqWeight,
                                       id.lgWeight,
                                       id.penalizationWeight,
                                       id.excludeOptPointsFromAreaComputation,
                                       id.repeatedImprovement,
                                       id.penalizationMode,
                                       id.optMethod);

    FlowControl::ODRConfigInput odrConfigInput(id.ac,
                                               id.cm,
                                               id.sm,
                                               id.radius,
                                               id.gridStep,
                                               id.levels,
                                               id.ld,
                                               id.neighborhood,
                                               id.seType,
                                               id.optRegionInApplication);

    FlowControl::BCFlowInput bcFlowInput(id.shape.name,
                                         bcInput,
                                         odrConfigInput,
                                         id.fp,
                                         id.iterations);


    FlowControl flow(bcFlowInput,
                     id.shape,
                     id.gridStep,
                     id.outputFolder,
                     std::cerr);

    return 0;
}


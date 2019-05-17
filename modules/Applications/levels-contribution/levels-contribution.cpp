#include "InputReader.h"
#include "FlowControl.h"

using namespace LevelsContribution;

int main(int argc, char* argv[])
{
    InputReader::InputData id = InputReader::readInput(argc, argv);
    bool repeatedImprovement = false;

    FlowControl::BCConfigInput bcInput(id.radius,
                                       0,
                                       1.0,
                                       0.0,
                                       0,
                                       id.excludeOptPointsFromAreaComputation,
                                       id.repeatedImprovement,
                                       id.penalizationMode,
                                       InputReader::InputData::OptMethod::Improve);

    FlowControl::ODRConfigInput odrConfigInput(InputReader::InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL,
                                               InputReader::InputData::ODRConfigInput::CountingMode::CM_PIXEL,
                                               InputReader::InputData::ODRConfigInput::SpaceMode::Pixel,
            id.radius,
            id.gridStep,
                    id.levels,
            id.ld,
            id.neighborhood,
            id.seType,
            id.opt);

    FlowControl::BCFlowInput bcFlowInput(id.shape.name,
                                         bcInput,
                                         odrConfigInput,
                                         InputReader::InputData::FlowProfile::SingleStepConvexities,
                                         id.iterations);


    FlowControl flow(bcFlowInput,
                     id.shape,
                     id.gridStep,
                     id.outputFolder,
                     id.excludeOptPointsFromAreaComputation,
                     std::cerr);

    return 0;
}
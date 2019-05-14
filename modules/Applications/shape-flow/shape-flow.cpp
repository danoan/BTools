#include "model/InputReader.h"
#include "model/Types.h"
#include "control/FlowControl.h"



using namespace ShapeFlow;

std::string resolveShapeName(Shape shape)
{
    if(shape==Shape::Triangle) return "triangle";
    else if(shape==Shape::Square) return "square";
    else if(shape==Shape::Pentagon) return "pentagon";
    else if(shape==Shape::Heptagon) return "heptagon";
    else if(shape==Shape::Ball) return "ball";
    else if(shape==Shape::Ellipse) return "ellipse";
    else if(shape==Shape::Flower) return "flower";
    else return "";
}

int main(int argc, char* argv[])
{
    InputReader::InputData id = InputReader::readInput(argc,argv);

    FlowControl::BCConfigInput bcInput(id.radius,
                                       id.dtWeight,
                                       id.sqWeight,
                                       id.lgWeight,
                                       id.penalizationWeight,
                                       id.excludeOptPointsFromAreaComputation,
                                       id.penalizationMode,
                                       id.optMethod);

    FlowControl::ODRConfigInput odrConfigInput(id.ac,
                                               id.cm,
                                               id.sm,
                                               id.levels,
                                               id.radius,
                                               id.gridStep,
                                               id.ld,
                                               id.neighborhood,
                                               id.seType,
                                               id.optRegionInApplication);

    FlowControl::BCFlowInput bcFlowInput(resolveShapeName(id.shape),
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


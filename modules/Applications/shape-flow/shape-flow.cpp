#include "model/InputReader.h"
#include "model/Types.h"
#include "control/FlowControl.h"



using namespace ShapeFlow;

std::string resolveShapeName(Shape shape)
{
    if(shape==Shape::Triangle) return "Triangle";
    else if(shape==Shape::Square) return "Square";
    else if(shape==Shape::Pentagon) return "Pentagon";
    else if(shape==Shape::Heptagon) return "Heptagon";
    else if(shape==Shape::Ball) return "Ball";
    else if(shape==Shape::Ellipse) return "Ellipse";
    else if(shape==Shape::Flower) return "Flower";
    else return "";
}

int main(int argc, char* argv[])
{
    InputReader::InputData id;
    InputReader::readInput(id,argc,argv);

    FlowControl::BCConfigInput bcInput(id.radius,
                                       id.dtWeight,
                                       id.sqWeight,
                                       id.lgWeight,
                                       id.optMethod);

    FlowControl::ODRConfigInput odrConfigInput(id.ac,
                                  id.cm,
                                  id.sm,
                                  id.levels,
                                  id.ld,
                                  id.neighborhood,
                                  id.optRegionInApplication);

    FlowControl::BCFlowInput bcFlowInput(resolveShapeName(id.shape),
                                         bcInput,
                                         odrConfigInput,
                                         id.fp,
                                         id.iterations);


    FlowControl flow(bcFlowInput,
                     id.shape,
                     id.outputFolder,
                     std::cerr);

    return 0;
}


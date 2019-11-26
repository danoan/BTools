#include "BTools/reader/DCFReader.h"
#include "control/FlowControl.h"



using namespace ShapeFlow;
using namespace BTools::Reader;

int main(int argc, char* argv[])
{
    DCFReader::InputData id = DCFReader::readInput(argc,argv,"OUTPUT_FOLDER\n");

    std::string outputFolder;
    try
    {
        outputFolder = argv[argc-1];
    }catch(std::exception ex)
    {
        std::cerr << "Missing output_folder!\n";
        exit(1);
    }

    FlowControl::BCConfigInput bcInput(id.radius,
                                       id.dtWeight,
                                       id.sqWeight,
                                       id.lgWeight,
                                       id.excludeOptPointsFromAreaComputation,
                                       id.uniformPerimeter,
                                       0,
                                       id.optMethod,
                                       id.innerBallCoef,
                                       id.outerBallCoef);

    FlowControl::ODRConfigInput odrConfigInput(id.radius,
                                               id.gridStep,
                                               id.levels,
                                               id.ld,
                                               id.neighborhood,
                                               id.am,
                                               id.optRegionInApplication);


    FlowControl flow(bcInput,
                     odrConfigInput,
                     id.iterations,
                     id.shape,
                     id.gridStep,
                     outputFolder,
                     std::cerr);

    return 0;
}


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
                                       id.optMethod);

    FlowControl::ODRConfigInput odrConfigInput(id.radius,
                                               id.gridStep,
                                               id.levels,
                                               id.ld,
                                               id.neighborhood,
                                               id.optRegionInApplication);

    FlowControl::BCFlowInput bcFlowInput(id.shape.name,
                                         bcInput,
                                         odrConfigInput,
                                         id.fp,
                                         id.iterations);


    FlowControl flow(bcFlowInput,
                     id.shape,
                     id.gridStep,
                     outputFolder,
                     std::cerr);

    return 0;
}


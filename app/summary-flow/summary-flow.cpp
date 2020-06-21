#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/derivates/Misc.h>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>
#include <boost/filesystem/operations.hpp>

#include "summary-flow/input/InputData.h"
#include "summary-flow/input/InputReader.h"

#include "summary-flow/utils.h"
#include "summary-flow/control/OneImageFlow.h"

using namespace DGtal::Z2i;
using namespace SummaryFlow;

typedef std::set<SCell> LinelSet;

int main(int argc, char* argv[])
{
    InputData id = InputReader::readInput(argc,argv);


    boost::filesystem::path srcImagePath( id.flowImagesFolderPath );
    std::string name = srcImagePath.stem().string();

    boost::filesystem::path outputFilePath = id.outputFilePath;
    boost::filesystem::create_directories(outputFilePath.remove_filename());

    SummaryFlow::OneImageFlow oif(srcImagePath.string(),
            id.outputFilePath,
            id.imageExtension,
            id.drawInterval,
            id.colorScheme,
            id.iot,
            id.pixelMaskPath,
            id.dirsMaskPath,
            id.drawCenterBall,
            id.radius,
            id.h);

    return 0;
}
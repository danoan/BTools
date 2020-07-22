#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/writers/GenericWriter.h>
#include <DGtal/io/boards/Board2D.h>

#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>
#include <BTools/utils/digUtils.h>

#include "InputReader.h"

using namespace DGtal::Z2i;

using namespace SCaBOliC::Core;
using namespace BTools::Core;
using namespace RegionsOfInterest;

void saveODR(const ODRModel& ODR,std::string outputPath)
{
    DGtal::Board2D board;
    std::string specificStyle = ODR.original.className() + "/Paving";
    board << DGtal::SetMode(ODR.original.className(),"Paving");

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Blue, DGtal::Color::Blue));
    board << ODR.trustFRG;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Green, DGtal::Color::Green));
    board << ODR.optRegion;

    DigitalSet appRegion = ODR.applicationRegionInn;
    appRegion += ODR.applicationRegionOut;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Red, DGtal::Color::Red));
    board << appRegion;

    DigitalSet optAppIntersection(ODR.optRegion.domain());
    DIPaCUS::SetOperations::setIntersection(optAppIntersection,ODR.optRegion,appRegion);

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Yellow, DGtal::Color::Yellow));
    board << optAppIntersection;

    board.saveSVG(outputPath.c_str(),200,200,10);

}

int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    SCaBOliC::Core::ODRPixels odrPixels(id.radius,id.gridStep,id.levels,
                                  id.levelDefinition,ODRPixels::NeighborhoodType::FourNeighborhood,id.optBand);


    ODRModel odrModel = odrPixels.createODR(ODRPixels::ApplicationMode::AM_AroundBoundary,
                                          BTools::Utils::resolveShape(id.shape,id.gridStep),
                                          false);


    boost::filesystem::path p(id.outputFilepath);
    boost::filesystem::create_directories(p.remove_filename());
    saveODR(odrModel,id.outputFilepath);

    return 0;
}

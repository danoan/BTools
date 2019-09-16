#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>
#include <BTools/reader/DCFReader.h>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

#include <boost/filesystem.hpp>
#include <DGtal/io/writers/GenericWriter.h>


using namespace DGtal::Z2i;

using namespace SCaBOliC::Core;
using namespace BTools::Core;
using namespace BTools::Reader;

typedef DCFReader::Shape Shape;
typedef DCFReader::ShapeType ShapeType;

ODRInterface& getFactory(const DCFReader::InputData& id)
{
    ODRConfigInput odrConfigInput(id.radius,id.gridStep,id.levels,
            id.ld,id.neighborhood,id.optRegionInApplication);

    return ODRPool::get(odrConfigInput);
}

IFlowProfile& getProfile(const DCFReader::InputData& id)
{
    return FlowPool::getFlow(id.fp,id.optRegionInApplication);
}

DigitalSet getShape(Shape shape,double gridStep)
{
    int radius=20;
    if(shape.type==ShapeType::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
    else if(shape.type==ShapeType::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
    else if(shape.type==ShapeType::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
    else if(shape.type==ShapeType::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
    else if(shape.type==ShapeType::Wave) return DIPaCUS::Shapes::wave(gridStep,1200,radius*3,radius*6,0.01);
    else
    {
        cv::Mat img = cv::imread(shape.imagePath,CV_8UC1);
        Domain domain( DGtal::Z2i::Point(0,0), DGtal::Z2i::Point(img.cols-1,img.rows-1) );
        DigitalSet ds(domain);
        DIPaCUS::Representation::CVMatToDigitalSet(ds,img,1);
        return ds;
    }
}

void saveODR(const ODRModel& ODR,std::string outputPath)
{
    DGtal::Board2D board;
    std::string specificStyle = ODR.original.className() + "/Paving";
    board << DGtal::SetMode(ODR.original.className(),"Paving");

//    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Silver));
//    board << ODR.trustBKG;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Blue, DGtal::Color::Blue));
    board << ODR.trustFRG;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Green, DGtal::Color::Green));
    board << ODR.optRegion;

    DigitalSet appRegion = ODR.applicationRegionIn;
    appRegion += ODR.applicationRegionOut;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Red, DGtal::Color::Red));
    board << appRegion;

    DigitalSet optAppIntersection(ODR.optRegion.domain());
    DIPaCUS::SetOperations::setIntersection(optAppIntersection,ODR.optRegion,appRegion);

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Yellow, DGtal::Color::Yellow));
    board << optAppIntersection;

    board.saveSVG(outputPath.c_str(),200,200,10);

}

DCFReader::InputData defaultValues()
{
    DCFReader::InputData id;

    id.radius=3;
    id.neighborhood= ODRConfigInput::NeighborhoodType::FourNeighborhood;
    id.ld = ODRConfigInput::LevelDefinition::LD_CloserFromCenter;

    id.am = ODRModel::ApplicationMode::AM_AroundBoundary;

    id.levels=3;
    id.optRegionInApplication = false;

    id.shape = Shape(ShapeType::Square);
    id.gridStep = 1.0;

    return id;
}

int main(int argc, char* argv[])
{
    DCFReader::InputData id = DCFReader::readInput(argc,argv,"OUTPUT_FILEPATH\n",defaultValues);

    std::string outputFilePath;
    try
    {
        outputFilePath = argv[argc-1];
    }catch(std::exception ex)
    {
        std::cerr << "Missing output_filepath!\n";
        exit(1);
    }



    SCaBOliC::Core::ODRPixels odrPixels(id.radius);

    ODRModel odrModel = odrPixels.createODR(flowStepConfig.applicationMode(),
                                          getShape(id.shape,id.gridStep),
                                          id.optRegionInApplication);


    boost::filesystem::path p(outputFilePath);
    boost::filesystem::create_directories(p.remove_filename());
    saveODR(odrModel,outputFilePath);

    return 0;
}

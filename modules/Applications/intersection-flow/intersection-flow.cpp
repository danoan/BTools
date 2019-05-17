#include <unistd.h>

#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>

#include "SCaBOliC/Core/ODRModel.h"
#include "SCaBOliC/Core/ODRInterface.h"

#include "BTools/core/pool/ODRPool.h"
#include "BTools/core/model/input/ODRConfigInput.h"

#include "BTools/utils/imgUtils.h"
#include "BTools/utils/strUtils.h"

#include "Types.h"

using namespace IntersectionFlow;
using namespace BTools::Core;
using namespace SCaBOliC::Core;
using namespace DGtal::Z2i;

struct InputData
{
    InputData()
    {
        gridStep=1.0;
        radius = 3.0;
        shape = Shape::Square;
        profile = IFlowProfile::FlowProfile::SingleStepConvexities;
    }
    std::string outputFolder = "";

    int iterations;
    double gridStep;
    double radius;
    IFlowProfile::FlowProfile profile;

    Shape shape;
};

void usage(char* argv[])
{
    std::cout << "Usage: " << argv[0]
              << "[-i Max Iterations default 10] \n"
                 "[-S Shape (triangle square pentagon heptagon ball ellipse ball dumbell). Default: square\n"
                 "[-h Grid step (default:1.0)]\n"
                  "FLOW_OUTPUT_FOLDER \n";
}

InputData readInput(int argc, char* argv[])
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"S:r:h:i:p:"))!=-1 )
    {
        switch(opt)
        {
            case 'i':
            {
                id.iterations = std::atoi(optarg);
                break;
            }
            case 'S':
            {
                if(strcmp(optarg,"triangle")==0) id.shape = Shape::Triangle;
                else if(strcmp(optarg,"square")==0) id.shape = Shape::Square;
                else if(strcmp(optarg,"pentagon")==0) id.shape = Shape::Pentagon;
                else if(strcmp(optarg,"heptagon")==0) id.shape = Shape::Heptagon;
                else if(strcmp(optarg,"ball")==0) id.shape = Shape::Ball;
                else if(strcmp(optarg,"ellipse")==0) id.shape = Shape::Ellipse;
                else if(strcmp(optarg,"flower")==0) id.shape = Shape::Flower;
                else throw std::runtime_error("Unrecognized shape!");
                break;
            }
            case 'r':
            {
                id.radius = std::atof(optarg);
                break;
            }
            case 'h':
            {
                id.gridStep = std::atof(optarg);
                break;
            }
            case 'p':
            {
                if(strcmp(optarg,"single")==0 ) id.profile = IFlowProfile::FlowProfile::SingleStepConvexities;
                else if(strcmp(optarg,"double")==0 ) id.profile = IFlowProfile::FlowProfile::DoubleStep;
                else throw std::runtime_error("Flow profile not recognized");
                break;
            }
            default:
            {
                usage(argv);
                exit(1);
            }
        }
    }

    id.outputFolder = argv[optind++];

    return id;
}

DigitalSet getShape(Shape shape,double gridStep)
{
    int radius=20;
    if(shape==Shape::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
    else if(shape==Shape::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
    else if(shape==Shape::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
    else if(shape==Shape::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
    else if(shape==Shape::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
    else if(shape==Shape::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
    else if(shape==Shape::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
}

DigitalSet flow(ODRPool::ODRInterface& odrFactory,
                const DigitalSet& shape,
                ODRModel::OptimizationMode optMode)
{
    ODRModel odr = odrFactory.createODR(optMode,
                                        ODRModel::ApplicationMode::AM_InternRange,
                                        shape,
                                        false);

    const DigitalSet& appRegion = odr.applicationRegion;
    const DigitalSet& optRegion = odr.optRegion;

    DIPaCUS::Misc::DigitalBallIntersection DBIO = odrFactory.handle()->intersectionComputer(optRegion);

    DigitalSet temp(shape.domain());
    DigitalSet optIntersection(optRegion.domain());
    for(auto it=appRegion.begin();it!=appRegion.end();++it)
    {
        DBIO(temp,*it);
        optIntersection.insert(temp.begin(),temp.end());
    }

    DigitalSet solution(shape.domain());
    solution.insert(odr.trustFRG.begin(),odr.trustFRG.end());
    for(auto it=optRegion.begin();it!=optRegion.end();++it)
    {
        if(optIntersection(*it))
        {
            solution.insert(*it);
        }
    }

    return solution;
}

int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    ODRConfigInput odrConfigInput(ODRConfigInput::ApplicationCenter::AC_PIXEL,
                                  ODRConfigInput::CountingMode::CM_PIXEL,
                                  ODRConfigInput::SpaceMode::Pixel,
                                  id.radius,
                                  id.gridStep,
                                  1,
                                  ODRConfigInput::LevelDefinition::LD_FartherFromCenter,
                                  ODRConfigInput::NeighborhoodType::FourNeighborhood,
                                  ODRConfigInput::StructuringElementType::RECT,
                                  false);


    ODRPool::ODRInterface& odrFactory = BTools::Core::ODRPool::get(odrConfigInput);
    ODRModel::OptimizationMode optMode;
    DigitalSet shape = getShape(id.shape,id.gridStep);

    boost::filesystem::create_directories(id.outputFolder);

    int it=0;
    while(it<id.iterations)
    {
        if(id.profile==IFlowProfile::SingleStepConvexities) optMode = ODRModel::OptimizationMode::OM_CorrectConvexities;
        else if(it%2==0) optMode = ODRModel::OptimizationMode::OM_CorrectConvexities;
        else optMode = ODRModel::OptimizationMode::OM_CorrectConcavities;

        DigitalSet partialSolution = flow(odrFactory,shape,optMode);

        if(optMode==ODRModel::OptimizationMode::OM_CorrectConcavities) shape.assignFromComplement(partialSolution);
        else shape = partialSolution;

        BTools::Utils::exportImageFromDigitalSet(shape,id.outputFolder + "/" + BTools::Utils::nDigitsString(it,4) + ".pgm" );
        ++it;
    }

    return 0;
}
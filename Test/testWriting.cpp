#include <opencv2/core/types.hpp>

#include <BTools/model/instance/Study.h>
#include "BTools/DataWriter.h"


using namespace BTools::Model;

cv::Rect randomRect()
{
    int x1 = (int) rand()%100;
    int x2 = (int) rand()%100;
    int y1 = (int) rand()%100;
    int y2 = (int) rand()%100;

    return( cv::Rect( cv::Point(x1,y1),cv::Point(x2,y2) ) );
}

int main()
{
    typedef BinOCS::BoundaryCorrection::ODRConfigInput ODRConfigInput;
    typedef BinOCS::BoundaryCorrection::IFlowProfile::FlowProfile FlowProfile;

    srand(time(NULL));

    std::vector<Study> vectorOfStudies;

    int numVariation = 4;
    int numStudies = 4;

    ODRConfigInput odrConfigInput(ODRConfigInput::ApplicationCenter::AC_PIXEL,
                                  ODRConfigInput::CountingMode::CM_PIXEL,
                                  ODRConfigInput::SpaceMode::Pixel,
                                  3,
                                  ODRConfigInput::NeighborhoodType::FourNeighborhood);

    double curvatureWeight[numVariation] = {0.25,0.5,1.0,2.0};
    for(int i=0;i<numStudies;++i)
    {
        Study study;
        study.studyName = "ROI-" + std::to_string(i+1) + "/" + std::to_string(numVariation);
        for (int j = 0; j < numVariation; ++j)
        {

            BCFlowInput::BCConfigInput bcInput(3,
                                         1.0,
                                         curvatureWeight[j],
                                         1.0,
                                         BCFlowInput::BCConfigInput::QPBOSolverType::Probe);

            BCFlowInput bcFlowInput("alpha = " + std::to_string(curvatureWeight[j]),
                                    bcInput,
                                    odrConfigInput,
                                    FlowProfile::DoubleStep,
                                    5);

            Instance::SeedSequenceInput seedInput;
            seedInput.imgFilePath = "aaa.jpg";
            seedInput.vectorOfROI.push_back(randomRect());

            OptOutput output(bcFlowInput,seedInput);
            output.unlabeled = random()%20;
            output.MDCAElasticaValue = ( (double) random()/RAND_MAX*10 );
            output.IIElasticaValue = ( (double) random()/RAND_MAX*10 );
            output.optEnergyValue = ( (double) random()/RAND_MAX*10 );

            study.vectorOfOptOutput.push_back(output);
        }
        vectorOfStudies.push_back(study);
    }

    for(int i=0;i<numStudies;++i)
    {
        const Study& currStudy = vectorOfStudies[i];
        BTools::DataWriter::write(currStudy,std::cout);
    }


    return 0;
}
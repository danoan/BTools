
#include <BinOCS/Lab/model/input/ROICorrectionInput.h>
#include <BinOCS/Lab/model/instance/GeneralInstance.h>
#include <iostream>

using namespace BinOCS::Lab::Model;

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
    srand(time(NULL));

    typedef GeneralInstance<ROICorrectionInput> MyInstance;
    std::vector<MyInstance> vectorOfInstances;

    int numROIPerInput = 4;
    int numInstances = 1;
    const int numVariations = 4;



    double curvatureWeight[numVariations] = {0.25,0.5,1.0,2.0};
    for(int i=0;i<numInstances;++i)
    {
        GeneralInstance<ROICorrectionInput> instance(
                "Image-" + std::to_string(i+1), numROIPerInput );

        for (int j = 0; j < numVariations; ++j)
        {
            ROICorrectionInput roicInput("alpha = " + std::to_string(curvatureWeight[j]));
            roicInput.roiInput.imgFilePath = "aaa.jpg";

            roicInput.roiInput.vectorOfROI.push_back(randomRect());

            roicInput.bcInput.solverType = BCorrectionInput::QPBOSolverType::ImproveProbe;
            roicInput.bcInput.estimatingBallRadius = 3;
            roicInput.bcInput.dataTermWeight = 1.0;
            roicInput.bcInput.sqTermWeight = curvatureWeight[j];
            roicInput.bcInput.lengthTermWeight = 1.0;
            roicInput.bcInput.maxIterations = 5;

            std::vector<OptOutput> ROIOutput;
            for (int k = 0; k < numROIPerInput; ++k)
            {
                OptOutput output;
                output.unlabeled = random()%20;
                output.MDCAElasticaValue = ( (double) random()/RAND_MAX*10 );
                output.IIElasticaValue = ( (double) random()/RAND_MAX*10 );
                output.optEnergyValue = ( (double) random()/RAND_MAX*10 );

                ROIOutput.push_back(output);
            }

            instance.vectorOfInput.push_back(roicInput);
            instance.vectorOfOutput.push_back(ROIOutput);
        }
        vectorOfInstances.push_back(instance);
    }

    for(int i=0;i<numInstances;++i)
    {
        vectorOfInstances[i].write(std::cout);
    }


    return 0;
}
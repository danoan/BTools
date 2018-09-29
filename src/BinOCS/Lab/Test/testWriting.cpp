#include <BinOCS/Lab/model/instance/GeneralInstance.h>
#include <BinOCS/Lab/model/input/SeedCorrectionInput.h>

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

    typedef GeneralInstance<SeedCorrectionInput> MyInstance;
    std::vector<MyInstance> vectorOfInstances;

    int numROIPerInput = 4;
    int numInstances = 1;
    const int numVariations = 4;



    double curvatureWeight[numVariations] = {0.25,0.5,1.0,2.0};
    for(int i=0;i<numInstances;++i)
    {
        GeneralInstance<SeedCorrectionInput> instance(
                "Image-" + std::to_string(i+1), numROIPerInput );

        for (int j = 0; j < numVariations; ++j)
        {
            SeedCorrectionInput seedcInput("alpha = " + std::to_string(curvatureWeight[j]));
            seedcInput.seedInput.imgFilePath = "aaa.jpg";

            seedcInput.seedInput.vectorOfROI.push_back(randomRect());

            seedcInput.bcInput.solverType = BCorrectionInput::QPBOSolverType::ImproveProbe;
            seedcInput.bcInput.estimatingBallRadius = 3;
            seedcInput.bcInput.dataTermWeight = 1.0;
            seedcInput.bcInput.sqTermWeight = curvatureWeight[j];
            seedcInput.bcInput.lengthTermWeight = 1.0;
            seedcInput.bcInput.maxIterations = 5;

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

            instance.vectorOfInput.push_back(seedcInput);
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
#include "DatasetControl.h"

using namespace BTools::Application;

template<typename TInstanceProfile>
void DatasetControl::runFlowOnDataset(const std::string &datasetPathStr,
                                      BCFlowInput bcFlowInputModel,
                                      const std::string &outputFolder)
{
    typedef TInstanceProfile MyInstanceProfile;
    assert(boost::filesystem::is_directory(datasetPathStr));

    boost::filesystem::path datasetPath(datasetPathStr);
    boost::filesystem::directory_iterator di(datasetPath);

    while(di!=boost::filesystem::directory_iterator())
    {
        if(di->path().extension()==".txt")
        {
            std::string dataPath = di->path().string();
            std::string imageName = di->path().stem().string();

            SeedSequenceInput seedInput = DataReader::read(dataPath);


            boost::filesystem::path outputPath(outputFolder);
            outputPath.append(imageName);
            boost::filesystem::create_directories(outputPath);

            MyInstanceProfile instanceProfile;

            BTools::Model::Study study;
            study.studyName = instanceProfile.profileIdentifier() + "Study";


            int totalSeed = seedInput.numSeed();

            SelectorOutput selectorOutput;
            selectorOutput.baseImage = cv::imread(seedInput.imgFilePath,cv::IMREAD_COLOR);

            while (instanceProfile.fillInstance(bcFlowInputModel))
            {
                for (int i = 0; i < totalSeed; ++i)
                {
                    OptOutput output(bcFlowInputModel,seedInput);
                    seedInput.getSelector(selectorOutput,i);

                    BTools::Application::FromSeedControl(output,
                                                         seedInput.imgFilePath,
                                                         bcFlowInputModel,
                                                         selectorOutput,
                                                         outputPath.string());

                    study.vectorOfOptOutput.push_back(output);
                }

            }

            std::ofstream ofs( (outputPath.string() + "/" + instanceProfile.profileIdentifier() + "values.txt").c_str() );
            DataWriter::write(study,ofs);

            ofs.close();
        }

        di++;
    }


}

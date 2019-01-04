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


            MyInstanceProfile instanceProfile;
            boost::filesystem::path outputPath(outputFolder);
            outputPath.append(imageName);
            outputPath.append("Profile-" + instanceProfile.profileIdentifier());

            BTools::Model::Study study;
            study.studyName = instanceProfile.profileIdentifier() + "Study";


            int totalSeed = seedInput.numSeed();

            SelectorOutput selectorOutput;
            selectorOutput.baseImage = cv::imread(seedInput.imgFilePath,CV_LOAD_IMAGE_COLOR);

            int instanceNum=0;
            while (instanceProfile.fillInstance(bcFlowInputModel))
            {
                for (int i = 0; i < totalSeed; ++i)
                {
                    boost::filesystem::path currentOutputPath(outputPath);
                    currentOutputPath.append("Instance-"+std::to_string((instanceNum)));
                    currentOutputPath.append("ROI-"+std::to_string(i));

                    boost::filesystem::create_directories(currentOutputPath);

                    OptOutput output(bcFlowInputModel,seedInput);
                    seedInput.getSelector(selectorOutput,i);

                    BTools::Application::FromSeedControl(output,
                                                         seedInput.imgFilePath,
                                                         bcFlowInputModel,
                                                         selectorOutput,
                                                         currentOutputPath.string());

                    study.vectorOfOptOutput.push_back(output);
                }
                instanceNum++;
            }

            std::ofstream ofs( (outputPath.string() + "/" + instanceProfile.profileIdentifier() + "values.txt").c_str() );
            DataWriter::write(study,ofs);

            ofs.close();
        }

        di++;
    }


}

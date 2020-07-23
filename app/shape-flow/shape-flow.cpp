#include <ostream>

#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>

#include <BTools/api/api.h>
#include <BTools/utils/digUtils.h>
#include <BTools/utils/strUtils.h>
#include <BTools/utils/timer.h>

#include "model/MockDistribution.h"
#include "io/DataWriter.h"
#include "io/InputReader.h"
#include "utils.h"

using namespace ShapeFlow;

typedef DGtal::Z2i::DigitalSet DigitalSet;

typedef BTools::Core::ModelParameters ModelParameters;
typedef BTools::Core::BCInput BCInput;

typedef DataWriter::TableEntry TableEntry;

struct ExtParameters{
  ExtParameters(std::ostream& osLog, const std::string& shapeName, const std::string& outputFolder)
      :osLog(osLog),
       shapeName(shapeName),
       outputFolder(outputFolder){}

  std::ostream& osLog;
  std::string shapeName;
  std::string outputFolder;
  std::vector<TableEntry> entries;
};


void callback(BTools::API::CallbackData&& data, ExtParameters& extParams) {
  switch (data.event) {
    case BTools::API::Event::Start:
      extParams.entries.push_back(TableEntry(data.bcInput.modelParameters,
                                             data.solution, std::to_string(data.iteration)));

      BTools::Utils::Timer::start();
      extParams.osLog << "Flow Start: " << extParams.shapeName << "\n";
      extParams.osLog << "Iterations (" << data.bcInput.maxIterations << "): ";

      if (extParams.outputFolder != "") {
        boost::filesystem::create_directories(extParams.outputFolder);
        std::string initialImagePath = extParams.outputFolder + "/" + BTools::Utils::nDigitsString(0, 4) + ".pgm";
        cv::imwrite(initialImagePath, data.bcInput.imageData.grabcutImage);
      }
      break;
    case BTools::API::Event::Iteration:extParams.osLog << "|";
      extParams.entries.push_back(TableEntry(data.bcInput.modelParameters,
                                             data.solution, std::to_string(data.iteration)));

      if (data.bcInput.displayEachIteration) {
        cv::Mat imageOutput = cv::Mat::zeros(data.bcInput.imageData.inputImage.rows,
                                             data.bcInput.imageData.inputImage.cols,
                                             CV_8UC1);

        DIPaCUS::Representation::digitalSetToCVMat(imageOutput, data.solution.outputDS);
        cv::imshow(data.windowName, imageOutput);
        cv::waitKey(10);
      }

      if (extParams.outputFolder != "") {
        std::string
            currImagePath = extParams.outputFolder + "/" + BTools::Utils::nDigitsString(data.iteration, 4) + ".pgm";
        BTools::Utils::exportImageFromDigitalSet(data.solution.outputDS,
                                                 data.bcInput.imageData.inputDomain,
                                                 currImagePath);
      }

      Utils::checkBounds(data.solution.outputDS, data.solution.outputDS.domain());

      break;
    case BTools::API::Event::End:
      if (data.bcInput.displayEachIteration) {
        extParams.osLog << "The flow is done. Press any key to exit\n";
        cv::waitKey(0);
      }
      std::string endTimeStr = BTools::Utils::Timer::end();

      std::ofstream ofs(extParams.outputFolder + "/" + extParams.shapeName + ".txt");
      extParams.osLog << "\nWriting Results...";

      DataWriter::printTable(extParams.shapeName, extParams.entries, ofs);
      ofs << "\n\n#";
      ofs << endTimeStr;

      extParams.osLog << "\n\n";
  }

}

int main(int argc, char* argv[])
{
  InputData id = readInput(argc,argv);

  ModelParameters modelParameters(id.radius,
                                  id.gridStep,
                                  id.levels,
                                  id.levelDefinition,
                                  0,
                                  id.sqWeight,
                                  id.lgWeight,
                                  0);

  DigitalSet dsShape = BTools::Utils::resolveShape(id.shape,id.gridStep);
  cv::Mat initialImage = Utils::createInitialImage(dsShape,modelParameters);

  MockDistribution frDistr;
  MockDistribution bkDistr;

  BTools::Core::ImageData imageDataInput(frDistr,
                                         bkDistr,
                                         initialImage,
                                         initialImage);

  BTools::Core::BCInput bcInput(modelParameters,
                                imageDataInput,
                                id.iterations,
                                id.showIterations,
                                id.showProgress);

  std::ofstream ofs(id.outputFolder + "/input-data.txt");
  DataWriter::printFlowMetadata(modelParameters,*imageDataInput.inputDS,ofs);
  ofs.close();

  ExtParameters extParams(std::cerr,id.shape.name,id.outputFolder);
  BTools::API::bce(bcInput,
                   [&extParams](BTools::API::CallbackData&& data){ callback( std::move(data),extParams); } );

  return 0;
}


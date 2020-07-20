#include <ostream>

#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>


#include <DIPaCUS/base/Representation.h>
#include <SCaBOliC/Utils/Utils.h>
#include <SCaBOliC/Energy/model/Solution.h>

#include <BTools/core/model/input/BCInput.h>
#include <BTools/core/model/input/ModelParameters.h>
#include <BTools/core/model/input/ImageData.h>

#include <BTools/utils/imgUtils.h>
#include <BTools/utils/strUtils.h>
#include <BTools/utils/timer.h>

#include <BTools/api/api.h>
#include <InputReader.h>

#include "ShapeType.h"
#include "model/MockDistribution.h"
#include "control/DataWriter.h"

using namespace ShapeFlow;

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Space Space;
typedef DGtal::Z2i::Domain Domain;

typedef DGtal::Shapes<Domain> Shapes;
typedef DIPaCUS::Representation::Image2D Image2D;
typedef SCaBOliC::Energy::Solution EnergySolution;

typedef BTools::Core::ModelParameters ModelParameters;
typedef BTools::Core::BCInput BCInput;

typedef DataWriter::TableEntry TableEntry;

DigitalSet resolveShape(Shape shape,double gridStep)
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
  else if(shape.type==ShapeType::Bean) return DIPaCUS::Shapes::bean(gridStep,0,0,0.1);
  else
  {
    cv::Mat img = cv::imread(shape.imagePath,CV_8UC1);
    Domain domain( DGtal::Z2i::Point(0,0), DGtal::Z2i::Point(img.cols-1,img.rows-1) );
    DigitalSet ds(domain);
    DIPaCUS::Representation::CVMatToDigitalSet(ds,img,1);
    return ds;
  }
}

cv::Mat createInitialImage(const DigitalSet& _ds,const ModelParameters& modelParameters){
  int borderSize = 20;

  DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(borderSize,borderSize));
  Point dims = ds.domain().upperBound() - ds.domain().lowerBound() + Point(1,1);
  int cols = dims[0];
  int rows = dims[1];

  cv::Mat image = cv::Mat::zeros( rows,cols,CV_8UC1 );
  DIPaCUS::Representation::digitalSetToCVMat(image, ds);

  return image;
}

std::vector<DataWriter::TableEntry> initEntries(const ModelParameters& modelParameters, const DigitalSet& ds)
{
  std::vector<DataWriter::TableEntry> entries;

  EnergySolution firstSolution(ds.domain());
  firstSolution.outputDS = ds;
  firstSolution.energyValue = -1;
  entries.push_back(DataWriter::TableEntry(modelParameters,firstSolution,"0"));

  return entries;
}

void checkBounds(const DigitalSet& ds, const Domain& domain)
{
  Point lb,ub;
  ds.computeBoundingBox(lb,ub);

  if(lb(0) <= domain.lowerBound()(0)+1 ||
      lb(1) <= domain.lowerBound()(1)+1 ||
      ub(0) >= domain.upperBound()(0)-1 ||
      ub(1) >= domain.upperBound()(1)-1 )
  {
    throw std::runtime_error("Result image is too big.");
  }

  if(ds.size()<10) throw std::runtime_error("Result image is too small.");
}


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

void callback(BTools::API::CallbackData&& data, ExtParameters& extParams){
  switch(data.event){
    case BTools::API::Event::Start:
      extParams.entries = initEntries(data.bcInput.modelParameters,*data.bcInput.imageData.inputDS);

      BTools::Utils::Timer::start();
      extParams.osLog << "Flow Start: " << extParams.shapeName << "\n";
      extParams.osLog << "Iterations (" << data.bcInput.maxIterations << "): ";

      if(extParams.outputFolder!=""){
        boost::filesystem::create_directories(extParams.outputFolder);
        std::string initialImagePath = extParams.outputFolder + "/" + BTools::Utils::nDigitsString(0,4) + ".pgm";
        cv::imwrite(initialImagePath,data.bcInput.imageData.grabcutImage);
      }
      break;
    case BTools::API::Event::Iteration:
      extParams.osLog << "|";
      extParams.entries.push_back(TableEntry(data.bcInput.modelParameters,
                                             data.solution,std::to_string(data.iteration)));

      if(data.bcInput.displayEachIteration)
      {
        cv::Mat imageOutput = cv::Mat::zeros( data.bcInput.imageData.inputImage.rows,
                                              data.bcInput.imageData.inputImage.cols,
                                              CV_8UC1);

        DIPaCUS::Representation::digitalSetToCVMat(imageOutput,data.solution.outputDS);
        cv::imshow(data.windowName,imageOutput);
        cv::waitKey(10);
      }

      if(extParams.outputFolder!=""){
        std::string currImagePath = extParams.outputFolder + "/" + BTools::Utils::nDigitsString(data.iteration,4) + ".pgm";
        BTools::Utils::exportImageFromDigitalSet(data.solution.outputDS,data.bcInput.imageData.inputDomain,currImagePath);
      }

      checkBounds(data.solution.outputDS,data.solution.outputDS.domain());

      break;
    case BTools::API::Event::End:
      if(data.bcInput.displayEachIteration){
        extParams.osLog << "The flow is done. Press any key to exit\n";
        cv::waitKey(0);
      }
      std::string endTimeStr = BTools::Utils::Timer::end();

      std::ofstream ofs(extParams.outputFolder + "/" + extParams.shapeName + ".txt");
      extParams.osLog << "\nWriting Results...";

      DataWriter::printTable(extParams.shapeName,extParams.entries,ofs);
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

  DigitalSet dsShape = resolveShape(id.shape,id.gridStep);
  cv::Mat initialImage = createInitialImage(dsShape,modelParameters);

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

  ExtParameters extParams(std::cerr,id.shape.name,id.outputFolder);
  BTools::API::bce(bcInput,
                   [&extParams](BTools::API::CallbackData&& data){ callback( std::move(data),extParams); } );

  return 0;
}


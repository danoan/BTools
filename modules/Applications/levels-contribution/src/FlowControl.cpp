#include "FlowControl.h"

using namespace LevelsContribution;

FlowControl::DigitalSet FlowControl::resolveShape(Shape shape,double gridStep)
{
    int radius=20;
    if(shape.type==ShapeType::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
    else if(shape.type==ShapeType::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
    else if(shape.type==ShapeType::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
    else if(shape.type==ShapeType::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
    else
    {
        cv::Mat img = cv::imread(shape.imagePath,CV_8UC1);
        Domain domain( DGtal::Z2i::Point(0,0), DGtal::Z2i::Point(img.cols-1,img.rows-1) );
        DigitalSet ds(domain);
        DIPaCUS::Representation::CVMatToDigitalSet(ds,img,1);
        return ds;
    }
}

FlowControl::FlowControl(const BCFlowInput& bcFlowInput,
                         Shape shape,
                         double gridStep,
                         const std::string& outputFolder,
                         bool ignoreOptIntersection,
                         std::ostream& osLog)
{
    boost::filesystem::create_directories(outputFolder);

    DigitalSet ds = resolveShape(shape,gridStep);
    shapeFlow( ds,bcFlowInput,outputFolder,ignoreOptIntersection,osLog );
}

void FlowControl::createMDCAFigure(const DigitalSet& ds, const std::string& outputPath)
{
    typedef Curve::IncidentPointsRange::ConstCirculator AdapterCirculator;
    typedef DGtal::StabbingCircleComputer<AdapterCirculator> SegmentComputer;
    typedef DGtal::SaturatedSegmentation<SegmentComputer> Segmentation;

    Curve curve;
    DIPaCUS::Misc::computeBoundaryCurve(curve,ds);

    Curve::IncidentPointsRange intRange = curve.getIncidentPointsRange();

    DGtal::Board2D board;
    Point lb,ub;
    ds.computeBoundingBox(lb,ub);
    Domain domain(lb,ub);
    board << domain;
    board << curve;

    Segmentation seg( intRange.c(), intRange.c(), SegmentComputer() );


    int n = 0;
    for (Segmentation::SegmentComputerIterator it = seg.begin(),
                 itEnd = seg.end(); it != itEnd; ++it, ++n)
    {
        board << DGtal::SetMode(it->className(), "Annulus");
        board << (*it);
    }

    boost::filesystem::path p(outputPath);
    boost::filesystem::create_directories(p.remove_filename());

    //std::cerr << "# " << n << " arcs" << std::endl;
    board.saveSVG(outputPath.c_str());

}

void FlowControl::createLevelsContributionFigure(const BCAInput& bcaInput,
        const std::string& outputPath,
        bool ignoreOptIntersection)
{
    ODRInterface& odrFactory = ODRPool::get(bcaInput.odrConfigInput);

    ODRModel odr = odrFactory.createODR(ODRModel::OptimizationMode::OM_CorrectConvexities,
                                       ODRModel::ApplicationMode::AM_AroundBoundary,
                                       bcaInput.imageDataInput.inputDS,
                                       bcaInput.odrConfigInput.optInApplicationRegion);

    const DigitalSet& appRegion = odr.applicationRegion;
    const DigitalSet& optRegion = odr.optRegion;
    const DigitalSet& trustFRG = odr.trustFRG;

    std::map<DGtal::Z2i::Point,int> hits;
    for(auto it=optRegion.begin();it!=optRegion.end();++it) hits[*it] = 0;

    int ballArea = odrFactory.handle()->pixelArea();

    DigitalSet optIntersection(optRegion.domain());
    DigitalSet trustIntersection(optRegion.domain());


    DIPaCUS::Misc::DigitalBallIntersection DBIO = odrFactory.handle()->intersectionComputer(optRegion);
    DIPaCUS::Misc::DigitalBallIntersection DBIT = odrFactory.handle()->intersectionComputer(trustFRG);
    for(auto it=appRegion.begin();it!=appRegion.end();++it)
    {
        DBIO(optIntersection,*it);
        DBIT(trustIntersection,*it);
        for(auto ito=optIntersection.begin();ito!=optIntersection.end();++ito)
        {
            if(ignoreOptIntersection) hits[*ito] +=  pow( ( (ballArea - optIntersection.size())/2.0 - trustIntersection.size() ),2);
            else hits[*ito] +=  pow( (ballArea/2.0 - (trustIntersection.size() + optIntersection.size() ) ),2);
        }
        optIntersection.clear();
        trustIntersection.clear();
    }

    DGtal::Board2D board;
    std::string specificStyle = odr.original.className() + "/Paving";
    board << DGtal::SetMode(odr.original.className(),"Paving");

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Blue, DGtal::Color::Blue));
    board << odr.trustFRG;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Green, DGtal::Color::Green));
    board << odr.optRegion;

//    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Blue, DGtal::Color::Yellow));
//    board << odr.trustBKG;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Red, DGtal::Color::Red));
    board << odr.applicationRegion;

    DGtal::Z2i::Point pt = *appRegion.begin();

    DigitalSet ballDS = DIPaCUS::Shapes::ball(1.0,pt(0),pt(1),odrFactory.handle()->scaledRadius());
    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Cyan));
    board << ballDS;


//    int min,max;
//    min=hits[*optRegion.begin()];
//    max=hits[*optRegion.begin()];
//    for(auto it=optRegion.begin();it!=optRegion.end();++it)
//    {
//        if(hits[*it]<min) min = hits[*it];
//        if(hits[*it]>max) max = hits[*it];
//    }
//
//    std::cout << max << " :: " << min << std::endl;
//    if(min==max) max = min+1;
//
//    DGtal::GradientColorMap<double,
//            DGtal::ColorGradientPreset::CMAP_GRAYSCALE> cmap_jet(min,max);
//
//    board << DGtal::SetMode( optRegion.begin()->className(), "Paving" );
//    std::string pointStyle = optRegion.begin()->className() + "/Paving";
//
//    for(auto it=optRegion.begin();it!=optRegion.end();++it)
//    {
//        board << DGtal::CustomStyle(pointStyle, new DGtal::CustomColors(DGtal::Color::Black,
//                                                                           cmap_jet( hits[*it] )));
//        board << *it;
//    }

    boost::filesystem::path p(outputPath);
    boost::filesystem::create_directories(p.remove_filename());

    board.saveSVG(outputPath.c_str(),200,200,10);
}


FlowControl::BCAOutput FlowControl::boundaryCorrection(const BCFlowInput& bcFlowInput,
                                                       const cv::Mat& currentImage,
                                                       const std::string& baseFolder,
                                                       const std::string& suffix,
                                                       bool ignoreOptIntersection,
                                                       Point& translation)
{
    MockDistribution frDistr;
    MockDistribution bkDistr;

    ImageDataInput imageDataInput(frDistr,
                                  bkDistr,
                                  currentImage,
                                  currentImage);


    BCAInput bcaInput(bcFlowInput.bcInput,
                      imageDataInput,
                      bcFlowInput.odrConfigInput,
                      bcFlowInput.flowProfile);

    createLevelsContributionFigure(bcaInput,baseFolder + "/regions/" + suffix + ".svg",ignoreOptIntersection);
    createMDCAFigure(bcaInput.imageDataInput.inputDS,baseFolder + "/mdca/" + suffix + ".svg");
    BCAOutput bcaOutput(bcaInput);


    std::vector<IBCControlVisitor*> visitors = { new BTools::Visitors::PotentialMap(baseFolder + "/pmap/" + suffix+ ".svg") };

    BTools::Core::BCApplication BCA(bcaOutput,
                                    bcaInput,
                                    1,
                                    false,
                                    visitors.begin(),
                                    visitors.end());

    translation = imageDataInput.translation;
    delete visitors[0];

    return bcaOutput;
}

FlowControl::DigitalSet FlowControl::correctTranslation(const BCAOutput::EnergySolution& solution,
                                                        const cv::Mat& currentImage,
                                                        const Point& translation)
{
    DigitalSet translatedBackDS( Domain( Point(0,0),
                                         Point(currentImage.cols-1,currentImage.rows-1)
    ) );


    for (auto it = solution.outputDS.begin(); it != solution.outputDS.end(); ++it)
    {
        translatedBackDS.insert(*it + translation );
    }

    return translatedBackDS;
}

void FlowControl::checkBounds(const DigitalSet& ds, const Domain& domain)
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

void FlowControl::shapeFlow(const DigitalSet& _ds,
                            const BCFlowInput& bcFlowInput,
                            const std::string& outputFolder,
                            bool ignoreOptIntersection,
                            std::ostream& osLog)
{
    osLog << "Flow Start: " << bcFlowInput.inputName << "\n";
    osLog << "Iterations (" << bcFlowInput.maxIterations << "): ";


    boost::filesystem::create_directories(outputFolder);
    std::string currImagePath = outputFolder + "/" + BTools::Utils::nDigitsString(0,4) + ".pgm";
    std::ofstream os(outputFolder + "/" + bcFlowInput.inputName + ".txt");


    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(20,20));
    Domain flowDomain = ds.domain();


    BTools::Utils::exportImageFromDigitalSet(ds,flowDomain,currImagePath);

    cv::Mat img = cv::imread(currImagePath,cv::IMREAD_COLOR);
    Domain solutionDomain(Point(0,0),Point(img.cols-1,img.rows-1));

    int i=1;
    try
    {
        do
        {
            osLog << "|";

            std::vector<IBCControlVisitor*> visitors;
            cv::Mat currentImage = cv::imread(currImagePath,cv::IMREAD_COLOR);


            Point translation;
            std::string suffix = BTools::Utils::nDigitsString(i,4);
            BCAOutput bcaOutput = boundaryCorrection(bcFlowInput,currentImage,outputFolder,suffix,ignoreOptIntersection,translation);

            DigitalSet correctedSet = correctTranslation(bcaOutput.energySolution,currentImage,translation);
            checkBounds(correctedSet,flowDomain);


            currImagePath = outputFolder + "/" + BTools::Utils::nDigitsString(i,4) + ".pgm";
            BTools::Utils::exportImageFromDigitalSet(correctedSet,flowDomain,currImagePath);


            ++i;
        }while(i<bcFlowInput.maxIterations);
    }catch(std::exception ex)
    {
        osLog << ex.what() << "\n";
    }


}



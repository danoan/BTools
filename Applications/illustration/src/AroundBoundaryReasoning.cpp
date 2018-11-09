#include "../include/AroundBoundaryReasoning.h"

using namespace BTools::Application::Illustration;

int AroundBoundaryReasoning::createAndSavePicture(int radius,
                                                   const Point &center,
                                                   const DigitalSet &baseSet,
                                                   const std::string &outputFilePath)
{
    const Domain& domain = baseSet.domain();

    DigitalSet dsBall(domain);
    DIPaCUS::Misc::DigitalBallIntersection::digitalBall(dsBall,center,radius);

    DIPaCUS::Misc::DigitalBallIntersection dbi(radius,baseSet);
    DigitalSet dsIntersection(domain);
    dbi(dsIntersection,center);

    DGtal::Board2D board;


    board << domain
          << DGtal::CustomStyle(baseSet.className(),new DGtal::CustomColors(DGtal::Color::Black,DGtal::Color::Silver))
          << baseSet
          << DGtal::CustomStyle(baseSet.className(),new DGtal::CustomColors(DGtal::Color::Black,DGtal::Color::Blue) )
          << dsBall
          << DGtal::CustomStyle(baseSet.className(),new DGtal::CustomColors(DGtal::Color::Black,DGtal::Color::Cyan) )
          << dsIntersection;

    board.saveEPS(outputFilePath.c_str());

    return dsBall.size()/2.0 - dsIntersection.size();
}

void AroundBoundaryReasoning::createFromListOfCenter(Point listOfCenter[],
                                                     int radius,
                                                     const DigitalSet& dsBase,
                                                     const std::string& outputPrefix)
{
    double coefficient;
    double csum =0;
    std::ofstream ofs(outputPrefix + "-data.txt");
    for(int i=0;i<6;++i)
    {
        coefficient = createAndSavePicture(radius,
                                           listOfCenter[i],
                                           dsBase,
                                           outputPrefix + std::to_string(i) + ".eps");

        csum+=coefficient;
        ofs << coefficient << "\n";
    }

    if(csum>0) ofs << "Lack\n";
    else if(csum==0) ofs << "Balanced\n";
    else ofs << "Abundance\n";

    ofs.flush();
    ofs.close();
}

AroundBoundaryReasoning::AroundBoundaryReasoning(const std::string& outputFolder)
{
    boost::filesystem::create_directories(outputFolder);

    int estimatingBallRadius = 3.0;
    int squareSide = 10;
    int h = 1.0;

    MyNGon2D square(0,0,squareSide,4,3.1415/4.0);
    MyGaussDigitizer gd;

    Domain domain(square.getLowerBound() + 2*Point(-estimatingBallRadius,-estimatingBallRadius),
                  square.getUpperBound() + 2*Point(estimatingBallRadius,estimatingBallRadius)
    );
    gd.init(domain.lowerBound(),domain.upperBound(),h);
    gd.attach(square);

    Point tlc,mp;
    topLeftCorner(tlc,gd);
    mp = tlc;
    mp(1) -= squareSide/2.0;

    DigitalSet dsSquare(domain);
    for(auto it=domain.begin();it!=domain.end();++it)
    {
        if(gd(*it)) dsSquare.insert(*it);
    }

    Point listOfCenterTLC[6] = {tlc + Point(-3,0),tlc + Point(-2,0),tlc + Point(-1,0),
                                tlc+Point(1,0),tlc+Point(2,0),tlc+Point(3,0)};
    createFromListOfCenter(listOfCenterTLC,estimatingBallRadius,dsSquare,outputFolder + "/ab-tlc-");

    Point listOfCenterMP[6] = {mp + Point(-3,0),mp + Point(-2,0),mp + Point(-1,0),
                               mp + Point(1,0),mp+Point(2,0),mp+Point(3,0)};
    createFromListOfCenter(listOfCenterMP,estimatingBallRadius,dsSquare,outputFolder + "/ab-mp-");


}

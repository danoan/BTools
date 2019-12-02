#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/derivates/Misc.h>

#include <DGtal/io/writers/GenericWriter.h>

#include <boost/filesystem.hpp>
#include <DGtal/io/boards/Board2D.h>

typedef DIPaCUS::Representation::Image2D Image2D;
using namespace DGtal::Z2i;

int main(int argc,char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "Usage: jmiv-figR1 outputFolder";
        exit(1);
    }

    std::string outputFolder = argv[1];

    boost::filesystem::path p(outputFolder);
    boost::filesystem::create_directories(p);

    DigitalSet flower = DIPaCUS::Shapes::flower(0.1,0,0,10,4,2);
    Image2D flowerImg(flower.domain());
    DIPaCUS::Representation::digitalSetToImage(flowerImg,flower);
    DGtal::GenericWriter<Image2D>::exportFile(outputFolder+"/flower.pgm",flowerImg);

    std::vector<Point> extremePoints;
    extremePoints.push_back(*flower.begin());
    for(auto p:flower)
    {
        Point r = *extremePoints.begin();
        if(p[0] < r[0])
        {
            extremePoints.clear();
            extremePoints.push_back(p);
        }else if(p[0]==r[0])
        {
            extremePoints.push_back(p);
        }
    }

    std::sort(extremePoints.begin(),extremePoints.end(),[](const Point& p1, const Point& p2){ return p1[1]<p2[1]; });
    Point pMiddle = extremePoints[ extremePoints.size()/2 ];


    Curve c;
    DIPaCUS::Misc::computeBoundaryCurve(c,flower);
    KSpace kspace;
    const Domain& domain = flower.domain();
    kspace.init(domain.lowerBound(),domain.upperBound(),true);

    DGtal::Circulator<Curve::ConstIterator> cBegin(c.begin(),c.begin(),c.end());
    bool found=false;
    auto it = cBegin;
    do
    {
        for(auto p:kspace.sUpperIncident(*it))
        {
            Point pixel = kspace.sCoords(p);
            if(pixel==pMiddle)
            {
                found=true;
                break;
            }
        }

        if(found) break;

        ++it;
    }while(it!=cBegin);

    auto segBegin = it-17;
    auto segEnd = it+20;


    Point removeAfterPoint = pMiddle + Point(10,0);
    DigitalSet clippedFlower = flower;
    for(auto p:flower)
    {
        if(p[0]>removeAfterPoint[0]) clippedFlower.erase(p);
        if(p[1]>removeAfterPoint[1]+10) clippedFlower.erase(p);
        if(p[1]<removeAfterPoint[1]-10) clippedFlower.erase(p);
    }

    DGtal::Board2D board;
    board << DGtal::CustomStyle(flower.className() + "/paving",new DGtal::CustomColors(DGtal::Color::Silver,DGtal::Color::Silver));
    board << clippedFlower;

    board << DGtal::CustomStyle(segBegin->className(),new DGtal::CustomColors(DGtal::Color::Green,DGtal::Color::Green));
    for(auto it=segBegin;it!=segEnd;++it)
    {
        board << *it;
    }

    board << DGtal::CustomStyle(segBegin->className(),new DGtal::CustomColors(DGtal::Color::Blue,DGtal::Color::Blue));
    for(auto it=segBegin;it!=segEnd;++it)
    {
        for(auto p:kspace.sLowerIncident(*it))
        {
            board << p;
        }

    }


    board.saveEPS( (outputFolder + "/cellular-grid-illustration.eps").c_str() );


    return 0;
}
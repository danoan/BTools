#include <time.h>
#include <cstdlib>

#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/base/Shapes.h>

#include <BTools/utils/imgUtils.h>

using namespace DGtal::Z2i;

template<class TIterator>
TIterator advanceIterator(TIterator it, int n)
{
    for(int i=0;i<n;++i) ++it;
    return it;
}

DigitalSet holedSquare(int n, int squareSide, int holeSize)
{
    DigitalSet square = DIPaCUS::Shapes::square(1.0,0,0,squareSide);
    DigitalSet smallSquare = DIPaCUS::Shapes::square(1.0,0,0,holeSize);

    Domain domain( square.domain().lowerBound() - Point(holeSize*4,holeSize*4), square.domain().upperBound() - Point(holeSize*4,holeSize*4));
    auto begin = domain.begin();

    srand(time(NULL));
    for(int i=0;i<n;++i)
    {
        double r = rand() % domain.size();
        Point holeCenter = *advanceIterator(begin,r);

        for(auto it=smallSquare.begin();it!=smallSquare.end();++it)
        {
            Point np = *it + holeCenter;
            square.erase(np);
        }
    }

    return square;
}

int main(int argc,char* argv[])
{
    if(argc < 5)
    {
        std::cerr << "Usage: " << argv[0] << " NumHoles SideSquare HoleSize OutputFilePath\n";
        exit(1);
    }

    int numHoles = std::atoi( argv[1] );
    int squareSize = std::atoi( argv[2] );
    int holeSize = std::atoi( argv[3] );
    std::string outputFilePath = argv[4];

    boost::filesystem::path p(outputFilePath);
    boost::filesystem::create_directories(p.remove_filename());

    DigitalSet hs = holedSquare(numHoles,squareSize,holeSize);
    BTools::Utils::exportImageFromDigitalSet(hs,outputFilePath);


    return 0;
}
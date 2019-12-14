#include <iostream>
#include <boost/filesystem.hpp>

#include "glued-curve.h"
#include "distance-transform.h"

using namespace Fig2;

int main(int argc, char* argv[])
{
    if(argc <2)
    {
        std::cerr << "Usage: " << argv[0]  << " OutputFolder\n";
        exit(1);
    }

    std::string outputFolder = argv[1];

    std::string gluedCurveOutputFilepath = outputFolder + "/glued-curve-example.eps";
    boost::filesystem::path p(gluedCurveOutputFilepath);
    boost::filesystem::create_directories(p.remove_filename());

    GluedCurve::gluedCurve(gluedCurveOutputFilepath);
    DistanceTransform::distanceTransform(3,0.25,outputFolder);

    return 0;
}


#include "ElasticaProblem/model/Inbox.h"

using namespace BTools::Application::Illustration::ElasticaProblem;



Intern::Inbox::Inbox(RealPoint A,
                     RealPoint B,
                     RealPoint tA,
                     RealPoint tB)
{
    if(tA(1)>0) tA = -tA;   //Impose a counterclockwise orientation
    if(tB(1)<0) tB = -tB;   //Impose a counterclockwise orientation

    double h= 50.0;

    RealPoint extA = A+tA*h;
    RealPoint extB = B-tB*h;

    left = Line2D(A,extA);
    bottom = Line2D(extA,extB);
    right = Line2D(extB,B);
    top = Line2D(B,A);
}
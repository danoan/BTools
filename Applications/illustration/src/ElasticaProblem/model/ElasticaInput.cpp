#include "ElasticaProblem/model/ElasticaInput.h"

using namespace BTools::Application::Illustration::ElasticaProblem;


ElasticaInput::ElasticaInput(RealPoint A,
                             RealPoint B,
                             RealPoint tA,
                             RealPoint tB):A(A),
                                           B(B),
                                           tA(tA),
                                           tB(tB),
                                           inputDS( createInputDS(A,B,tA,tB) ){};





bool ElasticaInput::isInsideHalfplanes(const std::vector<Line2D> &halfplanes,
                                       const Point& p)
{
    bool r=true;
    for(auto it=halfplanes.begin();it!=halfplanes.end();++it)
    {
        r = r && it->signedDistance(p) >= 0;
    }

    return r;
}

bool ElasticaInput::boundingBox(RealPoint &lb,
                                RealPoint &ub,
                                const std::vector<RealPoint>& extremes)
{
    lb = extremes[0];
    ub = extremes[0];
    for(int i=0;i<extremes.size();++i)
    {
        lb(0) = extremes[i][0]<lb(0)?extremes[i][0]:lb(0);
        lb(1) = extremes[i][1]<lb(1)?extremes[i][1]:lb(1);

        ub(0) = extremes[i][0]>ub(0)?extremes[i][0]:ub(0);
        ub(1) = extremes[i][1]>ub(1)?extremes[i][1]:ub(1);
    }


}

Intern::Triangle ElasticaInput::leftTriangle(RealPoint A, RealPoint tA)
{
    double h = 50.0;
    if(tA(1)<0)
    {
        RealPoint botR = A + tA*h;
        RealPoint top = A - tA*h;
        RealPoint botL( top(0),botR(1) );

        return Intern::Triangle( Line2D(top,botL),Line2D(botL,botR),Line2D(botR,top) );
    }
    else
    {
        RealPoint botL = A -tA*h;
        RealPoint top = A;
        RealPoint botR( top(0),botL(1));

        return Intern::Triangle( Line2D(top,botR),Line2D(botR,botL),Line2D(botL,top));
    }
}

Intern::Triangle ElasticaInput::rightTriangle(RealPoint B, RealPoint tB)
{
    double h = 50.0;
    if(tB(1)<0)
    {
        RealPoint botR = B + tB*h;
        RealPoint top = B;
        RealPoint botL( top(0),botR(1) );

        return Intern::Triangle( Line2D(top,botL),Line2D(botL,botR),Line2D(botR,top) );
    }
    else
    {
        RealPoint botL = B -tB*h;
        RealPoint top = B+tB*h;
        RealPoint botR( top(0),botL(1));

        return Intern::Triangle( Line2D(top,botL),Line2D(botL,botR),Line2D(botR,top));
    }
}

DigitalSet ElasticaInput::createInputDS(RealPoint A,
                                        RealPoint B,
                                        RealPoint tA,
                                        RealPoint tB)
{
    assert( tA(0)>=0 && tA(0)<=1 && tA(1)>=-1 && tA(1)<=1 ); //1st and 4th quadrants.
    assert( tB(0)>=0 && tB(0)<=1 && tB(1)>=-1 && tB(1)<=1 ); //1st and 4th quadrants.

    assert( A(1) == B(1) && A(0) <= B(0) ); //AB is parallel to the horizontal axis and A is at the left of B.


    Intern::Inbox cb(A,B,tA,tB);
    std::vector<Line2D> isIn = {cb.left,cb.bottom,cb.right,cb.top};

    Intern::Triangle lTriangle = leftTriangle(A,tA);
    std::vector<Line2D> isInLeft = {lTriangle.bottom,lTriangle.side,lTriangle.hypotenuse};

    Intern::Triangle rTriangle = rightTriangle(B,tB);
    std::vector<Line2D> isInRight = {rTriangle.bottom,rTriangle.side,rTriangle.hypotenuse};

    std::function<bool(Point)> myPredicate = [&isIn,&isInLeft,&isInRight](Point p)->bool{
        return isInsideHalfplanes(isIn,p) || isInsideHalfplanes(isInRight,p) || isInsideHalfplanes(isInLeft,p); };


    std::vector<RealPoint> extremes = { cb.left.p(),cb.bottom.p(),cb.right.p(),cb.top.p(),
                                        lTriangle.hypotenuse.p(),lTriangle.side.p(),lTriangle.bottom.p(),
                                        rTriangle.hypotenuse.p(),rTriangle.side.p(),rTriangle.bottom.p()};

    RealPoint lb,ub;
    boundingBox(lb,ub,extremes);
    Domain _domain( lb,ub);

    DigitalSet _ds(_domain);
    for(auto it=_domain.begin();it!=_domain.end();++it)
    {
        if(myPredicate(*it)) _ds.insert(*it);
    }

    RealPoint border(10,10);
    Domain domain(lb-border,ub+border);
    DigitalSet ds( domain );
    ds.insert(_ds.begin(),_ds.end());

    return ds;

}

#include "OneImageFlow.h"

using namespace SummaryFlow;

OneImageFlow::Domain OneImageFlow::commonDomain(SetPointSequenceIterator begin,
                                                SetPointSequenceIterator end)
{
    Point lb,ub;
    lb = *begin->begin();
    ub = lb;
    for(auto itS=begin;itS!=end;++itS)
    {
        for(auto itP=itS->begin();itP!=itS->end();++itP)
        {
            Point p = *itP;
            lb(0) = p(0)<lb(0)?p(0):lb(0);
            lb(1) = p(1)<lb(1)?p(1):lb(1);

            ub(0) = p(0)>ub(0)?p(0):ub(0);
            ub(1) = p(1)>ub(1)?p(1):ub(1);
        }
    }

    return Domain(lb + Point(-5,-5),ub + Point(5,5));
}

void OneImageFlow::createUnifiedImage(const std::string& imgOutputPath,
                                      SetPointSequenceIterator begin,
                                      SetPointSequenceIterator end,
                                      int seqStep,
                                      ImageOutputType iot)
{
    Domain domain = commonDomain(begin,end);
    DigitalSet ds(domain);

    Color red = Color(255,0,0);
    Color blue = Color(0,0,255);
    Color listOfColors[4] = {red,Color(0,0,0),Color(100,100,100),Color(200,200,200)};

    int c=0;
    int colorIndex;

    Board2D board;
//    board << DGtal::CustomStyle( domain.className(),
//                                 new DGtal::CustomColors(Color::White,Color::White) )
//          << domain;

    SetPointSequenceIterator itS;
    int jump = 0;
    for(itS=begin;itS!=end;++itS,--jump)
    {
        if(jump>0) continue;

        colorIndex = c%3;
        colorIndex += c==0?0:1;
        ds.insert(itS->begin(),itS->end());
        board << DGtal::CustomStyle( ds.className(),
                                     new DGtal::CustomColors(listOfColors[colorIndex],listOfColors[colorIndex]) )
              << ds;
        ds.clear();

        jump=seqStep;
        ++c;
    }
    itS = begin;
    while(itS+1!=end)++itS;
    ds.insert(itS->begin(),itS->end());
    board << DGtal::CustomStyle( ds.className(),
                                 new DGtal::CustomColors(blue,blue) )
          << ds;

    if(iot==SVG) board.saveSVG( (imgOutputPath).c_str(),200,200,10 );
    else board.saveEPS( (imgOutputPath).c_str(),200,200,10 );

}

OneImageFlow::OneImageFlow(const std::string& imageSrcFolder,
                           const std::string& imageOutputPath,
                           int seqStep,
                           ImageOutputType iot)
{
    boost::filesystem::path imageSrcPath(imageSrcFolder);
    boost::filesystem::directory_iterator di(imageSrcPath);

    std::vector<std::string> vectorOfImgPath;
    boost::filesystem::path currPath;
    int numImages=0;
    while( di!=boost::filesystem::directory_iterator() )
    {
        currPath = di->path();
        if(boost::filesystem::is_regular_file(currPath) && currPath.extension().string()==".pgm")
        {
            vectorOfImgPath.push_back(currPath.string());
            numImages+=1;
        }
        ++di;
    }

    if(seqStep<0) seqStep=numImages/10;

    std::sort(vectorOfImgPath.begin(),vectorOfImgPath.end());

    std::vector< SetPoint > setPointFamily;

    for(auto it=vectorOfImgPath.begin();it!=vectorOfImgPath.end();++it)
    {
        SetPoint sp;
        cv::Mat cvImg = cv::imread(*it);

        cv::Mat grayscale(cvImg.size(),
                          CV_8UC1);

        if(cvImg.type()!=CV_8UC1)
            cv::cvtColor(cvImg,grayscale,cv::COLOR_RGB2GRAY,1);


        DigitalSet ds( Domain(Point(0,0),Point(grayscale.cols-1,grayscale.rows-1) ) );

        DIPaCUS::Representation::CVMatToDigitalSet(ds,grayscale);

        DigitalSet boundaryDS(ds.domain());
        DIPaCUS::Misc::digitalBoundary<Pred8>(boundaryDS,ds);

        sp.insert(boundaryDS.begin(),boundaryDS.end());

        setPointFamily.push_back(sp);
    }

    createUnifiedImage(imageOutputPath,
                       setPointFamily.begin(),
                       setPointFamily.end(),
                       seqStep,
                       iot);

}
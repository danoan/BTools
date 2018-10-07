#include "OneImageFlow.h"

using namespace BTools::Application::Illustration;

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
                                      int seqStep)
{
    Domain domain = commonDomain(begin,end);
    DigitalSet ds(domain);

    Color red = Color(255,0,0);
    Color blue = Color(0,0,255);
    Color listOfColors[4] = {red,Color(0,0,0),Color(100,100,100),Color(200,200,200)};

    int c=0;
    int colorIndex;

    Board2D board;
    board << DGtal::CustomStyle( domain.className(),
                                 new DGtal::CustomColors(Color::White,Color::White) )
          << domain;

    auto itS = begin;
    for(auto itS=begin;itS!=end;itS+=seqStep,++c)
    {
        colorIndex = c%3;
        colorIndex += c==0?0:1;
        ds.insert(itS->begin(),itS->end());
        board << DGtal::CustomStyle( ds.className(),
                                     new DGtal::CustomColors(listOfColors[colorIndex],listOfColors[colorIndex]) )
              << ds;
        ds.clear();
    }
    itS = begin;
    while(itS+1!=end)++itS;
    ds.insert(itS->begin(),itS->end());
    board << DGtal::CustomStyle( ds.className(),
                                 new DGtal::CustomColors(blue,blue) )
          << ds;

    board.saveEPS(imgOutputPath.c_str());
}

OneImageFlow::OneImageFlow(const std::string& imageSrcFolder,
                           const std::string& imageOutputPath,
                           int seqStep)
{
    boost::filesystem::path imageSrcPath(imageSrcFolder);
    boost::filesystem::directory_iterator di(imageSrcPath);

    std::vector<std::string> vectorOfImgPath;
    boost::filesystem::path currPath;
    while( di!=boost::filesystem::directory_iterator() )
    {
        currPath = di->path();
        if(boost::filesystem::is_regular_file(currPath))
        {
            vectorOfImgPath.push_back(currPath.string());
        }
        ++di;
    }
    std::sort(vectorOfImgPath.begin(),vectorOfImgPath.end());

    std::vector< SetPoint > setPointFamily;

    for(auto it=vectorOfImgPath.begin();it!=vectorOfImgPath.end();++it)
    {
        std::cout << *it << std::endl;
        SetPoint sp;
        Image2D image = DGtal::GenericReader<Image2D>::import(*it);

        DigitalSet ds(image.domain());
        DIPaCUS::Representation::ImageAsDigitalSet(ds,*it);

        DigitalSet boundaryDS(image.domain());
        Neigh8 a(boundaryDS,ds);

        sp.insert(boundaryDS.begin(),boundaryDS.end());
        setPointFamily.push_back(sp);
    }

    createUnifiedImage(imageOutputPath,
                       setPointFamily.begin(),
                       setPointFamily.end(),
                       seqStep);

}
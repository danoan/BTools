#include "summary-flow/OneImageFlow.h"

namespace SummaryFlow
{
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
                                          const std::set<Point>& dirs,
                                          int seqStep,
                                          ImageOutputType iot)
    {
        Domain domain = commonDomain(begin,end);
        DigitalSet ds(domain);

        Color red = Color(255,0,0);
        Color green = Color(0,255,0);
        Color blue = Color(0,0,255);
        Color listOfColors[3] = {Color(0,0,0),Color(100,100,100),Color(200,200,200)};

        int c=0;
        int colorIndex;

        Board2D board;
        SetPointSequenceIterator itS;
        int jump = 0;
        for(itS=begin+1;itS!=end;++itS,++c,--jump)
        {
            if(jump>0) continue;

            colorIndex = c%3;
            ds.insert(itS->begin(),itS->end());
            board << DGtal::CustomStyle( ds.className(),
                                         new DGtal::CustomColors(listOfColors[colorIndex],listOfColors[colorIndex]) )
                  << ds;
            ds.clear();

            jump=seqStep;
        }
        itS = begin;

        ds.insert(itS->begin(),itS->end());
        board << DGtal::CustomStyle( ds.className(),
                                     new DGtal::CustomColors(red,red) )
              << ds;
        ds.clear();


        while(itS!=end)++itS;
        --itS;
        ds.insert(itS->begin(),itS->end());
        board << DGtal::CustomStyle( ds.className(),
                                     new DGtal::CustomColors(blue,blue) )
              << ds;
        ds.clear();


        ds.insert(dirs.begin(),dirs.end());
        board << DGtal::CustomStyle( ds.className(),
                                     new DGtal::CustomColors(green,green) )
              << ds;


        if(iot==SVG) board.saveSVG( (imgOutputPath).c_str(),200,200,10 );
        else board.saveEPS( (imgOutputPath).c_str(),200,200,10 );

    }

    OneImageFlow::SetPoint OneImageFlow::setFromMask(const std::string& imgPath)
    {
        SetPoint ps;
        typedef DIPaCUS::Representation::Image2D Image2D;
        Image2D img = DGtal::GenericReader<Image2D>::import(imgPath);
        DigitalSet ds( img.domain() );
        DIPaCUS::Representation::imageAsDigitalSet(ds,img);
        for(auto p:ds) ps.insert(p);

        return ps;
    }

    OneImageFlow::OneImageFlow(const std::string& imageSrcFolder,
                               const std::string& imageOutputPath,
                               int seqStep,
                               ImageOutputType iot,
                               const std::string& pixelMaskPath,
                               const std::string& dirsMaskPath,
                               bool drawCenterBall,
                               double radius,
                               double h)
    {
        boost::filesystem::path imageSrcPath(imageSrcFolder);
        boost::filesystem::directory_iterator di(imageSrcPath);

        std::set<Point> fixedPixels;
        std::set<Point> dirs;

        if(pixelMaskPath!="") fixedPixels = setFromMask(pixelMaskPath);
        if(dirsMaskPath!="") dirs = setFromMask(dirsMaskPath);

        std::vector<std::string> vectorOfImgPath;
        boost::filesystem::path currPath;
        while( di!=boost::filesystem::directory_iterator() )
        {
            currPath = di->path();
            if(boost::filesystem::is_regular_file(currPath) && currPath.extension().string()==".pgm")
            {
                if(currPath.string()!=pixelMaskPath &&
                   currPath.string()!=dirsMaskPath)
                {
                    vectorOfImgPath.push_back(currPath.string());
                }
            }
            ++di;
        }
        std::sort(vectorOfImgPath.begin(),vectorOfImgPath.end());

        std::vector< SetPoint > setPointFamily;

        for(auto it=vectorOfImgPath.begin();it!=vectorOfImgPath.end();++it)
        {
            SetPoint sp;
            DigitalSet ds = Utils::imageToDigitalSet(*it);

            DigitalSet boundaryDS(ds.domain());
            DIPaCUS::Misc::digitalBoundary<Pred8>(boundaryDS,ds);

            DigitalSet filteredDS = Utils::eliminatePixels(boundaryDS,fixedPixels);

            if(filteredDS.size()>0)
            {
                sp.insert(filteredDS.begin(),filteredDS.end());
                setPointFamily.push_back(sp);
            }

        }

        if(drawCenterBall)
        {
            DigitalSet ballContour = Utils::centerBall(setPointFamily.back(),radius,h);
            dirs.insert(ballContour.begin(),ballContour.end());
        }


        createUnifiedImage(imageOutputPath,
                           setPointFamily.begin(),
                           setPointFamily.end(),
                           dirs,
                           seqStep,
                           iot);

    }
}


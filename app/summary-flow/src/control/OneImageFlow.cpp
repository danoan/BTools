#include "summary-flow/control/OneImageFlow.h"

namespace SummaryFlow
{
    OneImageFlow::Domain OneImageFlow::findCommonDomain(const SetPointSequence& contours)
    {
        auto begin = contours.begin();
        auto end = contours.end();

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


    void OneImageFlow::drawContours( DrawingBuffer& drawBuffer,
            const SetPointSequence& contours,
            int drawInterval,
            const ColorScheme& colorScheme)
    {
        auto itContour = contours.begin();
        auto itColor = colorScheme.begin();
        auto pointDraw = [&drawBuffer,&itColor](const Point& p){drawBuffer.draw(p,*itColor,*itColor);};

        //Draw intermediate contours
        while(itContour!=contours.end())
        {
            std::for_each(itContour->begin(),
                          itContour->end(),
                          pointDraw);

            itColor++;
            for(int i=0;i<drawInterval && itContour!=contours.end();++i){
                itContour++;
            }
        }

        //Draw initial contour
        auto pointDrawFirst = [&drawBuffer,&colorScheme](const Point& p){drawBuffer.draw(p,colorScheme.first(),colorScheme.first());};
        itContour = contours.begin();
        std::for_each(itContour->begin(),
                      itContour->end(),
                      pointDrawFirst);


        //Draw last contour
        auto pointDrawLast = [&drawBuffer,&colorScheme](const Point& p){drawBuffer.draw(p,colorScheme.last(),colorScheme.last());};
        while(itContour!=contours.end())++itContour;
        --itContour;
        std::for_each(itContour->begin(),
                      itContour->end(),
                      pointDrawLast);

    }

    void OneImageFlow::createUnifiedImage(const std::string& imgOutputPath,
                                          const SetPointSequence& contours,
                                          const std::set<Point>& extraPoints,
                                          const ColorScheme& colorScheme,
                                          int drawInterval,
                                          ImageOutputType iot)
    {
        Domain domain = findCommonDomain(contours);
        DrawingBuffer drawBuffer;
        drawContours(drawBuffer,contours,drawInterval,colorScheme);

        //Draw ExtraPoints
        auto pointDrawExtra = [&drawBuffer,&colorScheme](const Point& p){drawBuffer.draw(p,colorScheme.extra(),colorScheme.extra());};
        std::for_each(extraPoints.begin(),
                      extraPoints.end(),
                      pointDrawExtra);


        if(iot==SVG) drawBuffer.flushSVG( (imgOutputPath).c_str() );
        else drawBuffer.flushEPS( (imgOutputPath).c_str()  );

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

    void OneImageFlow::collectImagesPath(std::vector<std::string>& paths,
                                         const std::string& imageSrcFolder,
                                         const std::string& imageExtension,
                                         std::function<bool(const std::string&)> validPath)
    {
        boost::filesystem::path imageSrcPath(imageSrcFolder);
        boost::filesystem::directory_iterator di(imageSrcPath);

        boost::filesystem::path currPath;
        while( di!=boost::filesystem::directory_iterator() )
        {
            currPath = di->path();
            if(boost::filesystem::is_regular_file(currPath) && currPath.extension().string()==imageExtension)
            {

                if(validPath(currPath.string()))
                {
                    paths.push_back(currPath.string());
                }
            }
            ++di;
        }

        std::sort(paths.begin(),paths.end());
    }

    void OneImageFlow::extractContourPoints( SetPointSequence& contours,
            const std::string& imagePath,
            const SetPoint& fixedPixels)
    {
        SetPoint sp;
        DigitalSet ds = Utils::imageToDigitalSet(imagePath);

        DigitalSet boundaryDS(ds.domain());
        DIPaCUS::Misc::digitalBoundary<Pred8>(boundaryDS,ds);

        DigitalSet filteredDS = Utils::eliminatePixels(boundaryDS,fixedPixels);

        if(filteredDS.size()>0)
        {
            sp.insert(filteredDS.begin(),filteredDS.end());
            contours.push_back(sp);
        }
    }

    OneImageFlow::OneImageFlow(const std::string& imageSrcFolder,
                               const std::string& imageOutputPath,
                               const std::string& imageExtension,
                               int drawInterval,
                               const ColorScheme& colorScheme,
                               ImageOutputType iot,
                               const std::string& pixelMaskPath,
                               const std::string& dirsMaskPath,
                               bool drawCenterBall,
                               double radius,
                               double h)
    {
        std::vector<std::string> vectorOfImgPath;

        collectImagesPath(vectorOfImgPath,
                imageSrcFolder,
                imageExtension,
                [&pixelMaskPath,&dirsMaskPath](const std::string& s){ return s!=pixelMaskPath && s!=dirsMaskPath; });
        int numImages=vectorOfImgPath.size();

        SetPoint fixedPixels;
        SetPoint extraPoints;

        if(pixelMaskPath!="") fixedPixels = setFromMask(pixelMaskPath);
        if(dirsMaskPath!="") extraPoints = setFromMask(dirsMaskPath);

        SetPointSequence contours;
        for(auto imgPath:vectorOfImgPath)
        {
            extractContourPoints(contours,imgPath,fixedPixels);
        }

        if(drawCenterBall)
        {
            DigitalSet ballContour = Utils::centerBall(contours.back(),radius,h);
            extraPoints.insert(ballContour.begin(),ballContour.end());
        }

        if(drawInterval<0) drawInterval=(int) ceil(numImages/10.0);
        if(drawInterval>=contours.size()) drawInterval = 1+contours.size()/2;


        createUnifiedImage(imageOutputPath,
                           contours,
                           extraPoints,
                           colorScheme,
                           drawInterval,
                           iot);

    }
}


#include "BinOCS/Lab/utils.h"

using namespace BinOCS::Lab;

void Utils::showManyImages(std::string title,int nArgs, const cv::Mat& img1, const cv::Mat& img2)
{
    using namespace cv;
    using namespace std;

    int size;
    int i;
    int m, n;
    int x, y;

    cv::Mat listImg[2] = {img1,img2};

// w - Maximum number of images in a row
// h - Maximum number of images in a column
    int w, h;

// scale - How much we have to resize the image
    float scale;
    int max;

// If the number of arguments is lesser than 0 or greater than 12
// return without displaying
    if(nArgs <= 0) {
        printf("Number of arguments too small....\n");
        return;
    }
    else if(nArgs > 14) {
        printf("Number of arguments too large, can only handle maximally 12 images at a time ...\n");
        return;
    }
// Determine the size of the image,
// and the number of rows/cols
// from number of arguments
    else if (nArgs == 1) {
        w = h = 1;
        size = 300;
    }
    else if (nArgs == 2) {
        w = 2; h = 1;
        size = 300;
    }
    else if (nArgs == 3 || nArgs == 4) {
        w = 2; h = 2;
        size = 300;
    }
    else if (nArgs == 5 || nArgs == 6) {
        w = 3; h = 2;
        size = 200;
    }
    else if (nArgs == 7 || nArgs == 8) {
        w = 4; h = 2;
        size = 200;
    }
    else {
        w = 4; h = 3;
        size = 150;
    }

    ///va_args with cv::Mat raises an error: cannot receive objects of non-trivially-copyable type
    ///it will be better to rewrite this function without using va_args

// Create a new 3 channel image
    Mat DispImage = Mat::zeros(Size(100 + size*w, 60 + size*h), CV_8UC3);


// Loop for nArgs number of arguments
    for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {
        // Get the Pointer to the IplImage
        cv::Mat img = listImg[i];

        // Check whether it is NULL or not
        // If it is NULL, release the image, and return
        if(img.empty()) {
            printf("Invalid arguments");
            return;
        }

        // Find the width and height of the image
        x = img.cols;
        y = img.rows;

        // Find whether height or width is greater in order to resize the image
        max = (x > y)? x: y;

        // Find the scaling factor to resize the image
        scale = (float) ( (float) max / size );

        // Used to Align the images
        if( i % w == 0 && m!= 20) {
            m = 20;
            n+= 20 + size;
        }

        // Set the image ROI to display the current image
        // Resize the input image and copy the it to the Single Big Image
        Rect ROI(m, n, (int)( x/scale ), (int)( y/scale ));
        Mat temp; resize(img,temp, Size(ROI.width, ROI.height));
        temp.copyTo(DispImage(ROI));
    }

// Create a new window, and show the Single Big Image
    namedWindow( title, cv::WINDOW_FULLSCREEN );
    imshow( title, DispImage);
    waitKey();

}

cv::Rect Utils::computeBoundingBox(const cv::Mat &img)
{
    int nRows = img.rows;
    int nCols = img.cols;


    cv::Point low,high;
    low = cv::Point(10000,10000);
    high = cv::Point(0,0);

    typedef cv::Vec3b ColorType;

    const ColorType* row;
    for(int i=0;i<nRows;++i)
    {
        row = img.ptr<ColorType>(i);
        for(int j=0;j<nCols;++j)
        {
            if(row[j]==ColorType(0,0,0)) continue;

            low.x = j<low.x?j:low.x;
            low.y = i<low.y?i:low.y;

            high.x = j>high.x?j:high.x;
            high.y = i>high.y?i:high.y;
        }
    }

    return cv::Rect(low,high);
}

void Utils::enhance(cv::Mat& imgOutput,
                             const cv::Mat& baseImg,
                             const DGtal::Z2i::DigitalSet& enhanceDSMask,
                             double factor)
{
    for(auto it=enhanceDSMask.begin();it!=enhanceDSMask.end();++it)
    {
        int row = imgOutput.rows-(*it)(1)-1;
        int col = (*it)(0);

        std::cout << baseImg.at<cv::Vec3b>(row,col) << std::endl;
        std::cout << (baseImg.at<cv::Vec3b>(row,col)*factor) << std::endl;

        imgOutput.at<cv::Vec3b>(row,col) = (baseImg.at<cv::Vec3b>(row,col)*factor);

    }
}

std::string Utils::fixedStrLength(int l,double v)
{
    std::string out = std::to_string(v);
    while(out.length()<l) out += " ";

    return out;
}

std::string Utils::fixedStrLength(int l,std::string str)
{
    std::string out = str;
    while(out.length()<l) out += " ";

    return out;
}



std::string Utils::resolveQPBOSolverType(Model::BCorrectionInput::QPBOSolverType solverType)
{
    switch(solverType)
    {
        case Model::BCorrectionInput::QPBOSolverType::Simple:
            return "Simple";
        case Model::BCorrectionInput::QPBOSolverType::ImproveProbe:
            return "Improve-Probe";
        case Model::BCorrectionInput::QPBOSolverType::Improve:
            return "Improve";
        case Model::BCorrectionInput::QPBOSolverType::Probe:
            return "Probe";
    }
}

void Utils::write(const Model::BCorrectionInput& bcInput,
                  std::ostream& os)
{
    os << "Sq. Curv. Weigth: " << bcInput.sqTermWeight << std::endl
       << "Length Weigth: " << bcInput.lengthTermWeight << std::endl
       << "Data Weigth: " << bcInput.dataTermWeight << std::endl
       << "Estimating Ball Radius: " << bcInput.estimatingBallRadius << std::endl
       << "Solver Type: " << resolveQPBOSolverType(bcInput.solverType) << std::endl;
}

void Utils::write(const Model::GrabCorrectionInput& gcInput,
                  std::ostream& os)
{
    os << "Image: " << gcInput.imagePath << std::endl;
    write(gcInput.bcInput,os);
}

void Utils::write(const Model::SeedCorrectionInput &seedcInput, std::ostream &os)
{
    write(seedcInput.bcInput,os);
}


void Utils::write(const Model::OptOutput& output,
                  std::ostream& os,
                  bool vertical=true)
{
    if(vertical)
    {
        os << "Opt. Energy Value: " << output.optEnergyValue << std::endl
           << "II Elastica: " << output.IIElasticaValue << std::endl
           << "MDCA Elastica: " << output.MDCAElasticaValue << std::endl
           << "Unlabeled: " << output.unlabeled << std::endl;
    }
    else
    {
        int colLength=20;
        os << fixedStrLength(colLength,output.optEnergyValue) << "\t"
           << fixedStrLength(colLength,output.IIElasticaValue) << "\t"
           << fixedStrLength(colLength,output.MDCAElasticaValue) << "\t"
           << fixedStrLength(colLength,output.unlabeled) << std::endl;

    }
}

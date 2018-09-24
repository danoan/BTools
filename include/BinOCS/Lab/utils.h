#include <opencv2/opencv.hpp>

#include <cstdio>
#include <cstdarg>
#include <DGtal/helpers/StdDefs.h>

#include <BinOCS/Lab/model/input/BCorrectionInput.h>
#include <BinOCS/Lab/model/input/ROICorrectionInput.h>
#include <BinOCS/Lab/model/input/GrabCorrectionInput.h>
#include <BinOCS/Lab/model/OptOutput.h>

namespace BinOCS
{
    namespace Lab
    {
        namespace Utils
        {
            /*Function///////////////////////////////////////////////////////////////

            Name:       ShowManyImages

            Purpose:

            This is a function illustrating how to display more than one
            image in a single window using Intel OpenCV

            Parameters:

            string title: Title of the window to be displayed
            int    nArgs: Number of images to be displayed
            Mat    img1: First Mat, which contains the first image
            ...
            Mat    imgN: First Mat, which contains the Nth image

            Language:   C++

            The method used is to set the ROIs of a Single Big image and then resizing
            and copying the input images on to the Single Big Image.

            This function does not stretch the image...
            It resizes the image without modifying the width/height ratio..

            This function can be called like this:

            ShowManyImages("Images", 5, img2, img2, img3, img4, img5);

            This function can display upto 12 images in a single window.
            It does not check whether the arguments are of type Mat or not.
            The maximum window size is 700 by 660 pixels.
            Does not display anything if the number of arguments is less than
            one or greater than 12.

            Idea was from [[BettySanchi]] of OpenCV Yahoo! Groups.

            If you have trouble compiling and/or executing
            this code, I would like to hear about it.

            You could try posting on the OpenCV Yahoo! Groups
            [url]http://groups.yahoo.com/group/OpenCV/messages/ [/url]


            Parameswaran,
            Chennai, India.

            cegparamesh[at]gmail[dot]com

            ...
            ///////////////////////////////////////////////////////////////////////*/

            void showManyImages(std::string title, int nArgs, ...);
            void enhance(cv::Mat& imgOutput,
                         const cv::Mat& baseImg,
                         const DGtal::Z2i::DigitalSet& enhanceDSMask,
                         double factor);


            void write(const Model::BCorrectionInput& bcInput,
                       std::ostream& os);

            void write(const Model::GrabCorrectionInput& gcInput,
                       std::ostream& os);


            void write(const Model::ROICorrectionInput& roicInput,
                       std::ostream& os);


            void write(const Model::OptOutput &output,
                       std::ostream& os,
                       bool vertical);

            std::string fixedStrLength(int l,std::string str);
            std::string fixedStrLength(int l,double v);
            std::string resolveQPBOSolverType(Model::BCorrectionInput::QPBOSolverType solverType);
        }
    }
}


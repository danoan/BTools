#include "BTools/core/BCApplication.h"
#include <DIPaCUS/components/Morphology.h>

using namespace BTools::Core;

template<typename TVisitorIterator>
BCApplication::BCApplication(BCAOutput& bcaOutput,
                             const BCAInput& bcaInput,
                             int maxIterations,
                             bool displayEachIteration,
                             TVisitorIterator begin,
                             TVisitorIterator end)
{
    IFlowProfile& flowProfile = FlowPool::getFlow(bcaInput.flowProfile,
                                                  bcaInput.odrConfigInput.optInApplicationRegion);

    ODRInterface& odrInterface = ODRPool::get(bcaInput.odrConfigInput);

    BCAOutput::EnergySolution& solution = bcaOutput.energySolution;
//    DigitalSet inputDS = bcaInput.imageDataInput.inputDS;
    DigitalSet inputDS(bcaInput.imageDataInput.inputDS.domain());
    DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT, 1);
    DIPaCUS::Morphology::dilate(inputDS,bcaInput.imageDataInput.inputDS,se,bcaInput.bcConfigInput.initialDilation);

    BCAOutput lastValidSolution(bcaInput);
    //std::cerr << inputDS.domain() << std::endl;

    try
    {
        while(flowProfile.currentIteration()<maxIterations)
        {
            BCControl(solution,
                      bcaInput.bcConfigInput,
                      bcaInput.imageDataInput,
                      odrInterface,
                      flowProfile.nextStep(),
                      inputDS,
                      begin,
                      end);

            inputDS.clear();
            inputDS.insert(solution.outputDS.begin(),solution.outputDS.end());

            if(flowProfile.currentIteration()%5==0 && bcaInput.showProgress)
                std::cout << flowProfile.currentIteration() << "/" << maxIterations << std::endl;

            if(displayEachIteration)
            {
                prepareProductImage(bcaOutput,
                                    bcaInput.imageDataInput);

                std::string windowName="Iteration_" + std::to_string(flowProfile.currentIteration());
                cv::namedWindow(windowName);
                cv::imshow(windowName,bcaOutput.imgOutput);
                cv::waitKey(0);
                cv::destroyAllWindows();

            }

            lastValidSolution = bcaOutput;
        }
    }catch(std::exception ex)
    {
        std::cerr << "Error in iteration " << flowProfile.currentIteration() << ". Saving current solution.\n";
    }

    bcaOutput = lastValidSolution;
    prepareProductImage(bcaOutput,
                        bcaInput.imageDataInput);
}
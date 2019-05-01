#include "BTools/core/BCApplication.h"

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
    DigitalSet inputDS = bcaInput.imageDataInput.inputDS;

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


        if(displayEachIteration)
        {
            prepareProductImage(bcaOutput,
                                bcaInput.imageDataInput);

            std::string windowName="Iteration: " + std::to_string(flowProfile.currentIteration());
            cv::namedWindow(windowName);
            cv::imshow(windowName,bcaOutput.imgOutput);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
    }

    prepareProductImage(bcaOutput,
                        bcaInput.imageDataInput);
}
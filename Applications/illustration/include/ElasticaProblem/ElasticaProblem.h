#ifndef BTOOLS_ELASTICAPROBLEM_H
#define BTOOLS_ELASTICAPROBLEM_H

#include <DGtal/io/boards/Board2D.h>
#include "ElasticaProblem/model/ElasticaInput.h"
#include "SCaBOliC/Core/display.h"
#include "SCaBOliC/Core/ODRPixels.h"
#include "SCaBOliC/Energy/ISQ/ISQEnergy.h"
#include <DIPaCUS/derivates/Misc.h>
#include <SCaBOliC/Core/ODRInterpixels.h>
#include <BinOCS/BoundaryCorrection/BCApplication.h>
#include "MockDistribution.h"

namespace BTools
{
    namespace Application
    {
        namespace Illustration
        {
            namespace ElasticaProblem
            {
                typedef DGtal::Z2i::Curve Curve;
                typedef DGtal::Z2i::KSpace KSpace;

                typedef SCaBOliC::Core::ODRModel ODRModel;
                typedef ODRModel::OptimizationMode  OptimizationMode;
                typedef ODRModel::ApplicationMode ApplicationMode;
                typedef ODRModel::ApplicationCenter ApplicationCenter;
                typedef ODRModel::CountingMode CountingMode;
                typedef ODRModel::NeighborhoodType NeighborhoodType;

                typedef SCaBOliC::Core::ODRPixels ODRPixels;
                typedef SCaBOliC::Core::ODRInterface ODRInterface;
                typedef SCaBOliC::Energy::ISQEnergy ISQEnergy;
                typedef ISQEnergy::InputData ISQInputData;
                typedef ISQEnergy::Solution Solution;

                struct IterationData
                {
                    IterationData(OptimizationMode optMode,
                                  ApplicationMode appMode):optMode(optMode),
                                                           appMode(appMode){}
                    OptimizationMode optMode;
                    ApplicationMode appMode;
                };

                void testElasticaInput();
                void createAndSaveDS(const RealPoint& A,
                                     const RealPoint& B,
                                     const RealPoint& tA,
                                     const RealPoint& tB,
                                     const std::string& filename);

                void example();
                IterationData nextIterationData(const int iteration);
                Solution boundaryCorrection(const ODRModel& ODR,
                                            const OptimizationMode& optMode,
                                            const ApplicationMode& appMode,
                                            const unsigned int radius);

                void updateSet(Solution& solution,
                               const ODRInterface& odrFactory,
                               const ApplicationMode& appMode,
                               const ISQInputData& energyInput,
                               const ISQEnergy& energy);

                DigitalSet aroundBoundary(const DigitalSet& optRegionDS,
                                          const ElasticaInput& ei,
                                          unsigned int length);


                DigitalSet optRegion(const ElasticaInput& ei,
                                     const DigitalSet& inputDS,
                                     const OptimizationMode& optMode);

                ODRModel createODR(const ElasticaInput& ei,
                                   const DigitalSet& inputDS,
                                   const OptimizationMode& optMode,
                                   const ApplicationMode& appMode,
                                   unsigned int radius);

                Curve curveSegment(const Curve& curve, const Point& A, const Point& B);

                DigitalSet digitalSetFromCurve(const Curve& curve,
                                               bool directIncident);

                bool adjacentLinel(const Curve::SCell& linel,
                                   const KSpace& KCurve,
                                   const Point& pixelSpacePoint);
            }
        }
    }
}


#endif //BTOOLS_ELASTICAPROBLEM_H

#ifndef BTOOLS_POTENTIALMAP_H
#define BTOOLS_POTENTIALMAP_H

#include "boost/filesystem.hpp"

#include <BTools/core/interface/IBCControlVisitor.h>
#include <DGtal/io/boards/Board2D.h>

namespace BTools
{
    namespace Visitors
    {
        typedef BTools::Core::IBCControlVisitor IBCControlVisitor;

        class PotentialMap:public IBCControlVisitor
        {
        public:
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Domain Domain;

            typedef std::unordered_map<Point,double> PotentialValues;

        public:
            PotentialMap(const std::string& outputPath):outputPath(outputPath){};


            void visit(const OptimizationData& optData,
                       const VariableMap& vm,
                       const ODRModel& odr);

        private:
            void gatherPotentialValues(PotentialValues& potentialValues,
                                       const OptimizationData &optData,
                                       const VariableMap& vm,
                                       const DigitalSet& optRegion);

            void draw(const PotentialValues& pv,
                      const DigitalSet& optRegion,
                      const std::string& outputPath);

        private:
            const std::string outputPath;

        };
    }
}

#endif //BTOOLS_POTENTIALMAP_H

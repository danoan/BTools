#ifndef BTOOLS_JMIV_FIGURES_FIG_2_GLUED_CURVE_H
#define BTOOLS_JMIV_FIGURES_FIG_2_GLUED_CURVE_H

#include <DGtal/io/boards/Board2D.h>

#include <exhaustive-gc/core/check-elem/CheckableSeedPair.h>
#include <exhaustive-gc/core/control/CurveFromJoints.h>

#include <exhaustive-gc/api/utils/GenerateSeedPairs.h>
#include <exhaustive-gc/api/utils/FilterSeedPairs.h>
#include <exhaustive-gc/api/model/SearchParameters.h>
#include <exhaustive-gc/energy/EnergyInput.h>
#include <exhaustive-gc/energy/EnergyType.h>

#include <magLac/core/base/Range.hpp>
#include <magLac/core/single/Combinator.hpp>

#include <gcurve/utils/displayUtils.h>

namespace Fig2
{
    namespace GluedCurve
    {
        using namespace DGtal::Z2i;
        using namespace ExhaustiveGC::Core;
        using namespace ExhaustiveGC::API;
        using namespace ExhaustiveGC::Energy;

        void gluedCurve(const std::string& outputFilePath);
    }
}

#endif //BTOOLS_JMIV_FIGURES_FIG_2_GLUED_CURVE_H

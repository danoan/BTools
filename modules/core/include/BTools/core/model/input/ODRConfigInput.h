#ifndef BTools_FLOWCONFIGINPUT_H
#define BTools_FLOWCONFIGINPUT_H

#include <BTools/core/interface/IFlowProfile.h>

namespace BTools
{
    namespace Core
    {
        struct ODRConfigInput
        {
            typedef SCaBOliC::Core::ODRModel::ApplicationMode ApplicationMode;
            typedef SCaBOliC::Core::ODRModel::NeighborhoodType NeighborhoodType;
            typedef SCaBOliC::Core::ODRModel::LevelDefinition LevelDefinition;
            typedef SCaBOliC::Core::ODRModel::StructuringElementType StructuringElementType;

            ODRConfigInput(double radius,
                           double gridStep,
                           int levels,
                           LevelDefinition ld,
                           NeighborhoodType nt,
                           bool optInApplicationRegion):levels(levels),
                                                        radius(radius),
                                                        gridStep(gridStep),
                                                        levelDefinition(ld),
                                                        neighborhood(nt),
                                                        optInApplicationRegion(optInApplicationRegion)
            {}

            bool operator==(const ODRConfigInput& other) const
            {
                return other.levels==this->levels && other.neighborhood==this->neighborhood
                       && other.optInApplicationRegion==this->optInApplicationRegion;

            }

            const int levels;
            const double radius;
            const double gridStep;
            const NeighborhoodType neighborhood;
            const LevelDefinition levelDefinition;

            bool optInApplicationRegion;
        };
    }
}

namespace std
{
    template<>
    struct hash<BTools::Core::ODRConfigInput>
    {
    private:
        typedef BTools::Core::ODRConfigInput ODRConfigInput;
        typedef ODRConfigInput::NeighborhoodType NeighborhoodType;
        typedef SCaBOliC::Core::ODRModel::LevelDefinition LevelDefinition;

    private:
        size_t numId(const NeighborhoodType& nt) const{ return nt==NeighborhoodType::FourNeighborhood?0:1;}
        size_t numId(const LevelDefinition& ld) const{ return ld==LevelDefinition::LD_CloserFromCenter?0:1; }
        size_t numId(bool bel) const{ return bel?1:0; }

    public:
        size_t operator()(const ODRConfigInput& oci) const
        {
            return numId(oci.neighborhood) + oci.levels*2 + numId(oci.levelDefinition)*4 +
                   numId(oci.optInApplicationRegion)*8;
        }

    };
}

#endif //BTools_FLOWCONFIGINPUT_H

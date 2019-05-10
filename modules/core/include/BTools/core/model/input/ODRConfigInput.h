#ifndef BTools_FLOWCONFIGINPUT_H
#define BTools_FLOWCONFIGINPUT_H

#include <BTools/core/interface/IFlowProfile.h>

namespace BTools
{
    namespace Core
    {
        struct ODRConfigInput
        {
            typedef SCaBOliC::Core::ODRModel::ApplicationCenter ApplicationCenter;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode ApplicationMode;
            typedef SCaBOliC::Core::ODRModel::CountingMode CountingMode;
            typedef SCaBOliC::Core::ODRModel::SpaceMode SpaceMode;
            typedef SCaBOliC::Core::ODRModel::NeighborhoodType NeighborhoodType;
            typedef SCaBOliC::Core::ODRModel::LevelDefinition LevelDefinition;
            typedef SCaBOliC::Core::ODRModel::StructuringElementType StructuringElementType;

            ODRConfigInput(ApplicationCenter ac,
                           CountingMode cm,
                           SpaceMode sm,
                           int levels,
                           LevelDefinition ld,
                           NeighborhoodType nt,
                           StructuringElementType seType,
                           bool optInApplicationRegion):applicationCenter(ac),
                                                        countingMode(cm),
                                                        spaceMode(sm),
                                                        levels(levels),
                                                        levelDefinition(ld),
                                                        neighborhood(nt),
                                                        seType(seType),
                                                        optInApplicationRegion(optInApplicationRegion)
            {}

            bool operator==(const ODRConfigInput& other) const
            {
                return other.levels==this->levels && other.neighborhood==this->neighborhood
                       && other.applicationCenter==this->applicationCenter
                       && other.countingMode==this->countingMode
                       && other.spaceMode==this->spaceMode
                       && other.seType==this->seType
                       && other.optInApplicationRegion==this->optInApplicationRegion;

            }

            const int levels;
            const NeighborhoodType neighborhood;
            const ApplicationCenter applicationCenter;
            const CountingMode countingMode;
            const SpaceMode spaceMode;
            const LevelDefinition levelDefinition;
            const StructuringElementType seType;

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
        typedef ODRConfigInput::ApplicationCenter ApplicationCenter;
        typedef ODRConfigInput::CountingMode CountingMode;
        typedef ODRConfigInput::SpaceMode  SpaceMode;
        typedef SCaBOliC::Core::ODRModel::LevelDefinition LevelDefinition;

    private:
        size_t numId(const NeighborhoodType& nt) const{ return nt==NeighborhoodType::FourNeighborhood?0:1;}
        size_t numId(const ApplicationCenter& ac) const{ return ac==ApplicationCenter::AC_PIXEL?0:1; }
        size_t numId(const CountingMode& cm) const{ return cm==CountingMode::CM_PIXEL?0:1; }
        size_t numId(const SpaceMode& sm) const{ return sm==SpaceMode::Pixel?0:1; }
        size_t numId(const LevelDefinition& ld) const{ return ld==LevelDefinition::LD_CloserFromCenter?0:1; }
        size_t numId(bool bel) const{ return bel?1:0; }

    public:
        size_t operator()(const ODRConfigInput& oci) const
        {
            return numId(oci.neighborhood) + numId(oci.applicationCenter)*2 +
                   numId(oci.countingMode)*4 + numId(oci.spaceMode)*8 +
                   oci.levels*16 + numId(oci.levelDefinition)*32 +
                   numId(oci.optInApplicationRegion)*64;
        }

    };
}

#endif //BTools_FLOWCONFIGINPUT_H

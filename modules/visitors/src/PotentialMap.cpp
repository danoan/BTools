#include "BTools/visitors/PotentialMap.h"

using namespace BTools::Visitors;

void PotentialMap::gatherPotentialValues(PotentialValues& potentialValues,
                                         const OptimizationData &optData,
                                         const VariableMap& vm,
                                         const DigitalSet& optRegion)
{

    std::for_each(optRegion.begin(),optRegion.end(),[&potentialValues](Point p) mutable{potentialValues[p]=0;});
    for(auto it1=optRegion.begin();it1!=optRegion.end();++it1)
    {
        int var1 = vm.pim.at(*it1);
        for(auto it2=optRegion.begin();it2!=optRegion.end();++it2)
        {
            int var2 = vm.pim.at(*it2);
            if(var1==var2) potentialValues[*it1] += optData.localUTM.coeff(1,var1);
            else
            {
                int first = var1<var2?var1:var2;
                int second = var1<var2?var2:var1;
                assert(first<second);
                potentialValues[*it1]+= optData.localPTM.coeff(first,second);
            }
        }
    }
}

void PotentialMap::draw(const PotentialValues& pv,
                        const DigitalSet& optRegion,
                        const std::string& outputPath)
{
    assert(pv.size()>0);

    double max,min;
    max = pv.begin()->second;
    min = pv.begin()->second;

    double v;
    for(auto it=pv.begin();it!=pv.end();++it)
    {
        v = it->second;
        max = v>max?v:max;
        min = v<min?v:min;
    }


    DGtal::Board2D potentialMap;

    DIPaCUS::Properties::BoundingBox bb;
    optRegion.computeBoundingBox(bb.lb,bb.ub);
    Domain domain(bb.lb,bb.ub);

    potentialMap << domain;

    DGtal::GradientColorMap<double,
            DGtal::ColorGradientPreset::CMAP_GRAYSCALE> cmap_jet(min,max);

    potentialMap << DGtal::SetMode( optRegion.begin()->className(), "Paving" );
    std::string specificStyle = optRegion.begin()->className() + "/Paving";

    for(auto it=optRegion.begin();it!=optRegion.end();++it)
    {
        potentialMap << DGtal::CustomStyle( specificStyle,
                                             new DGtal::CustomColors(DGtal::Color::Black,
                                                                     cmap_jet( pv.at(*it) )));
        potentialMap << *it;
    }

    boost::filesystem::path p(outputPath);
    boost::filesystem::create_directories(p.remove_filename());

    potentialMap.saveSVG(outputPath.c_str(),200,200,10);

}

void PotentialMap::visit(const OptimizationData &optData,
                         const VariableMap &vm,
                         const ODRModel &odr)
{


    PotentialValues pv;
    gatherPotentialValues(pv,optData,vm,odr.optRegion);
    draw(pv,odr.optRegion,outputPath);

}
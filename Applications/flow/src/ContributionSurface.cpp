#include "ContributionSurface.h"

using namespace BTools::Application::Illustration;

ContributionSurface::ReverseVariableMap ContributionSurface::reverseVariableMap(const VariableMap &vm,
                                                           const ODRModel& odr)
{
    ReverseVariableMap rvm;
    const DigitalSet& optRegion = odr.optRegion;
    for(auto it=optRegion.begin();it!=optRegion.end();++it)
    {
        rvm[ vm.pim.at(*it) ] = *it;
    }

    return rvm;
}

void ContributionSurface::visit(const OptimizationData &od,
                                const VariableMap& vm,
                                const ODRModel& odr)
{
    ReverseVariableMap rvm = reverseVariableMap(vm,odr);

    ContributionMatrix contrM;
    int first,second;
    for(int i=0;i<od.numVars;++i)
    {
        ContributionVector contributionLine;
        for(int j=0;j<od.numVars;++j)
        {
            first = i<j?i:j;
            second = i<j?j:i;

            double value = od.localPTM.coeff(first,second);
            int x = rvm[j](0);
            int y = rvm[j](1);
            int z = i;

            contributionLine.push_back( Contribution(x,y,z,value) );

        }
        contrM.push_back(contributionLine);
    }

    std::ofstream ofs("gnudata.dat");
    ofs << generateGNUPlotData(contrM);
    ofs.flush();
    ofs.close();

}

std::string ContributionSurface::generateGNUPlotData(const ContributionMatrix &contrM)
{
    double max = fabs(contrM.begin()->begin()->value);
    for(auto it1=contrM.begin();it1!=contrM.end();++it1)
    {
        ContributionVector cline = *it1;
        for(auto it2=cline.begin();it2!=cline.end();++it2)
        {
            max = fabs(it2->value)>max?fabs(it2->value):max;
        }
    }

    std::string data="#Contribution Surface \n#X\tY\tZ\tC\n";
    for(auto it1=contrM.begin();it1!=contrM.end();++it1)
    {
        ContributionVector cline = *it1;
        for(auto it2=cline.begin();it2!=cline.end();++it2)
        {
            data+= std::to_string(it2->x); data+="\t";
            data+=std::to_string(it2->y); data+="\t";
            data+=std::to_string(it2->z); data+="\t";
            data+=std::to_string(it2->value); data+="\n";
        }
    }

    return data;
}
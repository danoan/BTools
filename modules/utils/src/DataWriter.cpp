#include "BTools/utils/DataWriter.h"

using namespace BTools::Utils;

void DataWriter::write(const OptOutput& optOutput,
                       std::ostream& os,
                       bool printHeader)
{
    const BCInput& bcInput = optOutput.bcInput;
    const ModelParameters& modelParameters = bcInput.modelParameters;
    int colLength=20;

    if(printHeader)
    {
        os << "Sq. Curv. Weigth: " << modelParameters.sqTermWeight << std::endl
           << "Length Weigth: " << modelParameters.lengthTermWeight << std::endl
           << "Data Weigth: " << modelParameters.dataTermWeight << std::endl
           << "Estimating Ball Radius: " << modelParameters.radius << std::endl;

        os << Utils::fixedStrLength(colLength,"Opt. Energy Value") << "\t"
           << Utils::fixedStrLength(colLength,"II Elastica") << "\t"
           << Utils::fixedStrLength(colLength,"MDCA Elastica") << "\t"
           << Utils::fixedStrLength(colLength,"Unlabeled") << "\n";
    }


    os << BTools::Utils::fixedStrLength(colLength,optOutput.optEnergyValue) << "\t"
       << BTools::Utils::fixedStrLength(colLength,optOutput.IIElasticaValue) << "\t"
       << BTools::Utils::fixedStrLength(colLength,optOutput.MDCAElasticaValue) << "\t"
       << BTools::Utils::fixedStrLength(colLength,optOutput.unlabeled) << std::endl;

}

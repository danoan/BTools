#include "BTools/io/writer/DataWriter.h"

namespace BTools{
namespace IO{
namespace Writer{

void write(const BCInput& bcInput,
           std::ostream& os,
           bool printHeader){
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


//    os << BTools::Utils::fixedStrLength(colLength,bcOutput.energySolution.energyValue) << "\t"
//       << BTools::Utils::fixedStrLength(colLength,bcOutput.IIElasticaValue) << "\t"
//       << BTools::Utils::fixedStrLength(colLength,bcOutput.MDCAElasticaValue) << "\t"
//       << BTools::Utils::fixedStrLength(colLength,bcOutput.energySolution.unlabeled) << std::endl;
}


}
}
}


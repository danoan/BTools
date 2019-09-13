#include "BTools/utils/DataWriter.h"

using namespace BTools::Utils;

std::string DataWriter::resolveQPBOSolverType(QPBOSolverType solverType)
{
    switch(solverType)
    {
        case QPBOSolverType::Simple:
            return "Simple";
        case QPBOSolverType::ImproveProbe:
            return "Improve-Probe";
        case QPBOSolverType::Improve:
            return "Improve";
        case QPBOSolverType::Probe:
            return "Probe";
        default:
            throw std::runtime_error("Solver not recognized!");
    }
}

void DataWriter::write(const OptOutput& optOutput,
                       std::ostream& os,
                       bool printHeader)
{
    const BCFlowInput::BCConfigInput& bcInput = optOutput.bcFlowInput.bcInput;
    int colLength=20;

    if(printHeader)
    {
        os << "Sq. Curv. Weigth: " << bcInput.sqTermWeight << std::endl
           << "Length Weigth: " << bcInput.lengthTermWeight << std::endl
           << "Data Weigth: " << bcInput.dataTermWeight << std::endl
           << "Estimating Ball Radius: " << bcInput.radius << std::endl
           << "Solver Type: " << resolveQPBOSolverType(bcInput.solverType) << "\n" << std::endl;

        os << Utils::fixedStrLength(colLength,"Input") << "\t"
           << Utils::fixedStrLength(colLength,"Opt. Energy Value") << "\t"
           << Utils::fixedStrLength(colLength,"II Elastica") << "\t"
           << Utils::fixedStrLength(colLength,"MDCA Elastica") << "\t"
           << Utils::fixedStrLength(colLength,"Unlabeled") << "\n";
    }


    os << Utils::fixedStrLength(colLength,optOutput.bcFlowInput.inputName) << "\t";

    os << BTools::Utils::fixedStrLength(colLength,optOutput.optEnergyValue) << "\t"
       << BTools::Utils::fixedStrLength(colLength,optOutput.IIElasticaValue) << "\t"
       << BTools::Utils::fixedStrLength(colLength,optOutput.MDCAElasticaValue) << "\t"
       << BTools::Utils::fixedStrLength(colLength,optOutput.unlabeled) << std::endl;

}

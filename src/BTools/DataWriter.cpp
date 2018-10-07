#include "BTools/DataWriter.h"

using namespace BTools;

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


void DataWriter::write(const Study& study,
                       std::ostream& os)
{
    os << "******Study: " << study.studyName << "***********\n\n";

    bool printHeader=true;
    for(auto it=study.vectorOfOptOutput.begin();it!=study.vectorOfOptOutput.end();++it)
    {
        write(*it,os,printHeader);
        printHeader=false;
    }

    os << "\n" << std::endl;
}

void DataWriter::writeRect(const SeedSequenceInput& dataToWrite,std::ofstream& ofs)
{
    const std::vector<cv::Rect>& vroi = dataToWrite.vectorOfROI;
    ofs << vroi.size() << std::endl;
    for(auto it=vroi.begin();it!=vroi.end();++it)
    {
        ofs << it->x << " ";
        ofs << it->y << " ";
        ofs << it->width << " ";
        ofs << it->height << " ";
        ofs << std::endl;
    }
}

void DataWriter::writeMask(const SeedSequenceInput& dataToWrite,std::ofstream& ofs)
{
    const SeedSequenceInput::VectorOfSequenceOfPoints& vsp = dataToWrite.vsp;
    ofs << vsp.size() << std::endl;
    for(auto itV=vsp.begin();itV!=vsp.end();++itV)
    {
        ofs << itV->size() << std::endl;
        for(auto itS=itV->begin();itS!=itV->end();++itS)
        {
            ofs << itS->x << " "
                << itS->y << std::endl;
        }
    }
}

void DataWriter::write(const SeedSequenceInput& dataToWrite,
           std::string outputFilepath)
{
    std::ofstream ofs(outputFilepath);

    ofs << dataToWrite.imgFilePath << std::endl;
    ofs << dataToWrite.width << " "
        << dataToWrite.height << std::endl;

    writeRect(dataToWrite,ofs);
    writeMask(dataToWrite,ofs);

    ofs.close();
}

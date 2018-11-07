#include "AroundBoundaryReasoning.h"
#include "ElasticaProblem/ElasticaProblem.h"

namespace BTools
{
    namespace Application
    {
        std::string projectDir = PROJECT_DIR;
        std::string imageDir = projectDir + "/images";
        std::string outputDir = projectDir + "/output";
    }
}

using namespace BTools::Application::Illustration;

int main(int argc, char* argv[])
{
    //AroundBoundaryReasoning abr(outputDir + "/illustration/ab-reasoning");

    //ElasticaProblem::testElasticaInput();
    ElasticaProblem::example();

    return 0;
}
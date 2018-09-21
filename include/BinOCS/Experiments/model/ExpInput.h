#ifndef BINOCS_EXPERIMENTS_EXPINPUT_H
#define BINOCS_EXPERIMENTS_EXPINPUT_H

namespace BinOCS
{
    namespace Experiments
    {
        struct ExpInput
        {
            int maxIterations;
            unsigned long int estimatingBallRadius;
            double dataTermWeight;
            double sqTermWeight;
            double lengthTermWeight;

            std::string outputFolder;
        };
    }
}
#endif //BINOCS_EXPERIMENTS_EXPINPUT_H

#include "BTools/utils/strUtils.h"

using namespace BTools;

std::string Utils::fixedStrLength(int l,double v)
{
    std::string out = std::to_string(v);
    while(out.length()<l) out += " ";

    return out;
}

std::string Utils::fixedStrLength(int l,std::string str)
{
    std::string out = str;
    while(out.length()<l) out += " ";

    return out;
}

std::string Utils::nDigitsString(int num, int digits)
{
    std::string s = "";
    int numSize = num==0?1:log10( abs(num) ) + 1;
    int lZero = digits - numSize;
    while(lZero>0)
    {
        s+=std::to_string(0);
        --lZero;
    }
    s+=std::to_string(num);
    return s;
}
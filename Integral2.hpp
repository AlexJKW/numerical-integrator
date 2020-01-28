#include "IntegralInterface.hpp"

class Integral2: public IntegralInterface
{
    private:
        //Define private methods
        double ComputeIntegrand(const double x) const;
        double ComputeAnalyticIntegral() const;
};

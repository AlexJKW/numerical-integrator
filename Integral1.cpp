#include "Integral1.hpp"
#include <cmath>

double Integral1::ComputeIntegrand(const double x) const
{
    return cos(x); //Return integrand
}

double Integral1::ComputeAnalyticIntegral() const
{
    return sin(1); //Return exact integral
}

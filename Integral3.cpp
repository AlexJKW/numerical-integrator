#include "Integral3.hpp"
#include <cmath>

double Integral3::ComputeIntegrand(const double x) const
{
    return (1./pow(x+0.1,2))*sin(1/(x+0.1)); //Return integrand
}

double Integral3::ComputeAnalyticIntegral() const
{
    return cos(1./1.1)-cos(1./0.1); //Return exact integral
}

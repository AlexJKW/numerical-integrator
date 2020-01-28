#include "Integral2.hpp"
#include <cmath>

double Integral2::ComputeIntegrand(const double x) const
{
    return pow(x,1./2.); //Return integrand
}
double Integral2::ComputeAnalyticIntegral() const
{
    return 2./3.; //Return exact integral
}

#include "ClenshawCurtis.hpp"
#include <string>
#include <cmath>
#include <iostream>

ClenshawCurtis::ClenshawCurtis(IntegralInterface& anIntegral,
            const double xmin, const double xmax,
            const int initPanels, const int maxPanels,
            const int nodes, const double tolerance,
            const std::string outputFileName)
{
    mpIntegral = &anIntegral; //Initialise members as given by specialised constructor
    mXmin = xmin;
    mXmax = xmax;
    mInitPanels = initPanels;
    mMaxPanels = maxPanels;
    mNodes = nodes;
    mTolerance = tolerance;
}

double ClenshawCurtis::IntegratePanel(const double xmin, const double h)
{
    int N = mNodes; //Initialise variables
    double x[N+1];
    double w[N+1];
    double c = 0;
    double b = 0;
    double sum;
    double result = 0;

    for(int k=0;k<N+1;k++)
    {
        //Compute x value
        x[k] = xmin + h/2.*(1.+cos((N-k)*M_PI/N));

        //Compute c value
        if(k==0 || k==N)
        {
            c = 1.;
        }
        else
        {
            c = 2.;
        }

        //Compute the sum needed to calculate weights
        sum = 0.;
        for(int j=1;j<floor(N/2)+1;j++)
        {
            b = 2;
            if(j==N/2)
            {
                b = 1; //Only case where b = 1
            }
            sum = sum + (b/(4*pow(j,2)-1))*cos(2*k*j*M_PI/N); //Compute sum
        }

        w[k] = c*h/(2*N)*(1-sum); //Compute weight value

        result = result + w[k]*mpIntegral->ComputeIntegrand(x[k]); //Compute approximation to integral

    }

    return result;

}

double ClenshawCurtis::EstimateError(const double onePanel, const double twoPanels)
{
    double orderOfAccuracy;
    if(mNodes % 2 == 0)
    {
        orderOfAccuracy = mNodes + 1; //If N is even
    }
    else
    {
        orderOfAccuracy = mNodes; //If N is odd
    }
    return (twoPanels-onePanel)/(pow(2,orderOfAccuracy)-1); //Return error estimate
}

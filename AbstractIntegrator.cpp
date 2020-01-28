#include "AbstractIntegrator.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

void AbstractIntegrator::CompositeIntegration()
{
    double h = (mXmax-mXmin)/double(mInitPanels); //Initialise variables
    double x = mXmin;
    double approxIntegral = 0;
    double onePanel = 0;
    double twoPanels = 0;
    double errorEstimate = 0;
    double totalErrorEstimate = 0;

    for(int i=1;i<mInitPanels+1;i++)
    {
        onePanel = IntegratePanel(x,h); //Compute one panel approximation
        twoPanels = IntegratePanel(x,h/2.) + IntegratePanel(x+h/2,h/2); //Compute two panels approximation
        errorEstimate = EstimateError(onePanel,twoPanels); //Compute error estimate
        approxIntegral = approxIntegral + onePanel + errorEstimate; //Update extrapolated approximation
        totalErrorEstimate = totalErrorEstimate + errorEstimate; //Update global error estimate
        x = x + h;
    }

    double exactIntegral = mpIntegral->ComputeAnalyticIntegral(); //Compute exact integral
    mApproximation = approxIntegral; //Update public members
    mErrorEstimate = totalErrorEstimate;
    mActualError = fabs(approxIntegral-exactIntegral); //Compute actual error
}

void AbstractIntegrator::GlobalRefinement()
{
    CompositeIntegration(); //Compute extrapolated approximation
    while(fabs(mErrorEstimate) > mTolerance && mInitPanels <= mMaxPanels) //Check if error is small enough or we hit max panel number
    {
        CompositeIntegration(); //Compute extrapolated approximation
        cout << "M: " << mInitPanels << "   Approximation: " << mApproximation << " Estimated Error: " << mErrorEstimate << "   Actual Error: " << mActualError << "\n";
        mInitPanels = mInitPanels*2; //Halve number of panels
    }
}

void AbstractIntegrator::LocalRefinement()
{
    double E = 0; //Initialise variables
    double I = 0;
    int nPanels = mInitPanels;
    bool checksRequired = true;
    double h = (mXmax-mXmin)/double(mInitPanels); //Compute step size
    vector<bool> localChecks; //<vector> library used so we can easily resize vectors
    vector<double> xLeft;

    for(int i=0;i<mInitPanels;i++)
    {
        localChecks.push_back(true); //Fill localChecks with true boolean values
        xLeft.push_back(mXmin + i*h); //Compute xLeft values
    }

    int currentPanels; //Instantiate variables
    double localTOL;
    double onePanel, twoPanels, errorEstimate, approxIntegral;

    while(checksRequired && nPanels <= mMaxPanels) //While we still need to reach a tolerance somewhere or max number of panels reached
    {
        checksRequired = false; //Set checksRequired to be false
        localTOL = mTolerance*h/(mXmax-mXmin); //Compute local tolerance
        currentPanels = nPanels;
        for(int i=0;i<nPanels;i++)
        {
            if(localChecks[i] == true)
            {
                onePanel = IntegratePanel(xLeft[i],h); //Compute one panel approximation
                twoPanels = IntegratePanel(xLeft[i],h/2.) + IntegratePanel(xLeft[i]+h/2,h/2); //Compute two panels approximation
                errorEstimate = EstimateError(onePanel,twoPanels); //Compute error estimate
                approxIntegral = onePanel + errorEstimate; //Update extrapolated integral

                if(fabs(errorEstimate) < localTOL)
                {
                    E = E + errorEstimate; //Update global error estimate
                    I = I + approxIntegral; //Update global extrapolated approximation
                    localChecks[i] = false; //No checks needed in this area of domain
                }
                else
                {
                    currentPanels = currentPanels + 1; //Increment number of panels
                    localChecks.push_back(true); //Need more checks locally
                    checksRequired = true; //Need more checks globally
                    xLeft.push_back(xLeft[i] + h/2); //Compute new xLeft value
                }
            }
        }
        nPanels = currentPanels; //Update number of panels
        h = h/2; //Halve step size
    }

    mApproximation = I; //Update public members
    mErrorEstimate = E;
    mNpanels = nPanels;

    ofstream myfile; //Define output stream
    myfile.open("Q4.dat"); // Open file
    assert(myfile.is_open()); // Check file is open

    int length = xLeft.size(); //Compute length of vector

    for(int i=0;i<length-1;i++)
    {
        h = xLeft[i+1] - xLeft[i]; //Compute step size
        onePanel = IntegratePanel(xLeft[i],h); //Compute one panel approximation
        twoPanels = IntegratePanel(xLeft[i],h/2.) + IntegratePanel(xLeft[i]+h/2,h/2); //Compute two panel approximation
        errorEstimate = EstimateError(onePanel,twoPanels); //Update error estimate
        approxIntegral = onePanel + errorEstimate; //Update extrapolated approximation
        myfile << "Panel: " << i+1 << " xLeft: " << xLeft[i] << "    xRight: " << xLeft[i+1] << "    Integrand: " << approxIntegral << "\n"; //Write results to file
    }

    myfile.close(); //Close the file

}

//Getters
double AbstractIntegrator::GetApproximation()
{
    return mApproximation;
}

double AbstractIntegrator::GetErrorEstimate()
{
    return mErrorEstimate;
}

double AbstractIntegrator::GetActualError()
{
    return mActualError;
}

int AbstractIntegrator::GetNpanels()
{
    return mNpanels;
}

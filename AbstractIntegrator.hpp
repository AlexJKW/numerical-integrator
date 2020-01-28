#ifndef ABSTRACTINTEGRATORHEADERDEF
#define ABSTRACTINTEGRATORHEADERDEF

#include "IntegralInterface.hpp"

class AbstractIntegrator
{
    public:
        //Define public methods
        virtual double IntegratePanel(const double xmin, const double h ) = 0;

        void CompositeIntegration();

        virtual double EstimateError(const double onePanel, const double twoPanels) = 0;

        void GlobalRefinement();

        void LocalRefinement();

        //Get Methods
        double GetApproximation();

        double GetErrorEstimate();

        double GetActualError();

        int GetNpanels();

    protected:
        //Define protected members
        double mXmin, mXmax;
        int mInitPanels, mMaxPanels, mNodes;
        IntegralInterface* mpIntegral;
        double mTolerance;

    private:
        double mApproximation, mErrorEstimate, mActualError;
        int mNpanels;
};

#endif

#ifndef CLENSHAWCURTISHEADERDEF
#define CLENSHAWCURTISHEADERDEF

#include<string>
#include "AbstractIntegrator.hpp"

class ClenshawCurtis: public AbstractIntegrator
{
    public:
        ClenshawCurtis(IntegralInterface& anIntegral,
            const double xmin, const double xmax,
            const int initPanels, const int maxPanels,
            const int nodes, const double tolerance,
            const std::string outputFileName = "output.dat"); //Define specialized constructor

        //Define public methods
        double IntegratePanel(const double xmin, const double h);

        double EstimateError(const double onePanel, const double twoPanels);

};

#endif

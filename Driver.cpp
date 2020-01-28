#include "Integral1.hpp"
#include "Integral2.hpp"
#include "Integral3.hpp"
#include "SimpsonRule.hpp"
#include "ClenshawCurtis.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "QUESTION 5) Clenshaw-Curtis Quadrature Rule with 10 panels and 3 nodes: \n\n";

    Integral1 I1; //Instantiate integral objects
    Integral2 I2;
    Integral3 I3;

    double xmin = 0; //Initialise variables
    double xmax = 1;
    const int initPanels = 10;
    int maxPanels = 1000000;
    const int nodes = 3;
    double tolerance = pow(10,-10);

    ClenshawCurtis Int1(I1,xmin,xmax,initPanels,maxPanels,nodes,tolerance); //Initialise ClenshawCurtis objects for each integral
    ClenshawCurtis Int2(I2,xmin,xmax,initPanels,maxPanels,nodes,tolerance);
    ClenshawCurtis Int3(I3,xmin,xmax,initPanels,maxPanels,nodes,tolerance);

    cout << "----------- Integral 1 -----------\n";
    Int1.CompositeIntegration(); //Compute Clenshaw-Curtis approximation to integral 1
    cout << "Approximation: " << Int1.GetApproximation() << "   Actual Error: " << Int1.GetActualError() << "\n"; //Output results
    cout << "\n";
    cout << "----------- Integral 2 -----------\n";
    Int2.CompositeIntegration(); //Compute Clenshaw-Curtis approximation to integral 2
    cout << "Approximation: " << Int2.GetApproximation() << "   Actual Error: " << Int2.GetActualError() << "\n"; //Output results
    cout << "\n";
    cout << "----------- Integral 3 -----------\n";
    Int3.CompositeIntegration(); //Compute Clenshaw-Curtis approximation to integral 1
    cout << "Approximation: " << Int3.GetApproximation() << "   Actual Error: " << Int3.GetActualError() << "\n"; //Output results
    cout << "\n";

    double N[5] = {2,4,8,16,32}; //Consider various N values - here we double N each time
    ClenshawCurtis* testCC; //Dynamically allocated object

    ofstream myfile; //Define output stream
    myfile.open("Q5errors.dat"); // Open file
    assert(myfile.is_open()); // Check file is open

    myfile << "Integral 1 ------------\n";
    for(int i=0;i<5;i++)
    {
        testCC = new ClenshawCurtis(I1,xmin,xmax,initPanels,maxPanels,N[i],tolerance); //New ClenshawCurtis object with varied number of nodes
        testCC->CompositeIntegration(); //Compute approximation to integral 1
        myfile << "N: " << N[i] << "    E(N): " << testCC->GetActualError() << "\n"; //Write results to file
    }

    myfile << "\nIntegral 2 -----------\n";
    for(int i=0;i<5;i++)
    {
        testCC = new ClenshawCurtis(I2,xmin,xmax,initPanels,maxPanels,N[i],tolerance); //New ClenshawCurtis object with varied number of nodes
        testCC->CompositeIntegration(); //Compute approximation to integral 2
        myfile << "N: " << N[i] << "    E(N): " << testCC->GetActualError() << "\n"; //Write results to file
    }

    myfile << "\nIntegral 3 -----------\n";
    for(int i=0;i<5;i++)
    {
        testCC = new ClenshawCurtis(I3,xmin,xmax,initPanels,maxPanels,N[i],tolerance); //New ClenshawCurtis object with varied number of nodes
        testCC -> CompositeIntegration(); //Compute approximation to integral 3
        myfile << "N: " << N[i] << "    E(N): " << testCC->GetActualError() << "\n"; //Write results to file
    }

    myfile.close(); //Close the file

    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    /////////FOLLOWING CODE IS JUST TESTING////////////////
    //////////TO FIND THE N VALUE AT WHICH/////////////////
    /////////EACH INTEGRAL APPROXIMATION IS////////////////
    ////////////WITHIN TOLERANCE OF 10^-10/////////////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////

    cout << "We now find the number of nodes required to reach a tolerance smaller than 10^-10...\n";
    //double testError = 1.0;
    //double testNodes = 3;

    //while(testError > pow(10,-10))
    //{
    //    testCC = new ClenshawCurtis(I1,xmin,xmax,initPanels,maxPanels,testNodes,tolerance);
    //    testCC -> CompositeIntegration();
    //    testError = testCC -> GetActualError();
    //    testNodes = testNodes + 1;
    //}

    //TEST ABOVE GIVES N=4 TO REACH TOL OF 10^-10 FOR INTEGRAL 1
    cout << "Integral 1 - Number of nodes: " << 4 << "\n";
    testCC = new ClenshawCurtis(I1,xmin,xmax,initPanels,maxPanels,4,tolerance);
    testCC -> CompositeIntegration();
    cout << "Approximation: " << testCC->GetApproximation() << "   Actual Error: " << testCC->GetActualError() << "\n";

    //while(testError > pow(10,-10))
    //{
    //    testCC = new ClenshawCurtis(I2,xmin,xmax,initPanels,maxPanels,testNodes,tolerance);
    //    testCC -> CompositeIntegration();
    //    testError = testCC -> GetActualError();
    //    testNodes = testNodes + 1;
    //}

    //TEST ABOVE GIVES N=326 TO REACH TOL OF 10^-10 FOR INTEGRAL 2"
    cout << "Integral 2 - Number of nodes: " << 326 << "\n";
    testCC = new ClenshawCurtis(I2,xmin,xmax,initPanels,maxPanels,326,tolerance);
    testCC -> CompositeIntegration();
    cout << "Approximation: " << testCC->GetApproximation() << "   Actual Error: " << testCC->GetActualError() << "\n";
    //testError = 1.0;
    //testNodes = 3;

    //while(testError > pow(10,-10))
    //{
    //    testCC = new ClenshawCurtis(I3,xmin,xmax,initPanels,maxPanels,testNodes,tolerance);
    //    testCC -> CompositeIntegration();
    //    testError = testCC -> GetActualError();
    //    testNodes = testNodes + 1;
    //}

    //TEST ABOVE GIVES N=18 TO REACH TOL OF 10^-10 FOR INTEGRAL 3
    cout << "Integral 3 - Number of nodes: " << 18 << "\n";
    testCC = new ClenshawCurtis(I3,xmin,xmax,initPanels,maxPanels,18,tolerance);
    testCC -> CompositeIntegration();
    cout << "Approximation: " << testCC->GetApproximation() << "   Actual Error: " << testCC->GetActualError() << "\n";


    return 0;
}

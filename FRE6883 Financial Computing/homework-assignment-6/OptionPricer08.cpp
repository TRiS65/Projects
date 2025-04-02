#include "BinomialTreeModel02.h"
#include "Option08.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
using namespace fre;

int main()
{
    int N = 8;
    double U = 1.15125, D = 0.86862, R = 1.00545;
    double S0 = 106.00, K=100;

    BinomialTreeModel Model(S0, U, D, R);

    ofstream fout;
    fout.open("Results.txt"); 

    BinLattice<double> PriceTree(N);
    BinLattice<double> XTree(N);
    BinLattice<double> YTree(N);

    Call call(N, K);
    OptionCalculation callCalculation(&call);

    fout << "European call prices by PriceByCRR:" << fixed << setprecision(3) << callCalculation.PriceByCRR(Model) << endl << endl;
    fout << "European call prices by HW6 PriceByCRR:" << fixed << setprecision(3) << callCalculation.PriceByCRR(Model, PriceTree, XTree, YTree) << endl << endl;
    fout << "Stock positions in replicating strategy:"<< endl << endl;
    XTree.Display(fout);
    fout << "Money market account positions in replicating strategy:" << endl << endl;
    YTree.Display(fout);

    Put put(N, K);
    OptionCalculation putCalculation(&put);
    fout << "European put prices by PriceByCRR:" << fixed << setprecision(3) << putCalculation.PriceByCRR(Model) << endl << endl;
    fout << "European put prices by HW6 PriceByCRR:" << fixed << setprecision(3) << putCalculation.PriceByCRR(Model, PriceTree, XTree, YTree) << endl << endl;
    fout << "Stock positions in replicating strategy:"<< endl << endl;
    XTree.Display(fout);
    fout << "Money market account positions in replicating strategy:" << endl << endl;
    YTree.Display(fout);

    // BinLattice<double> CallPriceTree(N);
    // BinLattice<bool> CallStoppingTree(N);
    // cout << "American call option price = " << fixed << setprecision(2) << callCalculation.PriceBySnell(Model, CallPriceTree, CallStoppingTree) << endl;
    // cout << "American call price tree:" << endl << endl;
    // CallPriceTree.Display();
    // cout << "American call exercise policy:" << endl << endl;
    // CallStoppingTree.Display();

    // BinLattice<double> PutPriceTree(N);
    // BinLattice<bool> PutStoppingTree(N);
    // cout << "American put option price = " << fixed << setprecision(2) << putCalculation.PriceBySnell(Model, PutPriceTree, PutStoppingTree) << endl;
    // cout << "American put price tree:" << endl << endl;
    // PutPriceTree.Display();
    // cout << "American put exercise policy:" << endl << endl;
    // PutStoppingTree.Display();

    return 0;
}
/*

*/

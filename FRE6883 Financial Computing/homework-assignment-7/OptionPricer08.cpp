#include "BinomialTreeModel02.h"
#include "BlackScholesModel01.h"
#include "Option08.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace fre;

int main()
{
    int N = 8;
    // double U = 1.15125, D = 0.86862, R = 1.00545;
    double S0 = 106.00, K=100;
    double r=0.058;
    double sigma=0.46;
    double T=(double)9/12;
    BSModel bsModel(S0, r, sigma, T, N);
    BinomialTreeModel Model = bsModel.createBinModel();

    cout << setiosflags(ios::fixed) << setprecision(5);
    cout << "S0 = " << S0 << endl;
    cout << "r = " << r << endl;
    cout << "sigma = " << sigma << endl;
    cout << "T = " << T << endl;
    cout << "K = " << K << endl;
    cout << "N = " << N << endl;
    cout << endl;
    cout << "U = " << Model.GetU() << endl;
    cout << "D = " << Model.GetD() << endl;
    cout << "R = " << Model.GetR() << endl;
    cout << endl;

    Call call(N, K);
    OptionCalculation callCalculation(&call);
    BinLattice<double> CallPriceTree(N);
    BinLattice<bool> CallStoppingTree(N);
    cout << "American call option price = " << fixed << setprecision(3) << callCalculation.PriceBySnell(Model, CallPriceTree, CallStoppingTree) << endl;
    // cout << "American call price tree:" << endl << endl;
    // CallPriceTree.Display();
    // cout << "American call exercise policy:" << endl << endl;
    // CallStoppingTree.Display();

    return 0;
}
/*
S0 = 106.00000
r = 0.05800
sigma = 0.46000
T = 0.75000
K = 100.00000
N = 8

U = 1.15125
D = 0.86862
R = 1.00545

American call option price = 21.682

*/

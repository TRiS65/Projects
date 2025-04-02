#include "BinomialTreeModel02.h"
#include "Option05.h"
#include "DoubleDigitOpt.h"
#include "ButterflySpread.h"
#include "StrangleSpread.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace fre;

int main()
{
    int N = 8;
    double U = 1.15125, D = 0.86862, R = 1.00545;
    double S0 = 106.00, K1 = 100.00, K2 = 110;
    BinomialTreeModel Model(S0, U, D, R);

    DoubDigitOpt Doub(N, K1, K2);
    OptionCalculation DoubCalculation(&Doub);
    cout << "European double digit option price =  "<< fixed << setprecision(2) << DoubCalculation.PriceByCRR(Model) << endl;

    Strangle Strg(N, K1, K2);
    OptionCalculation StrgCalculation(&Strg);
    cout << "European strangle option price =  "<< fixed << setprecision(2) << StrgCalculation.PriceByCRR(Model) << endl;
    
    Butterfly Btf(N, K1, K2);
    OptionCalculation BtfCalculation(&Btf);
    cout << "European butterfly option price =  "<< fixed << setprecision(2) << BtfCalculation.PriceByCRR(Model) << endl;

    return 0;
}
/*

European double digit option price =  0.26
European strangle option price =  28.39
European butterfly option price =  1.04

*/

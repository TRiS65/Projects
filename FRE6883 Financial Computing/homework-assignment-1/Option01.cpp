#include "Option01.h"
#include "BinomialTreeModel.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace fre {
    double PriceByCRR(double S0, double U, double D, double R, unsigned int N, double K)
    {
        double q = RiskNeutProb(U, D, R);
        double Price[N+1];
        double Result = 0.0;
        for (unsigned int i = 0; i < sizeof(Price) / sizeof(Price[0]); i++)
        {
            Price[i] = 0.0;
        }
        for (unsigned int i = 0; i <= N; i++)
        {
            Price[i] = CallPayoff(CalculateAssetPrice(S0, U, D, N, i), K);
        }
        for (unsigned int i = 0; i <= N; i++)
        {
            Result += Combination(N,i) * pow(q,i) * pow(1-q,N-i) * Price[i];
            // cout << "result=" << Result << endl;
            // tgamma(n) = (n-1)!

            // for (int i = 0; i <= n; i++)
            // {
            //     Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) / R;
            // }
        }
        // return Price[0];
        Result /= pow(R,N);
        return Result;
    }

    double CallPayoff(double z, double K)
    {
        if (z > K) return z - K;
        return 0.0;
    }

    int Combination(unsigned int n,unsigned int r)
    {
        int A = 1;
        for (unsigned int i = 2; i <= r; i++)
        {
            A *= i;
        }
        int B = 1;
        for (unsigned int i = n-r+1; i <= n; i++)
        {
            B *= i;
        }
        // cout << n<<","<< r<< ","<< A<<","<< B<<","<< B/A <<endl;
        return B/A;
    } 
}

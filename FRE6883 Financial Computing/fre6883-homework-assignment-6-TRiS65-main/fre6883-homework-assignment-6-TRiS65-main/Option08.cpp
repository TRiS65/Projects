#include "Option08.h"
#include "BinomialTreeModel02.h"
#include "BinLattice02.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace fre {
    Option::~Option() {}
    double Call::Payoff(double z) const {
        if (z > K) return z - K;
        return 0.0;
    }
    double Put::Payoff(double z) const {
        if (z < K) return K - z;
        return 0.0;
    }
    double OptionCalculation::PriceByCRR(const BinomialTreeModel& Model){   
        double q = Model.RiskNeutProb();
        int N = pOption->GetN();
        vector<double> Price(N + 1);
        for (int i = 0; i <= N; i++){
            Price[i] = pOption->Payoff(Model.CalculateAssetPrice(N, i));
        }
        for (int n = N - 1; n >= 0; n--){
            for (int i = 0; i <= n; i++){
                Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) / Model.GetR();
            }
        }
        return Price[0];
    }
    double OptionCalculation::PriceByCRR(const BinomialTreeModel& Model, BinLattice<double>& PriceTree,BinLattice<double>& XTree,BinLattice<double>& YTree){
        double q = Model.RiskNeutProb();
        double R = Model.GetR();
        int N = pOption->GetN();
        double ContVal, X, Y;
        double H_u, H_d, S_u, S_d;
        for (int i = 0; i <= N; i++) {
            PriceTree.SetNode(N, i, pOption->Payoff(Model.CalculateAssetPrice(N, i)));
        }
        for (int n = N - 1; n >= 0; n--) {   
            for (int i = 0; i <= n; i++) { 
                H_u = PriceTree.GetNode(n + 1, i + 1);
                H_d = PriceTree.GetNode(n + 1, i);
                S_u = Model.CalculateAssetPrice(n+1, i+1);
                S_d = Model.CalculateAssetPrice(n+1, i);
                ContVal = (q * H_u + (1 - q) * H_d) / R;
                PriceTree.SetNode(n, i, ContVal);
                X = (H_u - H_d)/(S_u - S_d);
                XTree.SetNode(n, i, X);
                Y = (H_d - X * S_d)/ R;
                YTree.SetNode(n, i, Y);
            }
        }
        return PriceTree.GetNode(0, 0);
    }
    double OptionCalculation::PriceBySnell(const BinomialTreeModel& Model, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree){
        double q = Model.RiskNeutProb();
        int N = pOption->GetN();
        double ContVal = 0;
        for (int i = 0; i <= N; i++) {
            PriceTree.SetNode(N, i, pOption->Payoff(Model.CalculateAssetPrice(N, i)));
            StoppingTree.SetNode(N, i, 1);
        }
        for (int n = N - 1; n >= 0; n--) {   
            for (int i = 0; i <= n; i++) {   
                ContVal = (q * PriceTree.GetNode(n + 1, i + 1) + (1 - q) * PriceTree.GetNode(n + 1, i)) / Model.GetR();
                PriceTree.SetNode(n, i, pOption->Payoff(Model.CalculateAssetPrice(n, i)));
                StoppingTree.SetNode(n, i, 1);
                if (ContVal > PriceTree.GetNode(n, i)) {   
                    PriceTree.SetNode(n, i, ContVal);
                    StoppingTree.SetNode(n, i, 0);
                }
            }
        }
        return PriceTree.GetNode(0, 0);
    }
}

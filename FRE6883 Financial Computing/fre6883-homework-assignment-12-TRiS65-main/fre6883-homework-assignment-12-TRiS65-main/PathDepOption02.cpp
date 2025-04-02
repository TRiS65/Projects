#include "PathDepOption02.h"
#include <cmath>

namespace fre {
    void Rescale(SamplePath& S, double x, double k)
    {
        int m = S.size();
        for (int j = 0; j < m; j++)  S[j][k] = x * S[j][k];
        
    }
    
    double PathDepOption::PriceByMC(MCModel& Model, long N, double epsilon)
    {
        double H = 0.0;
        SamplePath S(m);
        int d = Model.GetS0().size();
        delta.resize(d);    // initialize delta
        Vector Heps(d);

        for (long i = 0; i < N; i++)
        {
            Model.GenerateSamplePath(T, m, S);
            H = (i * H + Payoff(S)) / (i + 1.0);
            for(int j = 0; j < d; j++){
                Rescale(S, 1.0 + epsilon,j);
                Heps[j] = (i * Heps[j] + Payoff(S)) / (i + 1.0);
                Rescale(S, 1/(1.0 + epsilon),j);
            }
        }

        Price = std::exp(-Model.GetR() * T) * H;
        for(int j = 0; j < d; j++){
            delta[j] = std::exp(-Model.GetR() * T) * (Heps[j] - H) / (Model.GetS0()[j] * epsilon);
        }

        return Price;
    }
    void PathDepOption::PrintDelta(){
        int d = delta.size();
        for(int i = 0; i < d; i++){
            cout << "delta[" << i << "] = " << delta[i] << endl;
        }
    }

    double ArthmAsianCall::Payoff(const SamplePath& S) const
    {
        double Ave = 0.0;
        int d = S[0].size();
        Vector one(d);
        for (int i = 0; i < d; i++) one[i] = 1.0;
        for (int k = 0; k < m; k++)
        {
            Ave = (k * Ave + (one ^ S[k])) / (k + 1.0);
        }
        if (Ave < K) return 0.0;
        return Ave - K;
    }
}

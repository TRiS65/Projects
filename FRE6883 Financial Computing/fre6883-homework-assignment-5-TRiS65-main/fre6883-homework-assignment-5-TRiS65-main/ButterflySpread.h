#include "Option05.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace fre {
	class Butterfly : public EurOption {
		private:
		double K1, K2; 
		public:
			Butterfly(int N_, double K1_, double K2_):EurOption(N_), K1(K1_), K2(K2_) {}
			~Butterfly() {}
			double Payoff(double z) const;
	};
    double Butterfly::Payoff(double z) const{
        double mean = (K1+K2)/2;
        if (z > K1 && z <= mean) return z-K1;
        if (z > mean && z <= K2) return K2-z;
        return 0.0;
    }

}

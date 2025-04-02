#include "Option05.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace fre {
	class Strangle : public EurOption {
		private:
		double K1, K2; 
		public:
			Strangle(int N_, double K1_, double K2_):EurOption(N_), K1(K1_), K2(K2_) {}
			~Strangle() {}
			double Payoff(double z) const;
	};
    double Strangle::Payoff(double z) const{
        if (z <= K1) return K1-z;
        if (z > K2) return z-K2;
        return 0.0;
    }

}

#include "Option05.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace fre {
	class DoubDigitOpt : public EurOption {
		private:
		double K1, K2; 
		public:
			DoubDigitOpt(int N_, double K1_, double K2_):EurOption(N_), K1(K1_), K2(K2_) {}
			~DoubDigitOpt() {}
			double Payoff(double z) const;
	};
    double DoubDigitOpt::Payoff(double z) const {
        if (K1 < z && z < K2) return 1.0;
        return 0.0;
    }

}

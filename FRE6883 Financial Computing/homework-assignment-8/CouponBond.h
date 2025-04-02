#pragma once
#include "NonlinearSolver02.h"
namespace fre {
class CpBond: public Function{
        private:
            double F, T, C;
        public:
            CpBond(double F_, double T_, double C_) :F(F_), T(T_), C(C_) {}
            double Value(double yield);
            double Deriv(double yield);
    };
}
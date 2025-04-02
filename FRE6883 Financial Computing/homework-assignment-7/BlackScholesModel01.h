#pragma once
#include "BinomialTreeModel02.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;


namespace fre {
    class BSModel{
        private:
            double S0, r, Sigma, T;
            int N;
        public:
            BSModel(): S0(0), r(0), Sigma(1),T(0),N(0) {}
            BSModel(double S0_, double r_, double Sigma_, double T_, int N_): S0(S0_), r(r_), Sigma(Sigma_), T(T_), N(N_) {}
            BSModel(const BSModel& BS) :S0(BS.S0), r(BS.r), Sigma(BS.Sigma), T(BS.T), N(BS.N) {}
			~BSModel() {}
            BinomialTreeModel createBinModel(){
                double h = T/N;
                double U = exp(Sigma*sqrt(h));
                double D = 1 / U;
                double R = exp(r*h);
                return BinomialTreeModel(S0, U, D, R);
            }
    };
}
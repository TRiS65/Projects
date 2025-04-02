#pragma once

namespace fre {
	//inputting and displaying option data
	int GetInputData(int& N, double& K);

	//pricing European option
	double* PriceByCRR(double S0, double U, double D, double R, int N, double K,
						double(*Payoff)(double z, double K));

	//computing call & put payoff
	double CallPayoff(double z, double K);
	double PutPayoff(double z, double K);

	double DigitCallPayoff(double z, double K);
	double DigitPutPayoff(double z, double K);
}
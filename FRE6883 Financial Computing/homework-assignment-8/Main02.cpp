#include <iostream>
#include <iomanip>
#include "Function02.h"
#include "NonlinearSolver02.h"
#include "CouponBond.h"
using namespace std;
using namespace fre;
int main() { 

    double F=100.0, T=3.0, C=1.2, P=98.56;
    double Acc=0.0001, LEnd=0.0, REnd=1.0, Guess=0.2;
	 
	 CpBond CpB(F,T,C);
	 NonlinearSolver solver(P, LEnd, REnd, Acc, Guess);

	 cout << "Yield by Bisect: " << fixed << setprecision(4) << solver.SolveByBisect(&CpB) << endl;
	 cout << "Yield by Newton-Raphson: " << fixed << setprecision(4) << solver.SolveByNR(&CpB) << endl;

	 return 0;
}
/*
Yield by bisection method: 0.0168
Yield by Newton-Raphson method: 0.0168
*/
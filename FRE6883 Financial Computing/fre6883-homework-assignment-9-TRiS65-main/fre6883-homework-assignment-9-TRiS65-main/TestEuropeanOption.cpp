// TestEuropeanOption.cpp
// Test program for the exact solutions of European options.
// (C) Datasim Component Technology BV 2003-2006
//

#include "EuropeanOption.hpp"
#include <iostream>
#include <math.h>

int main()
{
	char put[2] = {'P'};
	// char call[2] = {'C'};

	//Q1: Call option on a stock
	EuropeanOption callOption;
	cout << "Q1: Call option on a stock: " << callOption.Price() << endl;
	// cout << "    Delta on a call option: " << callOption.Delta() << endl;

	//Q2: Put option on a stock
	double U = 50.0;
	double K = 50.0;
	double T = 3.0/12;
	double r = 0.10;
	double sig = 0.30;
	double q = 0.00;		// Dividend yield: non dividend
	double b = r - q;

	EuropeanOption PutOption1(r, sig, K, T, U, b, put);

	cout << "Q2: Put option on a stock: " << PutOption1.Price() << endl;
	// cout << "    Delta on a put option: " << PutOption1.Delta() << endl;

	//Q3: Put option with dividend
	double divT = 2.0/12;
	double divDollar = 1.5;

	U = U - divDollar * exp(-r* divT);	// According to John Hull's Options, Futures, and Other Derivatives

	EuropeanOption PutOption2(r, sig, K, T, U, b, put);
	cout << "Q3: Put option with dividend: " << PutOption2.Price() << endl;
	// cout << "    Delta on a put option: " << PutOption2.Delta() << endl;

	return 0;
}

/*

Q1: Call option on a stock: 2.13293
Q2: Put option on a stock: 2.37561
Q3: Put option with dividend: 3.03039

*/

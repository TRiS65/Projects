// EuropeanOption2.hpp
//
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only. It has been 
// written for pedagogical reasons
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp


#include <string>
using namespace std;

class EuropeanOption
{
private:
	// Gaussian functions
	double n(double x) const;
	double N(double x) const;

	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double U;		// Current underlying price (e.g. stock, forward)
	double b;		// Cost of carry

	char* optType;
	//string optType;	// Option name (call, put)
	//string unam;	// Name of underlying asset
				

	// void init();	// Initialise all default values
	// void copy(const EuropeanOption& o2);

	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;
	double CallDelta() const;
	double PutDelta() const;
	double CallGamma() const;
	double PutGamma() const;
	double CallVega() const;
	double PutVega() const;

public:
	EuropeanOption();							// Default call option
	EuropeanOption(const EuropeanOption& option2);	// Copy constructor
	EuropeanOption(double r_, double sig_, double K_, double T_, double U_, double b_, char *const optType_);
	EuropeanOption (char *const optType_);	// Create option type
	virtual ~EuropeanOption();	

	EuropeanOption& operator = (const EuropeanOption& o2);

	double GetOptType() const;

	// Functions that calculate option price and sensitivities
	double Price() const;
	double Delta() const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)


};

#endif

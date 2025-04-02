#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class DefInt
{
    private:
        double a;
        double b;
        double (*f) (double);
    public:
        DefInt(): a(0), b(0), f(NULL){}
        DefInt(double str, double end, double (*func) (double)): a(str), b(end), f(func) {}
        DefInt(const DefInt& d): a(d.a), b(d.b), f(d.f){}
        ~DefInt(){}

        double ByTrapzoid(int N) const;
        double BySimpson(int N) const;
};
double DefInt :: ByTrapzoid(int N) const{
    double result = 0;
    double h = (b-a)/N;
    double x = a;
    for(int i = 1; i < N; i++){
        x += h;
        result += f(x);
    }
    result = (2 * result + f(a) + f(b)) * h / 2;
    return result;
}
double DefInt :: BySimpson(int N) const{
    if (N%2 == 1){
        cout << "N should be an even number for this method. ";
        return 0;
    }
    double result = 0.0;
    double h = (b-a)/N;
    double x = a;
    for(int i = 1; i < N; i++){
        x += h;
        if (i%2 == 1){ 
            result += 4 * f(x); 
        }else{
            result += 2 * f(x); 
        }
    }
    result = (result + f(a) + f(b)) * h / 3;
    return result;
}

double Function(double x)
{
    return x*x*x - x*x + 1;
}

int main()
{
    DefInt MyInt(1.0,2.0,Function);
    int N = 0;
    cout << "Subinterval N: "; cin >> N;
    cout << "Using Trapzoid Approximation: " << MyInt.ByTrapzoid(N) << endl;
    cout << "Using Simpson Approximation: " << MyInt.BySimpson(N) << endl;
    return 0;
}
/*
    Subinterval N: 100
    Using Trapzoid Approximation: 2.41673
    Using Simpson Approximation: 2.41667

    Subinterval N: 99
    Using Trapzoid Approximation: 2.41673
    Using Simpson Approximation: N should be an even number for this method. 0
*/
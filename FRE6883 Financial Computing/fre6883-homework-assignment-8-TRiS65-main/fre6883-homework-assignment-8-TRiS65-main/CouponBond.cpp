#include "CouponBond.h"
#include <cmath>
namespace fre {
    double CpBond::Value(double yield){
        double result = 0;
        int N = (int)T;
        for(int t = 1; t <= N; t++){
            result += exp(-yield*t);
        }
        result *= C;
        result += F * exp(-yield*T);
        return result;
    }
    double CpBond::Deriv(double yield){
        double result = 0;
        int N = (int)T;
        for(int t = 1; t <= N; t++){
            result += (-t) * exp(-yield*t);
        }
        result *= C;
        result += - T * F * exp(-yield*T);
        return result;
    }
}

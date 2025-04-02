CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

Main02: Main02.o CouponBond.o NonlinearSolver02.o
	$(CC) $(CFLAGS) -o Main02 Main02.o CouponBond.o NonlinearSolver02.o

Main02.o: Main02.cpp Function02.h NonlinearSolver02.h CouponBond.h
	$(CC) $(CFLAGS) -c Main02.cpp

NonlinearSolver02.o: Function02.h NonlinearSolver02.h NonlinearSolver02.cpp
	$(CC) $(CFLAGS) -c NonlinearSolver02.cpp
	
CouponBond.o: Function02.h CouponBond.cpp CouponBond.h
	$(CC) $(CFLAGS) -c CouponBond.cpp
	
clean:
	rm -rf Main02 *.o
	




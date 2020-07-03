#pragma once
#include <cmath>
#include <armadillo>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <string.h>
#include <conio.h>
#include <iomanip>
#include "Polynomial.h"
#include <time.h>  

constexpr double e = 1;//1 when in eV 1.6e-19C;
constexpr double m_e = 9.10938356e-31;
constexpr double hbar = 6.5821e-16;//eVs|||1.05459e-34Js;
constexpr double l0 = 1;// 1e-10; //=1A 
//IF WE PUT V IN eV, z in Angstroms, meff, G0 is just 2m0/hbar /hbar (in eV*s)
constexpr long double G0 = 2 * m_e * l0 * l0 * e / (hbar * hbar);//constant to normalize equation so we have undimensional variables
using namespace std;
//---------------------------------finite difference method------------------------------------------------------------
long double* setCoeffFinite(int rank);//coefficients for finite method with N+1 points
long double* setCoeffFinite(int rank, int points);//same but with given number of points
long double* tableFunFinite(long double(*function)(long double), long double step, long double x_i, long double x_f, int gFinite);//for tabeling function before differencing
long double differentiateFinite(int rank, long double step, long double* function, int pointNum, long double* coeff);//function to differenciate
//---------------------------------Integrals---------------------------------------------------------------------------
long double simpsonInt(double a, double b, double step, long double* function);
double simpsonInt(double a, double b, double step, arma::vec function);
//-----------------------------------Some helping functions-------------------------------------------------------------
long int factorial(int n);

//---------------------------------------------------------Numerical differential equations------------------------------------------------------------
arma::vec LanczosTridiag(int size, int eigenstatesNum, const arma::mat triDiagMat);
arma::vec multiplyMatrixVectorTridiag(const arma::mat triDiagMat, arma::vec vector);
//Lanczos method for tridiagonal matrix - I know that Lanczos is already tridiagonal
arma::vec ThomasTridiagAlghorithm(int size, double energy, const arma::mat& triDiagMat);
//for finding eigenvectors(O(n)) 

/*
Parameters
V[pointNum] - given potential
m[pointNum]- effective masses calculated before
eigenStatesNum- eigenstates number that we want to calculate
resultingFunctions[eigenStatesNum][pointNum] - table of functions the first is changing the function number, then the discretization goes
energies[eigenStatesNum] - energies in the system
step - step in discretization
pointNum - real discretization points
*/


void martinDeanSchroedingerChangingMass(std::vector<double> V, double* meff, int eigenStatesNum,bool wantHighest, std::vector<arma::vec>& resultingFunctions, arma::vec energies, const double step, int pointNum, double a);
//wantHighest is there if we want to get the highest eigenEnergies, not from the bottom
void martinDeanSchroedingerConstMass(std::vector<double> V, double* meff, int eigenStatesNum, std::vector<arma::vec> resultingFunctions, arma::vec energies, const double step, int pointNum, double a);

void martinDeanSchroedingerJumpingMass(std::vector<double> V, double* meff, int eigenStatesNum, bool wantHighest, std::vector<arma::vec> resultingFunctions, arma::vec energies, const double step, int pointNum, double a);


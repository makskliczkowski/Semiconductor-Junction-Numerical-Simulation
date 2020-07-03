#pragma once
#include "Parameters.h"
#include "Polynomial.h"
#include "Numerical_methods.h"
//--------------------------------------------------------------------------------WORK IN PROGRESSS--------------------------------------------------------------

arma::vec findEigValWithSturmTridiagSym(int pointNum, double eps, double a, double b, int sgn_a, int sgn_b, int eigNum, bool wantHighest, bool symetrizedOrNot, const arma::mat triDiagMat);
//function for finding given number of roots of a given polynomial for tridiagonal symetric matrix
//a,b -> interval, sgn_a,b number of sign changes and sgn_b-sgn_a will be number of zeros in given interval(pw. Sturm theorem)(when -1, need to calculate value again at this point, for recursion), energies will be roots, eigNum, number of roots)
int tridiagSymDeterminantDecomposNegative(bool symetrizedOrNot, double point, const arma::mat triDiagMat, int PointNum);
//function to quickly calculate the Sturm decomposition sign change number

double tridiagonalSymetricMatrixCharactPolynomial(int i, const vector<vector<double>> triDiagMat, double* meff, double point);
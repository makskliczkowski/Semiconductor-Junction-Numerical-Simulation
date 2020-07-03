#include "MethodsBisectionSchroedinger.h"
//---------------------------------------------------------------------------------NEEDS TO BE FINISHED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-----------------------------------------------

arma::vec findEigValWithSturmTridiagSym(int pointNum, double eps, double a, double b, int sgn_a, int sgn_b, int eigNum,bool wantHighest, bool symetrizedOrNot, const arma::mat triDiagMat)
{
	//double ap = a;
	//double bp = b;//helping points1
	double ap = a;
	double bp = b;//helping points1
	arma::vec energies(eigNum, arma::fill::zeros);
	int start =1;
	int end = eigNum;
	//now we check if the last value isn't bigger than our Vmax, if it is, then let's get the biggest possible if we want the big ones of course!
	int SIGNCHECKER = tridiagSymDeterminantDecomposNegative(symetrizedOrNot, b, triDiagMat, pointNum); //if -1 we need to calculate
	if (wantHighest == true) {
		if (eigNum < SIGNCHECKER) {
			start = SIGNCHECKER - eigNum + 1;
			end = SIGNCHECKER;
		}
		else {
			start = SIGNCHECKER;
			end = SIGNCHECKER;
		}
	}
	int helper = 0;
	for (int i = start; i <= end; i++) {
		/*We find interval a,b which contains ith eigenvalue. Then numbers of signs changed w(b) >= i and w (a)  < i. We then evaluate for c = a+b/2 -> so we need to count sign changes is the sequence
		if(w(a) >= i -> b=c
		else a = c*/
		int signa = sgn_a;
		int signb = sgn_b;
		if (signa == -1)
		{
			signa = tridiagSymDeterminantDecomposNegative(symetrizedOrNot, ap, triDiagMat, pointNum); //if -1 we need to calculate
		}
		if (signb == -1) {
			signb = tridiagSymDeterminantDecomposNegative(symetrizedOrNot, bp, triDiagMat, pointNum); //if -1 we need to calculate
		}
		double app = ap;
		double bpp = bp; //helping points2
		double cpp = 0;
		if (signb == 0) throw"There's no eigvalues smaller than b!\n";
		while (bpp - app > eps) {
			cpp = (bpp + app) / 2.0;
			int signcpp = tridiagSymDeterminantDecomposNegative(symetrizedOrNot, cpp, triDiagMat, pointNum);
			if (signcpp >= i) {
				bpp = cpp;//moving interval
				signb = signcpp;
			}
			else {
				app = cpp;//moving interval
				signa = signcpp;
			}
		}
		energies[helper] = (bpp+app)/2.0;
		//we know that the interval starts with this point now, because that is position of eigenvalue and they are increasing
		ap = energies[helper];
		helper++;
	}
	return energies;
}

int tridiagSymDeterminantDecomposNegative(bool symetrizedOrNot, double point, const arma::mat triDiagMat, int PointNum)
{
	//finding number of eigenvalues being less than point (STM)
	int numberOfChangedSigns = 0;
	int negative_values = 0;
	if (symetrizedOrNot == true) { //case changing mass
		double fim1 = 1.0;
		double fi = (triDiagMat(1, 1) - point);
		if (fi < 0) negative_values++;
		for (int i = 2; i < PointNum; i++) {//PointNum-1 decompositions
			fim1 = fi;
			double ai = triDiagMat(i, 1);
			//double bi = sqrt(triDiagMat(i, 0) * triDiagMat(i, 2));
			//fi = (ai - point) - (bi * bi / fim1);
			double fim2 = fim1;


			double bi = triDiagMat(i, 0);
			double cim1 = triDiagMat(i - 1, 2);
			fi = (ai - point) - (bi * cim1 / fim1);
			if (fi == 0) fi += abs(bi / DBL_MAX);
			if ((fi < 0 /*&& fim1 > 0)||(fi>0&&fim1 <0*/)) {
				//numberOfChangedSigns++;
				negative_values++;
			}
		}
	}
	else { //not changing mass
		double fim1 = 1.0;
		double fi = (triDiagMat(1, 1) - point);
		if (fi < 0) negative_values++;
		for (int i = 2; i < PointNum; i++) {//PointNum-1 decompositions
			double fim2 = fim1;
			fim1 = fi;
			double ai = triDiagMat(i,1);
			double bi = triDiagMat(i,0);
			fi = (ai - point) - (bi * bi /fim1);
			if (fi == 0) fi += abs(bi / DBL_MAX);
			if ((fi<0 /*&& fim1 > 0)||(fi>0&&fim1 <0*/)) {
				//numberOfChangedSigns++;
				negative_values++;
			}
		}
	}
	//return numberOfChangedSigns;
	return negative_values;
}


double tridiagonalSymetricMatrixCharactPolynomial(int i, const vector<vector<double>> triDiagMat, double* meff, double point) {
	//alpha is triDiagMat[i][1], beta triDiagMat[i][0]
	//	An Accelerated Bisection Method for the Calculation
	//	of Eigenvalues of a Symmetric Tridiagonal Matrix
	//	Herbert J.Bernstein Numer. Math. 43, 153-160 (1984) 
	//recurent function, (thinking about using polynomial class for quicker evaluation, must check it)
	double alpha = triDiagMat[i][1];
	double beta = triDiagMat[i][0];

	if (i == 0) {
		//Polynomial temp(0);
		//temp.setCoefficient(0, 1);
		//return temp;
		return 1;
	}
	if (i == 1) {
		//Polynomial temp(1);
		//temp.setCoefficient(0, alpha);
		//temp.setCoefficient(1, -1.0);
		return (alpha - point);
		//return temp;
	}
	if (i > 1) {
		Polynomial temp(1);
		temp.setCoefficient(0, alpha);
		temp.setCoefficient(1, -1.0);
		//return temp * tridiagonalSymetricMatrixCharactPolynomial(i - 1, triDiagMat, meff) - beta * beta * tridiagonalSymetricMatrixCharactPolynomial(i - 2, triDiagMat, meff);
		//SALEJDA-----------------------

		double cim1 = -meff[i - 1] - ((meff[i] - meff[i - 2]) / 4.0);
		double bi = -meff[i] + ((meff[i + 1] - meff[i - 1]) / 4.0);
		return (alpha - 1.0 - (bi * cim1 / tridiagonalSymetricMatrixCharactPolynomial(i - 1, triDiagMat, meff, point)));
	}
	//else return Polynomial(1);
	else return DBL_MAX;
}

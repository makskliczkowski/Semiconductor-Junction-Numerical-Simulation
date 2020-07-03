#include "Numerical_methods.h"
#include "MethodsBisectionSchroedinger.h"

//---------------------------------finite difference method------------------------------------------------------------
long double* tableFunFinite(long double (*function)(long double), long double step, long double x_i, long double x_f, int gFinite)
{
	int length = static_cast<int> ((x_f - x_i) / step);
	long double* forNumFunc = new long double[static_cast<int>(length) + 2 * gFinite];
	//calculate preboundaries for derivative
	long double stepper = -gFinite * step; //we begin at -g*step
	for (int i = 0; i < (length + 2 * gFinite); i++) {

		long double x = x_i + stepper;
		forNumFunc[i] = (function(x));
		//cout << "\t\t" << forNumFunc[i] << endl;
		stepper += step;
		//zaczynamy od -g *step
	}
	//we have more points in that table
	return forNumFunc;
}

long double* setCoeffFinite(int rank)
{
	int rankp = rank;
	if (rank % 2 != 0) {
		rankp++;
	}
	int g = static_cast<int>((rankp + 1) / 2);

	long double* coeff = new long double[int(2 * g) + 1];
	arma::mat matrix(int(2 * g) + 1, int(2 * g) + 1, arma::fill::zeros);
	arma::Col<int> vector(2 * g + 1, arma::fill::zeros);
	for (int i = 0; i < 2 * g + 1; i++) {
		for (int j = 0; j < 2 * g + 1; j++) {
			matrix(i, j) = pow((-g + j), i);
			if ((i) == 0 && g - j == 0) matrix(i, j) = 1;
			else if (i != 0 && g - j == 0) matrix(i, j) = 0;
		}
		if (i - rank == 0) vector[i] = factorial(rank);
	}
	//matrix.print("M=");
	//vector.print("V=");
	arma::vec tempo = arma::inv(matrix) * vector;
	for (int i = 0; i < 2 * g + 1; i++) {
		if (abs(tempo[i]) < 1e-2) tempo[i] = 0;
		coeff[i] = tempo[i];
	}
	return coeff;
}

long double* setCoeffFinite(int rank, int points)
{
	int g = static_cast<int>(points / 2);

	long double* coeff = new long double[points];
	arma::mat matrix(points, points, arma::fill::zeros);
	arma::Col<int> vector(points, arma::fill::zeros);
	for (int i = 0; i < points; i++) {
		for (int j = 0; j < points; j++) {
			matrix(i, j) = pow((-g + j), i);
			if ((i) == 0 && g - j == 0) matrix(i, j) = 1;
			else if (i != 0 && g - j == 0) matrix(i, j) = 0;
		}
		if (i - rank == 0) vector[i] = factorial(rank);
	}
	//	matrix.print("M=");
	//	vector.print("V=");
	arma::vec tempo = arma::inv(matrix) * vector;
	for (int i = 0; i < points; i++) {
		if (abs(tempo[i]) < 1e-2) tempo[i] = 0;
		coeff[i] = tempo[i];
	}
	return coeff;
}
//first method for the test finite derivatitvie method
long double differentiateFinite(int rank, long double step, long double* function, int pointNum, long double* coeff)
{
	//making a result for differentiating a function, we remenber that the function is tabled and begins later so we must consider that it's moved from our point which is in the middle
	long double* news = (coeff);
	if (news == nullptr) {
		news = setCoeffFinite(rank, pointNum);
	}
	long double result = 0.0;
	long double h = 1.0;
	for (int i = 0; i < rank; i++) {
		h = h * 1.0 / step;
	}
	int g = static_cast<int>(pointNum / 2);
	for (int i = 0; i < pointNum; i++) {

		//cout << "function[i]" << function[i] << "\t \t";
		result += news[i] * function[i];

		//cout << "result = this " << result << "+ " << endl;
		//we move it to the very left
		//mistake gets when h gets to big and exp cannot produce that much of a reliability
	}
	//cout << "result = " << result << "\t \t";
	//cout << "h*result = " << h*result <<endl  ;

	return h * result;
}
//------------------------------------integrals--------------------------------------------------------------------
long double simpsonInt(double a, double b, double step, long double* function)
{

	int n = static_cast<int>((b - a) / step);
	long double sum = function[0] + function[n];
	for (int i = 1; i < n - 1; i++) {
		if (i % 3 == 0) {
			sum = sum + 2 * function[i];
		}
		else {
			sum = sum + 3 * function[i];
		}
	}
	return sum * ((double(3) * step) / double(8));

}
double simpsonInt(double a, double b, double step, arma::vec function)
{

	int n = static_cast<int>((b - a) / step);
	double sum = function(0) + function(n-1);
	for (int i = 1; i < n - 1; i++) {
		if (i % 3 == 0) {
			sum = sum + 2 * function[i];
		}
		else {
			sum = sum + 3 * function[i];
		}
	}
	return sum * ((3.0 * step) / 8.0);
}
//----------------------------------helping functions--------------------------------------------------------------
long int factorial(int n) {
	if (n == 0) return 1;
	else return n * factorial(n - 1);
}

arma::vec multiplyMatrixVectorTridiag(const arma::mat triDiagMat, arma::vec vector) {
	arma::vec returner(vector.n_elem, arma::fill::zeros);

	returner[0] = triDiagMat(0,1) * vector[0] + triDiagMat(0,2) * vector[1];
	for (int i = 1; i < vector.n_elem-1; i++) {
		returner[i] = triDiagMat(i,0) * vector[i - 1] + triDiagMat(i,1) * vector[i] + triDiagMat(i,2) * vector[i + 1];
	}
	returner[returner.n_elem-1] = triDiagMat(returner.n_elem - 2,0) * vector[returner.n_elem - 2] + triDiagMat(returner.n_elem - 1,1) * vector[returner.n_elem - 1];
	return returner;
}
//HERE WE MULTIPLY TRIDIAGONAL MATRIX IN VECTOR FORM WITH VECTOR OF THE SAME SIZE AS DIAGONAL

arma::vec LanczosTridiag(int size, int eigenstatesNum, const arma::mat triDiagMat)
{
	//http://physics.bu.edu/~py502/lectures4/schrod.pdf
	//srand(time(NULL));
	arma::arma_rng::set_seed_random();  // set the seed to a random value
	int stepNumber;
	if (triDiagMat.n_rows < 350) stepNumber = static_cast<int>(triDiagMat.n_rows*26/31);
	else stepNumber = 350; //we will try to get fine convergence

	if (stepNumber < 2) return arma::vec();

	arma::vec eigenValues(stepNumber, arma::fill::zeros);
	arma::mat pseudoMatrix(stepNumber, stepNumber, arma::fill::zeros);
	arma::vec Psi0(size,arma::fill::randu);
	//Psi0.print("Psi0=");
	for (int i = 0; i < size; i++)Psi0(i) = Psi0(i) - 0.5;//create random vector first
	Psi0 = Psi0 / sqrt(cdot(Psi0, Psi0));
	//Psi0.print("Psi0-0.5I=");
	//BEGINNING---------FIRST ELEMENTS ABOVE LOOP ------------------------------------------------------------
	arma::vec tmp = multiplyMatrixVectorTridiag(triDiagMat, Psi0);//whole vector(can be devided into perpendicular and parallel parts)
	double ai = dot(Psi0, tmp);
	double bi = 0.0;
	arma::vec tmp2 = tmp - ai * Psi0;
	double bip1 = sqrt(dot(tmp2, tmp2));
	pseudoMatrix(0, 0) = ai;
	pseudoMatrix(0, 1) = bip1;
	//--------------------------LOOP-----------------------------------
	for (int i = 1; i < stepNumber - 1; i++) {
		//create new ith vector----------
		arma::vec Psii = tmp2 / bip1;
		//put on hamiltonian--------------
		tmp = multiplyMatrixVectorTridiag(triDiagMat, Psii);
		//--------H|phii> = bi|phi_i-1>+ai|phi_i>*bip1|phi_i+1>
		//and next goes getting all coefficients
		ai = dot(Psii, tmp);
		bi = bip1;// bi is bip1 from last step so we don't have to calculate it again
		tmp2 = tmp - (ai * Psii) - (bi * Psi0);//it will be for new Psii
		bip1 = sqrt(dot(tmp2, tmp2));
		pseudoMatrix(i, i - 1) = bi;
		pseudoMatrix(i, i) = ai;
		pseudoMatrix(i, i + 1) = bip1;
		//after writing to matrix we need to change psi_0(which is psi_i-1) to psii
		Psi0 = Psii;
	}
	//ENDING WE PUT LAST CONDITIONS------------------------------------------
	arma::vec Psii = tmp2 / bip1;
	//Psii.print();
	tmp = multiplyMatrixVectorTridiag(triDiagMat, Psii);
	//tmp.print("tmp = ");
	ai = dot(Psii, tmp);
	pseudoMatrix(stepNumber - 1, stepNumber - 2) = bip1;
	pseudoMatrix(stepNumber - 1, stepNumber - 1) = ai;
	//pseudoMatrix.print("Mat=");
	//-----------------------------------------------
	arma::mat eigvec;
	arma::eig_sym(eigenValues, eigvec, pseudoMatrix);
	return eigenValues;
}
//MUST FINISH!!!!!!!!!!!!!!!!!
arma::vec ThomasTridiagAlghorithm(int size, double energy, const arma::mat& triDiagMat) {
	//https://www.wikiwand.com/en/Tridiagonal_matrix_algorithm
	//for us mat= tridiag(ai,bi-energy,ci)
	//di = 0 for each i
	//we want to find x
	arma::vec A(size,arma::fill::zeros);
	arma::vec B(size,arma::fill::zeros);
	arma::vec C(size,arma::fill::zeros);
	arma::vec D(size, arma::fill::zeros);
	arma::vec X(size, arma::fill::zeros);
	A(0) = triDiagMat(0, 0) ;
	B(0) = triDiagMat(0, 1) - energy;
	C(0) = triDiagMat(0, 2);
	for (int i = 1; i < size; i++) {
		A(i) = triDiagMat(i, 0);
		B(i) = triDiagMat(i, 1) - energy;
		C(i) = triDiagMat(i, 2);
		std::cout << C(i) << endl;
		double W = A(i) / B(i - 1);
		B(i) = B(i) - W * C(i - 1);
		D(i) = D(i) - W * D(i - 1);
	}
	X(size - 1) = 1.0*D(size - 1) / B(size - 1);
	for (int i = size - 2; i >= 0; i--) {
		X(i) = 1.0*(D(i) - C(i) * X(i + 1)) / B(i);
	}
	//X.print("X=");
	return X;
	//BAAAAAAAAAAAAAAAAAAAAD NOT WOOOOOOOOOOORKING
}

//---------------------------------------------------------Numerical differential equations------------------------------------------------------------
//=========================================BISECTION METHOD===========================================================================
void martinDeanSchroedingerChangingMass(std::vector<double> V, double* meff, int eigenStatesNum, bool wantHighest, std::vector<arma::vec>& resultingFunctions, arma::vec energies, const double step,int pointNum, double a )
{
	//IT IS A SINGLE GRID METHOD http://przyrbwn.icm.edu.pl/APP/PDF/95/a095z6p02.pdf for parabolic potential 
	//https://www.wikiwand.com/en/Tridiagonal_matrix_algorithm Using Thomas algorithm for tridiagonal matrix
	//https://www.cmi.ac.in/~ksutar/NLA2013/iterativemethods.pdf - bisection method can be applied
	//we also try with LANCZOS
	//NOTE THAT OUR EFFECTIVE MASS IN PARAMETERS.H IS YET DIVIDED BY M0!!!
	/*
	Parameters
	V[pointNum] - given potential
	m[pointNum]- effective masses calculated before
	eigenStatesNum- eigenstates number that we want to calculate
	resultingFunctions[eigenStatesNum][pointNum] - table of functions the first is changing the function number, then the discretization goes
	energies[eigenStatesNum] - energies in the system
	step - step in discretization
	pointNum - real discretization points
	a- left point
	*/
	//---------files---------------------------------
	std::ofstream fileEn,fileWave;
	fileEn.setf(3, std::ios::floatfield);
	fileWave.setf(3, std::ios::floatfield);
	if (wantHighest == true) {
		fileEn.open("energiesVal.dat", std::ios::out);
		fileWave.open("wavefunctionsVal.dat", std::ios::out);
	}
	else {
		fileEn.open("energiesCond.dat", std::ios::out);
		fileWave.open("wavefunctionsCond.dat", std::ios::out);
	}

	if (!fileEn||!fileWave)
	{
		throw std::system_error(errno, std::system_category(), "failed to open ");
	}
	//-------------------------------------------------
	arma::mat triDiagMat(pointNum,3,arma::fill::zeros);//for our matrix problem to calculate (just 2 colums cause we create symetric)
	//arma::mat triDiagMatFull(pointNum, pointNum, arma::fill::zeros);//testing if results are fine
	arma::vec deltaPlus(pointNum, arma::fill::zeros);
	arma::vec deltaMinus(pointNum, arma::fill::zeros);
	double Vmin, Vmax;
	int Vmin_index, Vmax_index;
	double epsilon = 1e-12; //precision for bisection

	//initialize vector with 0's
	for (int i = 0; i < eigenStatesNum; i++) {
		resultingFunctions.push_back(arma::vec(pointNum, arma::fill::zeros));
	}
	//1e3 don't get that but let's go

	//----------finding minima and maxima of potential for out interval [a,b] for bisection--------------------------------
	Vmin_index = std::min_element(V.begin(), V.end()) - V.begin();
	Vmax_index = std::max_element(V.begin(), V.end()) - V.begin(); //findig extremas
	Vmax = V[Vmax_index];
	Vmin = V[Vmin_index];

	//------------------------------------------------------------------------------------------------------------------------
	//building matrix (vector form)------------------------------------------------------------------------------------------
	//we will hold just the bottom diagonal and use information that the spectrum of trid(bi,ai,ci) is equivalent to symetric tridiag matrix of trid(bi'=sqrt(bici),ai,bi') with our asumption for eff massses
	if (pointNum <= 2) throw"Damn, small number of points dawg";
//#pragma omp parallel for 
	//without normalizing units
	/*

	for (int i = 0; i < pointNum; i++)
	{
		double ai, bi, ci, wi, wip1, wim1;
		wi = 1.0 * hbar * hbar / (meff[i] * m_e);
		ai = 2 * wi + (step*step*V[i]);

		if (i == 0) {
			wip1 = 1 * hbar * hbar / (meff[i + 1]*m_e);
			wim1 = 0;// wip1;
			ci = -wi - ((wip1 - wim1) / 4.0);
			triDiagMat(i, 0) = 0.0;
			triDiagMat(i, 1) = ai;
			triDiagMat(i, 2) = ci;
		}
		else if (i == pointNum - 1) {
			wim1 = 1 * hbar * hbar / (meff[i - 1]*m_e);
			wip1 = 0;// wim1;
			bi = -wi + ((wip1 - wim1) / 4.0);
			ci = -wi - ((wip1 - wim1) / 4.0);
			triDiagMat(i, 0) = bi;
			triDiagMat(i, 1) = ai;
			triDiagMat(i, 2) = 0.0;
		}
		else {
			wim1 = 1.0 * hbar * hbar / (meff[i - 1]*m_e);
			wip1 = 1.0 * hbar * hbar / (meff[i + 1]*m_e);
			bi = -wi + ((wip1 - wim1) / 4.0);
			ci = -wi - ((wip1 - wim1) / 4.0);
			triDiagMat(i, 0) = bi;
			triDiagMat(i, 1) = ai;
			triDiagMat(i, 2) = ci;
		}
	}
	*/
	//with normalizing units
	Vmin = Vmin * step * step * G0; //normalizing ->non dim now
	Vmax = Vmax * step * step * G0 ;
	for (int i = 0; i < pointNum; i++)
	{
		double ai, bi, ci, wi, wip1, wim1;
		wi = 1.0 / meff[i];
		ai = 2.0 * wi + (V[i] * step * step * G0 );

		if (i == 0) {
			wip1 = 1.0 / meff[i + 1];
			wim1 = wip1;// wip1;
			ci = -wi - ((wip1 - wim1) / 4.0);
			triDiagMat(i,0) = 0.0;
			triDiagMat(i,1) = ai;
			triDiagMat(i, 2) = ci;
		}
		else if (i == pointNum - 1) {
			wim1 = 1.0 / meff[i - 1];
			wip1 = wim1;// wim1;
			bi = -wi + ((wip1 - wim1) / 4.0);
			ci = -wi - ((wip1 - wim1) / 4.0);
			triDiagMat(i, 0) = bi;
			triDiagMat(i, 1) = ai;
			triDiagMat(i,2 ) = 0.0;
		}
		else {
			wim1 = 1.0 / meff[i - 1];
			wip1 = 1.0 / meff[i + 1];
			bi = -wi + ((wip1 - wim1) / 4.0);
			ci = -wi - ((wip1 - wim1) / 4.0);
			triDiagMat(i, 0) = bi;
			triDiagMat(i, 1) = ai;
			triDiagMat(i, 2) = ci;
		}
	}
	
	//triDiagMat.print("triDiagMatrix=");
	// FULL MATRIX CREATION-----------------
	/*
	for (int i = 0; i < pointNum; i++)
	{
		double ai, bi, ci, wi, wip1, wim1;
		wi = 1.0 / meff[i];
		ai = 2.0 * wi + (V[i] * step * step * G0);
		if (i == 0) {
			wip1 = 1.0 / meff[i + 1];
			wim1 = wip1;// wip1;
			ci = -wi - ((wip1 - wim1) / 4.0);
			//triDiagMat(i, 0) = 0.0;
			triDiagMatFull(i, i) = ai;
			triDiagMatFull(i, i + 1) = ci;
		}
		else if (i == pointNum - 1) {
			wim1 = 1.0 / meff[i - 1];
			wip1 = wim1;// wim1;
			bi = -wi + ((wip1 - wim1) / 4.0);
			ci = -wi - ((wip1 - wim1) / 4.0);
			triDiagMatFull(i, i-1) = bi;
			triDiagMatFull(i, i) = ai;
			//triDiagMatFull(i, i+1) = 0.0;
		}
		else {
			wim1 = 1.0 / meff[i - 1];
			wip1 = 1.0 / meff[i + 1];
			bi = -wi + ((wip1 - wim1) / 4.0);
			ci = -wi - ((wip1 - wim1) / 4.0);
			triDiagMatFull.col(i)(i-1) = bi;
			triDiagMatFull.col(i)(i) = ai;
			triDiagMatFull.col(i)(i+1) = ci;
		}
	}
	*/
	//triDiagMatFull.print("triDiagFull");
	//-------------------------------------calculating energies-----------------------------------------------

	//findEigValWithSturmTridiagS;ym(pointNum,epsilon, Vmin, Vmax, -1, -1, energies, eigenStatesNum, true, triDiagMat, meff);//shall get all eigenvalues
	//arma::vec eigenvalues;
	//arma::eig_sym(eigenvalues, triDiagMatFull);
	//eigenvalues.print("valFull =");

	energies = findEigValWithSturmTridiagSym(pointNum, epsilon, Vmin, Vmax, -1, -1, eigenStatesNum,wantHighest,true, triDiagMat);
	//energies =  LanczosTridiag(pointNum, eigenStatesNum, triDiagMat);
	//std::cout << "Vmin = " << Vmin << " Vmax = " << Vmax << std::endl;
	//energies.print("energies num");
	//std::cout << "E DD = " << eigenvalues(0) << " " << eigenvalues(1) << endl;
	//std::cout << "eigval Num = " << energies(0) << endl;
	//std::cout << "eigVal DD = " << eigenvalues(0) << " " << eigenvalues(1) << " " << eigenvalues(2) << endl;
	//eigenvalues.print("valLan =");
	//AFTER THAT WE SHALL HAVE THE f_pointNum polynomial with corresponding eigenvalues, remember that eigenvalues are that of tylde, that epsilon~ = epislon/step/step
	//-------------------------------------calculating eigenfunctions---------------------------------------------------------
	//==============calculating deltas========================;========
	for (int j = 0; j < eigenStatesNum; j++) {
		int Np1 = pointNum - 1;
		resultingFunctions[j][0] = 0;//boundary conditions
		resultingFunctions[j][Np1] = 0; //boundary conditions
		fileEn <<  energies[j]/ (step * step * G0) <<std::endl;//PRINTING TO FILE-----------------
		int N = Np1 - 1;
		deltaPlus[Np1]=(1.0/(triDiagMat(Np1,1) - energies[j]));//Nth element -> for this we go like
		deltaMinus[0]=(1.0 / (triDiagMat(0,1) - energies[j]));//first element
		//calculating deltas------
		for (int i = 1; i < Np1; i++) {//here we calculate all deltas
			int i2= Np1 - i;//Because for delta Plus we go from behind
			double ai = triDiagMat(i, 1);
			double aj = triDiagMat(i2, 1);
			double cim1 = triDiagMat(i - 1, 2);
			double bi = triDiagMat(i, 0);
			double bjp1 = triDiagMat(i2 + 1, 0);
			double cj = triDiagMat(i2, 2);
			deltaMinus[i] = 1.0 / (ai - energies[j] -(bi*cim1 * deltaMinus[i - 1]));
			deltaPlus[i2] = 1.0 / (aj - energies[j] - (bjp1*cj* deltaPlus[i2 + 1]));
		}
		//deltaMinus.print("d-");
		//deltaPlus.print("d+");
		//std::reverse(deltaPlus.begin(), deltaPlus.end());//we need to reverse it -----------> MUST CHECK
		int k;
		//finding minimum-----------
		double convergence = DBL_MAX;//for minumum calculation
		for (int i = 1; i < Np1; i++) {//here we define deltas and look for k which holds the minimum for |bk^2deltaminus_k-1 + (ak-E)+b_k+1^2deltaPlus_k+1|
			double b_k = triDiagMat(i,0);
			double b_kp1 = triDiagMat(i + 1, 0);
			double a_k = triDiagMat(i,1);
			double c_k = triDiagMat(i,2);
			double c_km1 = triDiagMat(i - 1, 2);
			double absoluteVal = abs(-b_k * c_km1 * deltaMinus[i - 1] + (a_k - energies[j]) - c_k * b_kp1 * deltaPlus[i + 1]);
			if (absoluteVal <= convergence) {
				convergence = absoluteVal; //finding minimum
				k = i;
			}
		}
		//resultingFunctions.push_back(arma::vec(pointNum, arma::fill::zeros));
		resultingFunctions[j][k] = 1;
		//std::cout << k << std::endl;
		//BUILDING FUNCTIONS
		for (int i = k - 1; i >=0 ; i--) { 
			double ci = triDiagMat(i, 2);
			resultingFunctions[j][i] = -deltaMinus[i]* ci*resultingFunctions[j][i+1];
		}
		for (int i = k+1; i <=Np1; i++) {
			double bi = triDiagMat(i, 0);
			resultingFunctions[j][i] = -deltaPlus[i] * bi * resultingFunctions[j][i - 1];
		}
		resultingFunctions[j] = resultingFunctions[j] / sqrt((dot(resultingFunctions[j], resultingFunctions[j])));
		//deltaPlus = arma::vec(pointNum, arma::fill::zeros);
		//deltaMinus = arma::vec(pointNum, arma::fill::zeros);*/
	}
	for (int i = 0; i < pointNum; i++) {
		fileWave << i * step;
		for (int j = 0; j < eigenStatesNum; j++) {
			fileWave << "\t\t" << resultingFunctions[j][i]/  (sqrt(step));
		}
		fileWave << endl;
	}
	fileWave.close();
	fileEn.close();
}


void martinDeanSchroedingerJumpingMass(std::vector<double> V, double* meff, int eigenStatesNum, bool wantHighest, std::vector<arma::vec> resultingFunctions, arma::vec energies, const double step, int pointNum, double a) {

	//IT IS A SINGLE GRID METHOD http://przyrbwn.icm.edu.pl/APP/PDF/95/a095z6p02.pdf for parabolic potential 
//https://www.wikiwand.com/en/Tridiagonal_matrix_algorithm Using Thomas algorithm for tridiagonal matrix
//https://www.cmi.ac.in/~ksutar/NLA2013/iterativemethods.pdf - bisection method can be applied
//NOTE THAT OUR EFFECTIVE MASS IN PARAMETERS.H IS YET DIVIDED BY M0!!!
	//THIS TIME WE CALCULATE JUMP ON EFFECTIVE MASS AND SYMETRIZE THE MATRIX
/*
Parameters
V[pointNum] - given potential
m[pointNum]- effective masses calculated before
eigenStatesNum- eigenstates number that we want to calculate
resultingFunctions[eigenStatesNum][pointNum] - table of functions the first is changing the function number, then the discretization goes
energies[eigenStatesNum] - energies in the system
step - step in discretization
pointNum - real discretization points
a- left point
*/
//---------files---------------------------------
	std::ofstream fileEn, fileWave;
	fileEn.setf(3, std::ios::floatfield);
	fileWave.setf(3, std::ios::floatfield);
	if (wantHighest == true) {
		fileEn.open("energiesVal.dat", std::ios::out);
		fileWave.open("wavefunctionsVal.dat", std::ios::out);
	}
	else {
		fileEn.open("energiesCond.dat", std::ios::out);
		fileWave.open("wavefunctionsCond.dat", std::ios::out);
	}

	if (!fileEn || !fileWave)
	{
		throw std::system_error(errno, std::system_category(), "failed to open ");
	}
	//-------------------------------------------------
	arma::mat triDiagMat(pointNum, 3, arma::fill::zeros);//for our matrix problem to calculate (just 2 colums cause we create symetric)
	//arma::mat triDiagMatFull(pointNum, pointNum, arma::fill::zeros);//testing if results are fine
	arma::vec deltaPlus(pointNum, arma::fill::zeros);
	arma::vec deltaMinus(pointNum, arma::fill::zeros);
	double Vmin, Vmax;
	int Vmin_index, Vmax_index;
	double epsilon = 1e-12; //precision for bisection

	//initialize vector with 0's
	for (int i = 0; i < eigenStatesNum; i++) {
		resultingFunctions.push_back(arma::vec(pointNum, arma::fill::zeros));
	}
	//1e3 don't get that but let's go

	//----------finding minima and maxima of potential for out interval [a,b] for bisection--------------------------------
	Vmin_index = std::min_element(V.begin(), V.end()) - V.begin();
	Vmax_index = std::max_element(V.begin(), V.end()) - V.begin(); //findig extremas
	Vmax = V[Vmax_index];
	Vmin = V[Vmin_index];
	Vmin = Vmin * step * step * G0; //normalizing ->non dim now
	Vmax = Vmax * step * step * G0;
	//------------------------------------------------------------------------------------------------------------------------
	//building matrix (vector form)------------------------------------------------------------------------------------------
	//we will hold just the bottom diagonal and use information that the spectrum of trid(bi,ai,ci) is equivalent to symetric tridiag matrix of trid(bi'=sqrt(bici),ai,bi') with our asumption for eff massses
	if (pointNum <= 2) throw"Damn, small number of points dawg";
	//#pragma omp parallel for 
	triDiagMat(0, 1) = (1.0/meff[0]) + (V[0] * step * step * G0);
	for (int i = 1; i < pointNum; i++)
	{
		double ai, bi, ci, wi, wip1, wim1, bip1;
		bool jumping = false;
		wi = 1.0 / meff[i];
		bi = -wi;
		if (wi != (1.0 / meff[i - 1]) && i > 0) {
			double wim1 = 1.0 / meff[i-1];
			double wip1 = 1.0 / meff[i+1];
			wi = (wim1 + wip1) / 2.0; //jumping point

		}
		ai = 2 * wi + (V[i] * step * step * G0);
		triDiagMat(i, 0) = bi;
		triDiagMat(i, 1) = ai;
		triDiagMat(i-1, 2) = bi;
	}
	//triDiagMat.print("triDiagMatrix=");
	// FULL MATRIX CREATION-----------------
	/*
	triDiagMatFull(0, 1) = (1.0/meff[0]) + (V[0] * step * step * G0);
	for (int i = 1; i < pointNum; i++)
	{
		double ai, bi, ci, wi, wip1, wim1, bip1;
		bool jumping = false;
		wi = 1.0 / meff[i];
		bi = -wi;
		if (wi != (1.0 / meff[i - 1]) && i > 0) {
			double wim1 = 1.0 / meff[i-1];
			double wip1 = 1.0 / meff[i+1];
			wi = (wim1 + wip1) / 2.0; //jumping point

		}
		ai = 2 * wi + (V[i] * step * step * G0);
		triDiagMatFull(i, i-1) = bi;
		triDiagMatFull(i, i) = ai;
		triDiagMatFull(i-1, i-1+1) = bi;
	}
	*/
	//triDiagMatFull.print("triDiagFull");
	//-------------------------------------calculating energies-----------------------------------------------

	//arma::vec eigenvalues;
	//arma::eig_sym(eigenvalues, triDiagMatFull);
	//eigenvalues.print("valFull =");

	energies = findEigValWithSturmTridiagSym(pointNum, epsilon, Vmin, Vmax, -1, -1, eigenStatesNum, wantHighest, false, triDiagMat);
	std::cout << "Vmin = " << Vmin << " Vmax = " << Vmax << std::endl;
	std::cout << "eigval Num = " << energies(0) << endl;
	//eigenvalues.print("valLan =");
	//AFTER THAT WE SHALL HAVE THE f_pointNum polynomial with corresponding eigenvalues, remember that eigenvalues are that of tylde, that epsilon~ = epislon/step/step
	//-------------------------------------calculating eigenfunctions---------------------------------------------------------
	//==============calculating deltas========================;========
	for (int j = 0; j < eigenStatesNum; j++) {
		int Np1 = pointNum - 1;
		resultingFunctions[j][0] = 0;//boundary conditions
		resultingFunctions[j][Np1] = 0; //boundary conditions
		int N = Np1 - 1;
		fileEn << energies[j] / (step * step * G0) << std::endl;//PRINTING TO FILE-----------------
		deltaPlus[Np1] = (1.0 / (triDiagMat(Np1, 1) - energies[j]));//Nth element -> for this we go like
		deltaMinus[0] = (1.0 / (triDiagMat(0, 1) - energies[j]));//first element
		//cout << deltaMinus[1] << std::endl;
		//calculating deltas------
		for (int i = 1; i <= Np1; i++) {//here we calculate all deltas
			int i2 = Np1 - i;//Because for delta Plus we go from behind
			double ai = triDiagMat(i, 1);
			double aj = triDiagMat(i2, 1);
			double bi = triDiagMat(i, 0);
			double bjp1 = triDiagMat(i2 + 1, 0);
			deltaMinus[i] = 1.0 / (ai - energies[j] - (bi * bi * deltaMinus[i - 1]));

			deltaPlus[i2] = 1.0 / (aj - energies[j] - (bjp1 * bjp1 * deltaPlus[i2 + 1]));
			//cout << deltaPlus[i2] << "\t E = " << energies[j] << "aj = "<<aj << std::endl;
		}
		//deltaPlus[0] = 1.0 / (triDiagMat(0, 1)- energies[j] + triDiagMat(1,0) * triDiagMat(1, 0) * deltaPlus[1]);
		//deltaMinus[N] = 1.0 / (triDiagMat(N, 1) - energies[j] + triDiagMat(N, 0) * triDiagMat(N-1, 2) * deltaMinus[N-1]);
		//deltaMinus.print("d-");
		//deltaPlus.print("d+");
		//std::reverse(deltaPlus.begin(), deltaPlus.end());//we need to reverse it -----------> MUST CHECK
		int k;
		//finding minimum-----------
		double convergence = DBL_MAX;//for minumum calculation
		for (int i = 2; i < Np1 - 2; i++) {//here we define deltas and look for k which holds the minimum for |bk^2deltaminus_k-1 + (ak-E)+b_k+1^2deltaPlus_k+1|
			double b_k = triDiagMat(i, 0);
			double b_kp1 = triDiagMat(i + 1, 0);
			double a_k = triDiagMat(i, 1);
			double absoluteVal = abs(b_k * b_k * deltaMinus[i - 1] + (a_k - energies[j]) + b_kp1 * b_kp1 * deltaPlus[i + 1]);
			if (absoluteVal <= convergence) {
				convergence = absoluteVal; //finding minimum
				k = i;
			}
		}
		resultingFunctions[j][k] = 1;
		//std::cout << k << std::endl;
		//BUILDING FUNCTIONS
		for (int i = k - 1; i >= 0; i--) {
			double bip1 = triDiagMat(i + 1, 0);
			resultingFunctions[j][i] = -deltaMinus[i] * bip1 * resultingFunctions[j][i + 1];
		}
		for (int i = k + 1; i <= Np1; i++) {
			double bi = triDiagMat(i, 0);
			resultingFunctions[j][i] = -deltaPlus[i] * bi * resultingFunctions[j][i - 1];
		}
		resultingFunctions[j] = resultingFunctions[j] / sqrt((dot(resultingFunctions[j], resultingFunctions[j])));
		//resultingFunctions[j] = normalise(resultingFunctions[j],2);
		//deltaPlus = arma::vec(pointNum, arma::fill::zeros);
		//deltaMinus = arma::vec(pointNum, arma::fill::zeros);
	}
	for (int i = 0; i < pointNum; i++) {
		fileWave << a + i * step;
		for (int j = 0; j < eigenStatesNum; j++) {
			fileWave << "\t\t" << resultingFunctions[j][i] / (sqrt(step)); //don't know why
		}
		fileWave << endl;
	}
	fileWave.close();
	fileEn.close();


}


void martinDeanSchroedingerConstMass(std::vector<double> V, double* meff, int eigenStatesNum, std::vector<arma::vec> resultingFunctions, arma::vec energies, const double step, int pointNum, double a)
{
	//---------files---------------------------------
	std::ofstream fileEn, fileWave;
	fileEn.setf(3, std::ios::floatfield);
	fileWave.setf(3, std::ios::floatfield);
	fileEn.open("energies.dat", std::ios::out);
	fileWave.open("wavefunctions.dat", std::ios::out);
	if (!fileEn || !fileWave)
	{
		throw std::system_error(errno, std::system_category(), "failed to open ");
	}
	//-------------------------------------------------
	arma::mat triDiagMat(pointNum, 3, arma::fill::zeros);//for our matrix problem to calculate (just 2 colums cause we create symetric)
	//arma::mat triDiagMatFull(pointNum, pointNum, arma::fill::zeros);//testing if results are fine
	arma::vec deltaPlus(pointNum, arma::fill::zeros);
	arma::vec deltaMinus(pointNum, arma::fill::zeros);
	double Vmin, Vmax;
	int Vmin_index, Vmax_index;
	double epsilon = 1e-15; //for better precision in matrix

	//initialize vector with 0's
	for (int i = 0; i < eigenStatesNum; i++) {
		resultingFunctions.push_back(arma::vec(pointNum, arma::fill::zeros));
	}
	//1e3 don't get that but let's go

	//----------finding minima and maxima of potential for out interval [a,b] for bisection--------------------------------
	Vmin_index = std::min_element(V.begin(), V.end()) - V.begin();
	Vmax_index = std::max_element(V.begin(), V.end()) - V.begin(); //findig extremas
	Vmax = V[Vmax_index];
	Vmin = V[Vmin_index];
	Vmin = Vmin * step * step * G0; //normalizing ->non dim now
	Vmax = Vmax * step * step * G0;
	//------------------------------------------------------------------------------------------------------------------------
	//building matrix (vector form)------------------------------------------------------------------------------------------
	//we will hold just the bottom diagonal and use information that the spectrum of trid(bi,ai,ci) is equivalent to symetric tridiag matrix of trid(bi'=sqrt(bici),ai,bi') with our asumption for eff massses
	if (pointNum <= 2) throw"Damn, small number of points dawg";
	//#pragma omp parallel for 
	for (int i = 0; i < pointNum; i++)
	{
		double ai, bi, wi, wip1, wim1;
		ai = (2 / meff[i] + (V[i] * step * step * G0 ));
		if (i == 0) {
			bi = -1 / meff[i];
			triDiagMat(i, 0) = 0.0;
			triDiagMat(i, 1) = ai;
			triDiagMat(i, 2) = bi;
		}
		else if (i == pointNum - 1) {

			bi = -1 / meff[i];
			triDiagMat(i, 0) = bi;
			triDiagMat(i, 1) = ai;
			triDiagMat(i, 2) = 0.0;
		}
		else {
			bi = -1 / meff[i];
			triDiagMat(i, 0) = bi;
			triDiagMat(i, 1) = ai;
			triDiagMat(i, 2) = bi;
		}
	}
	// FULL MATRIX CREATION-----------------
	/*
	for (int i = 0; i < pointNum; i++)
	{
		double ai, bi;
		ai = (2 / meff[i] + (V[i] * step * step * G0 ));
		if (i == 0) {
			bi = -1;
			//triDiagMat(i, 0) = 0.0;
			triDiagMatFull(i, i) = ai;
			triDiagMatFull(i, i + 1) = bi;
		}
		else if (i == pointNum - 1) {
			bi = -1;
			triDiagMatFull(i, i-1) = bi;
			triDiagMatFull(i, i) = ai;
			//triDiagMatFull(i, i+1) = 0.0;
		}
		else {
			bi = -1;
			triDiagMatFull(i, i-1) = bi;
			triDiagMatFull(i, i) = ai;
			triDiagMatFull(i, i+1) = bi;
		}
	}
	*/
	//triDiagMatFull.print("triDiagFull");
	//triDiagMat.print("mat");
	
	//-------------------------------------calculating energies-----------------------------------------------
	energies = findEigValWithSturmTridiagSym(pointNum, epsilon, Vmin, Vmax, -1, -1, eigenStatesNum,false, 0, triDiagMat);
	//energies.print("val bisection = ");
	//arma::vec eigenvalues;
	//arma::mat eigvec;
	//arma::eig_sym(eigenvalues,eigvec, triDiagMatFull);
	//eigvec.col(0) = normalise(eigvec.col(0))*10;
	//eigvec.col(0).print("Eigvec");
	//eigenvalues.print("valFull =");
	//energies =  LanczosTridiag(pointNum, eigenStatesNum, triDiagMat);
	//energies.print("valLan =");
	//AFTER THAT WE SHALL HAVE THE f_pointNum polynomial with corresponding eigenvalues, remember that eigenvalues are that of tylde, that epsilon~ = epislon/step/step
	//-------------------------------------calculating eigenfunctions---------------------------------------------------------
	//==============calculating deltas========================;========
	for (int j = 0; j < eigenStatesNum; j++) {
		int Np1 = pointNum - 1;
		resultingFunctions[j][0] = 0;//boundary conditions
		resultingFunctions[j][Np1] = 0; //boundary conditions
		int N = Np1 - 1;
		fileEn << energies[j]/ (step * step * G0) << std::endl;//PRINTING TO FILE-----------------
		deltaPlus[Np1] = (1.0 / (triDiagMat(Np1, 1) - energies[j]));//Nth element -> for this we go like
		deltaMinus[0] = (1.0 / (triDiagMat(0, 1) - energies[j]));//first element
		//cout << deltaMinus[1] << std::endl;
		//calculating deltas------
		for (int i = 1; i <= Np1; i++) {//here we calculate all deltas
			int i2 = Np1 - i ;//Because for delta Plus we go from behind
			double ai = triDiagMat(i, 1);
			double aj = triDiagMat(i2, 1);
			double bi = triDiagMat(i, 0);
			double bjp1 = triDiagMat(i2 + 1, 0);
			deltaMinus[i] = 1.0 / (ai - energies[j] - (bi * bi * deltaMinus[i - 1]));

			deltaPlus[i2] = 1.0 / (aj - energies[j] - (bjp1 * bjp1 * deltaPlus[i2 + 1]));
			//cout << deltaPlus[i2] << "\t E = " << energies[j] << "aj = "<<aj << std::endl;
		}
		//deltaPlus[0] = 1.0 / (triDiagMat(0, 1)- energies[j] + triDiagMat(1,0) * triDiagMat(1, 0) * deltaPlus[1]);
		//deltaMinus[N] = 1.0 / (triDiagMat(N, 1) - energies[j] + triDiagMat(N, 0) * triDiagMat(N-1, 2) * deltaMinus[N-1]);
		//deltaMinus.print("d-");
		//deltaPlus.print("d+");
		//std::reverse(deltaPlus.begin(), deltaPlus.end());//we need to reverse it -----------> MUST CHECK
		int k;
		//finding minimum-----------
		double convergence = DBL_MAX;//for minumum calculation
		for (int i = 2; i < Np1-2; i++) {//here we define deltas and look for k which holds the minimum for |bk^2deltaminus_k-1 + (ak-E)+b_k+1^2deltaPlus_k+1|
			double b_k = triDiagMat(i, 0);
			double b_kp1 = triDiagMat(i + 1, 0);
			double a_k = triDiagMat(i, 1);
			double absoluteVal = abs( b_k * b_k * deltaMinus[i - 1] + (a_k - energies[j]) + b_kp1 * b_kp1 * deltaPlus[i + 1]);
			if (absoluteVal <= convergence) {
				convergence = absoluteVal; //finding minimum
				k = i;
			}
		}
		resultingFunctions[j][k] = 1;
		//std::cout << k << std::endl;
		//BUILDING FUNCTIONS
		for (int i = k-1 ; i >= 0; i--) {
			double bip1 = triDiagMat(i+1, 0);
			resultingFunctions[j][i] = -deltaMinus[i] * bip1 * resultingFunctions[j][i + 1];
		}
		for (int i = k+1 ; i <= Np1; i++) {
			double bi = triDiagMat(i, 0);			
			resultingFunctions[j][i] = -deltaPlus[i] * bi * resultingFunctions[j][i - 1];
		}
		resultingFunctions[j] = resultingFunctions[j]/ sqrt((dot(resultingFunctions[j],resultingFunctions[j])));
		//resultingFunctions[j] = normalise(resultingFunctions[j],2);
		//deltaPlus = arma::vec(pointNum, arma::fill::zeros);
		//deltaMinus = arma::vec(pointNum, arma::fill::zeros);
	}
	for (int i = 0; i < pointNum; i++) {
		fileWave << a + i * step;
		for (int j = 0; j < eigenStatesNum; j++) {
			fileWave << "\t\t" << resultingFunctions[j][i] / (sqrt(step)); //don't know why
		}
		fileWave << endl;
	}
	fileWave.close();
	fileEn.close();
}





//========================================================================
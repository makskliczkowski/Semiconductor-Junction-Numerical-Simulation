//Here we will define functions that shoudl be involved from main, they will be taking main arguments as parameters because they will be invoked from outside application. We will still need to compile
//the c++ app again, but now we will have all methods together and the change would be much easier for future. We can also compile different versions for different mains. 

#include "useInMainTests.h"
#include "Parameters.h"
#include "Numerical_methods.h"

//-------------------------------------------------------PARAMETERS APPLICATION------------------------------------------------
void ParametersApplicationRun(int argc, char** argv)
{
	//arguments:
	//1) T
	//2) x1
	//3) y1
	//4) x2
	//5) y2
	//6) x3
	//7) y3
	//8) bool include strain?
	//9) substrate
	double x1, y1, x2, y2, x3, y3, T;
	bool includeStrain;
	param substrate;

	if (argc == 10) {
		T = stod(argv[1], NULL);
		x1 = stod(argv[2], NULL);
		y1 = stod(argv[3], NULL);
		x2 = stod(argv[4], NULL);
		y2 = stod(argv[5], NULL);
		x3 = stod(argv[6], NULL);
		y3 = stod(argv[7], NULL);
		includeStrain = static_cast<bool>(stoi(argv[8], NULL));
		semiconductor which = AB_parser(argv[9]);
		substrate = substra(which);
		//-------------------ifs--------------------------------
		if (x1 > 1 || x1 < 0) throw "x must be in range [0,1]";
		if (y1 > 1 || y1 < 0) throw "y must be in range [0,1]";
		if (x2 > 1 || x2 < 0) throw "x must be in range [0,1]";
		if (y2 > 1 || y2 < 0) throw "y must be in range [0,1]";
		if (x3 > 1 || x3 < 0) throw "x must be in range [0,1]";
		if (y3 > 1 || y3 < 0) throw "y must be in range [0,1]";
		if (T < 0 || T > 400) throw "temperature ranges in [0,400]K";
	}
	else if (argc == 1) {
		T = 300;
		x1 = 0.9;
		y1 = 0.7;
		x2 = 0.65;
		y2 = 0.9;
		x3 = 0.1;
		y3 = 0.3;
		includeStrain = true;
		substrate = GaAs::GaAs;
	}
	else {
		throw "What's happening, hom much args?";
	}
	//--------------------calculations-----------------------------
	//Substrate
	AB SUBSTR(substrate, T);
	//--------AlGaAsSb-----------
	ABCD_x1mx_y1my AlGaAsSb = get_ABCD_2x2("Al", "Ga", "As", "Sb", x1, y1, T, trippleAlloyBowings::AlGaSb::bowAlGaSb, trippleAlloyBowings::AlGaAs::bowAlGaAs, trippleAlloyBowings::AlAsSb::bowAlAsSb, trippleAlloyBowings::GaAsSb::bowGaAsSb);
	//-------GaInPAs-------------
	ABCD_x1mx_y1my GaInPAs = get_ABCD_2x2("Ga", "In", "P", "As", x2, y2, T, trippleAlloyBowings::GaInAs::bowGaInAs, trippleAlloyBowings::GaInP::bowGaInP, trippleAlloyBowings::GaPAs::bowGaPAs, trippleAlloyBowings::InPAs::bowInPAs);
	//--------AlGaAsSb #2 -----------------------------------------------
	ABCD_x1mx_y1my AlGaAsSb2 = get_ABCD_2x2("Al", "Ga", "As", "Sb", x3, y3, T, trippleAlloyBowings::AlGaSb::bowAlGaSb, trippleAlloyBowings::AlGaAs::bowAlGaAs, trippleAlloyBowings::AlAsSb::bowAlAsSb, trippleAlloyBowings::GaAsSb::bowGaAsSb);
	//-------------------include temp and strain -------------------------
	SUBSTR.E_T();
	cout << SUBSTR.get_Ec() - SUBSTR.get_Ev_hh();
	AlGaAsSb.E_T();
	AlGaAsSb2.E_T();
	GaInPAs.E_T();
	if (includeStrain == true) {
		AlGaAsSb.includeStrain(SUBSTR.get_a_lat());
		GaInPAs.includeStrain(SUBSTR.get_a_lat());
		AlGaAsSb2.includeStrain(SUBSTR.get_a_lat());

	}
	SUBSTR.printToFile("substrate.dat");
	AlGaAsSb.printToFile("AlGaAsSb.dat");
	GaInPAs.printToFile("GaInPAs.dat");
	AlGaAsSb2.printToFile("AlGaAsSb2.dat");
	//--------------------interpolation-------------------------------------
	//in a function of x for given parameter y
	functionInterpolation(SUBSTR.get_a_lat(), "Al", "Ga", "As", "Sb", y1, T, trippleAlloyBowings::AlGaSb::bowAlGaSb, trippleAlloyBowings::AlGaAs::bowAlGaAs, trippleAlloyBowings::AlAsSb::bowAlAsSb, trippleAlloyBowings::GaAsSb::bowGaAsSb);
	functionInterpolation(SUBSTR.get_a_lat(), "Ga", "In", "P", "As", y2, T, trippleAlloyBowings::GaInAs::bowGaInAs, trippleAlloyBowings::GaInP::bowGaInP, trippleAlloyBowings::GaPAs::bowGaPAs, trippleAlloyBowings::InPAs::bowInPAs);
}

void NumericalSchroedingerRun(int argc, char** argv)
{
	//arguments:
	//1) PARABOLIC OR FOR MATERIALS
	/*if(MATERIALS)
	2) x1
	3) y1
	4) x2
	5) y2
	6) x3
	7) y3
	8) bool include strain
	9) substrate?
	10)eigenStatesNum
	11)stepInDiscretization
	12)DiscretizationPoints
	13) T
	14)Substratefinish
	15)FirstMaterial_finish_point
	16)SecondMaterial_finish_point
	17)width
	*/
	/*IF(PARABOLIC) ax^2+bx+c
	2) a
	3) b
	4) c
	5) meff
	6) stepInDiscretization
	7) DiscretizationPoints
	8) EigenstatesNum
	9) Starting point
	*/
	if (argc > 1) {
		/*PARABOLIC 1.0 0.0 0.0 1.0 0.01 600 3 -3.0 */
		string WhatToDo = argv[1];
		if (WhatToDo == "PARABOLIC") {
			double a, b, c, meff, step, xa;
			int pointNum, eigenNum;
			std::vector<arma::vec> functions;
			std::vector<double> energies;
			if (argc == 10) {
				a = stod(argv[2], NULL);
				b = stod(argv[3], NULL);
				c = stod(argv[4], NULL);
				meff = stod(argv[5], NULL);
				step = stod(argv[6], NULL);
				pointNum = stoi(argv[7], NULL);
				eigenNum = stoi(argv[8], NULL);
				xa = stod(argv[9], NULL);
			}
			else throw "Something is wrong ;c";
			std::vector<double> V; //potential
			double* mef = new double[pointNum];//effective mass 
			double x;
			for (int i = 0; i < pointNum; i++) { //writing them to table
				x = xa + step * i;//IN NONDIM CAUSE IT WAS ALREADY IN A
				V.push_back((a * x * x)/2 + (b * x) + c);
				mef[i] = meff;
			}
			martinDeanSchroedingerConstMass(V, mef, eigenNum, functions, energies, step, pointNum, xa);
		}
		else if (WhatToDo == "MATERIALS") {
			double x1, y1, x2, y2, x3, y3, T,  step , firstFinish, secondFinish;
			int pointNum, eigenNum;
			bool includeStrain;
			double width, substratewidth;
			param substrate;
			if (argc == 18) {
				x1 = stod(argv[2], NULL);
				y1 = stod(argv[3], NULL);
				x2 = stod(argv[4], NULL);
				y2 = stod(argv[5], NULL);
				x3 = stod(argv[6], NULL);
				y3 = stod(argv[7], NULL);
				includeStrain = static_cast<bool>(stoi(argv[8], NULL));
				semiconductor which = AB_parser(argv[9]); substrate = substra(which);
				eigenNum = stoi(argv[10], NULL);
				step = stod(argv[11], NULL);
				pointNum = stoi(argv[12], NULL);
				T = stod(argv[13], NULL);
				substratewidth = stod(argv[14], NULL);
				firstFinish = stod(argv[15], NULL);
				secondFinish = stod(argv[16], NULL);
				width = stod(argv[17], NULL);
				//-------------------ifs--------------------------------
				if (x1 > 1 || x1 < 0) throw "x must be in range [0,1]";
				if (y1 > 1 || y1 < 0) throw "y must be in range [0,1]";
				if (x2 > 1 || x2 < 0) throw "x must be in range [0,1]";
				if (y2 > 1 || y2 < 0) throw "y must be in range [0,1]";
				if (x3 > 1 || x3 < 0) throw "x must be in range [0,1]";
				if (y3 > 1 || y3 < 0) throw "y must be in range [0,1]";
				if (T < 0 || T > 400) throw "temperature ranges in [0,400]K";
			}
			//--------------------calculations for material parameters---------------------------------------------------------------------------------------------------------------------------------------------------
			//Substrate
			AB SUBSTR(substrate, T);
			//--------AlGaAsSb-----------
			ABCD_x1mx_y1my AlGaAsSb = get_ABCD_2x2("Al", "Ga", "As", "Sb", x1, y1, T, trippleAlloyBowings::AlGaSb::bowAlGaSb, trippleAlloyBowings::AlGaAs::bowAlGaAs, trippleAlloyBowings::AlAsSb::bowAlAsSb, trippleAlloyBowings::GaAsSb::bowGaAsSb);
			//-------GaInPAs-------------
			ABCD_x1mx_y1my GaInPAs = get_ABCD_2x2("Ga", "In", "P", "As", x2, y2, T, trippleAlloyBowings::GaInAs::bowGaInAs, trippleAlloyBowings::GaInP::bowGaInP, trippleAlloyBowings::GaPAs::bowGaPAs, trippleAlloyBowings::InPAs::bowInPAs);
			//--------AlGaAsSb #2 -----------------------------------------------
			ABCD_x1mx_y1my AlGaAsSb2 = get_ABCD_2x2("Al", "Ga", "As", "Sb", x3, y3, T, trippleAlloyBowings::AlGaSb::bowAlGaSb, trippleAlloyBowings::AlGaAs::bowAlGaAs, trippleAlloyBowings::AlAsSb::bowAlAsSb, trippleAlloyBowings::GaAsSb::bowGaAsSb);
			//-------------------include temp and strain -------------------------
			SUBSTR.E_T();
			cout << SUBSTR.get_Ec() - SUBSTR.get_Ev_hh();
			AlGaAsSb.E_T();
			AlGaAsSb2.E_T();
			GaInPAs.E_T();
			if (includeStrain == true) {
				AlGaAsSb.includeStrain(SUBSTR.get_a_lat());
				GaInPAs.includeStrain(SUBSTR.get_a_lat());
				AlGaAsSb2.includeStrain(SUBSTR.get_a_lat());

			}
			SUBSTR.printToFile("substrate.dat");
			AlGaAsSb.printToFile("AlGaAsSb.dat");
			GaInPAs.printToFile("GaInPAs.dat");
			AlGaAsSb2.printToFile("AlGaAsSb2.dat");
			//--------------------interpolation-------------------------------------
			//in a function of x for given parameter y
			functionInterpolation(SUBSTR.get_a_lat(), "Al", "Ga", "As", "Sb", y1, T, trippleAlloyBowings::AlGaSb::bowAlGaSb, trippleAlloyBowings::AlGaAs::bowAlGaAs, trippleAlloyBowings::AlAsSb::bowAlAsSb, trippleAlloyBowings::GaAsSb::bowGaAsSb);
			functionInterpolation(SUBSTR.get_a_lat(), "Ga", "In", "P", "As", y2, T, trippleAlloyBowings::GaInAs::bowGaInAs, trippleAlloyBowings::GaInP::bowGaInP, trippleAlloyBowings::GaPAs::bowGaPAs, trippleAlloyBowings::InPAs::bowInPAs);
			//----------------------------------------------------------------SCHROEDINGER FOR THOSE-------------------------------------------------------------------------------------------------------------------------
			double point = 0.0;
			std::vector<arma::vec> functionsCond,functionsVal;
			arma::vec energiesCond,energiesVal;
			std::vector<double> Valence;
			std::vector<double> Conduction;
			double* mefC = new double[pointNum];
			double* mefV = new double[pointNum];
			int i = 0;
			double nowWidth = substratewidth;
			while (point < nowWidth) { //first substrate
				Valence.push_back(SUBSTR.get_Ev_hh());
				Conduction.push_back(SUBSTR.get_Ec());
				mefC[i] = SUBSTR.get_which().EFF_MASS;
				mefV[i] = -SUBSTR.get_which().EFF_MASS;;
				point = i * step;
				i++;
			}
			nowWidth += firstFinish;
			while (point < nowWidth) {//first material
				Valence.push_back(AlGaAsSb.get_Ev_hh());
				Conduction.push_back(AlGaAsSb.get_Ec());
				mefC[i] = AlGaAsSb.get_m_eff();
				mefV[i] = -AlGaAsSb.get_m_eff();
				point = i * step;
				i++;
			}
			nowWidth += secondFinish;
			while (point < nowWidth) {//second material
				Valence.push_back(GaInPAs.get_Ev_hh());
				Conduction.push_back(GaInPAs.get_Ec());
				mefC[i] = GaInPAs.get_m_eff();
				mefV[i] =-GaInPAs.get_m_eff();
				point = i * step;
				i++;
			}
			nowWidth = width - substratewidth;
			while (point < nowWidth) {//third material
				Valence.push_back(AlGaAsSb2.get_Ev_hh());
				Conduction.push_back(AlGaAsSb2.get_Ec());
				mefC[i] = AlGaAsSb2.get_m_eff();
				mefV[i] = -AlGaAsSb2.get_m_eff();
				point = i * step;
				i++;
			}
			while (point < width) { //first substrate
				Valence.push_back(SUBSTR.get_Ev_hh());
				Conduction.push_back(SUBSTR.get_Ec());
				mefC[i] = SUBSTR.get_which().EFF_MASS;
				mefV[i] = -SUBSTR.get_which().EFF_MASS;
				point = i * step;
				i++;
			}

			martinDeanSchroedingerChangingMass(Valence, mefV, eigenNum,true, functionsVal, energiesVal, step, pointNum,0);//SCHROEDINGER FROM MARTIN,DEAN
			martinDeanSchroedingerChangingMass(Conduction, mefC, eigenNum,false, functionsCond, energiesCond, step, pointNum, 0);//SCHROEDINGER FROM MARTIN,DEAN
			//overlapping---------------------------------------------------------------------------
			std::ofstream fileOv;
			fileOv.setf(3, std::ios::floatfield);
			fileOv.open("overlapping.dat", std::ios::out);
			arma::vec overlapping(pointNum);
			double integral = 0;
			for (int i = 0; i < pointNum; i++) {
				overlapping[i] = functionsCond[0][i] * functionsVal[0][i];
			}
			//overlapping.print("overlapp");
			integral = simpsonInt(0, width, step, overlapping);
			fileOv << abs(integral);
			cout << endl<< integral << endl;
			fileOv.close();
		}
	}
	else{//else we will make parabolic potential 
		std::vector<arma::vec> functions;
		arma::vec energies;
		double meff, step;
		int pointNum, eigenNum;
		//a = 3.4e12;
		double bcoeff = 0;
		double ccoeff = 0;
		//assuming kx^2
		double k = 1; //in eV/mn^2
		meff = 2;//divided by m_0
		step = 0.01;//in Angstroms
		double a = -3.5; // in angstroms
		double b = 3.5;
		pointNum = static_cast<int>(abs((b-a)/step));
		cout << pointNum << endl;
		eigenNum = 4;
		std::vector<double> V;
		double* mef = new double[pointNum];
		double x;
		for (int i = 0; i < pointNum; i++) {
			x = a + step*i;//IN NONDIM CAUSE IT WAS ALREADY IN A
			V.push_back((k*x*x/2 + bcoeff*x + ccoeff));// SEND IN NON_DIM CAUSE IT WAS ALREADY IN eV
			mef[i] = meff;//m*/me
		}
		martinDeanSchroedingerConstMass(V, mef, eigenNum, functions, energies, step, pointNum,a);//SCHROEDINGER FROM MARTIN,DEAN
	}
}

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

using namespace std;
#define concat(first, second) first second
//-----------------------------------CONSTANT PARAMETERS------------------------------------------------------
//-----------------parsers-------------------------------------------------
enum semiconductor {
	sAlSb = 1,
	sGaSb,
	sGaAs,
	sInAs,
	sAlAs,
	sGaP,
	sInP,
	nothing = 0
	//we have to add s at the begining because of the namespace
	//when adding new remember to include it in semiconParser
};
semiconductor AB_parser(const char* semic);
//------------------bowings------------------------------------------------
namespace trippleAlloyBowings {
	struct bowing {
		double (*Eg)(double);
		double SPIN_ORB;
		double EFF_MASS;
		double VBO;
		double a_c;

		double alpha =0.0;
		double beta = 0.0;
		double a_v = 0.0;
		double b = 0.0;
		double C11 = 0.0; 
		double C12 = 0.0;
		double a_lat = 0.0;
	};
	namespace AlGaAs {
		inline double Eg(double x) {
			return -0.127 + 1.310 * x;
		};
		constexpr bowing bowAlGaAs{
			&Eg,
			0.0,
			0.0,
			0.0,
			0.0,

			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};
	};
	namespace GaInAs {
		inline double Eg(double x) {
			return 0.477;
		};
		constexpr bowing bowGaInAs{
			&Eg,
			0.15,
			0.0091,
			-0.38,
			2.61,//ac

			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};
	};
	namespace GaInP {
		inline double Eg(double x) {
			return 0.65;
		};
		constexpr bowing bowGaInP{
			&Eg,
			0.0,
			0.051,
			0.0,
			0.0,

			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};
	};
	namespace AlGaSb {
		inline double Eg(double x) {
			return -0.044 + 1.22 * x;
		};
		constexpr bowing bowAlGaSb{
			&Eg,
			0.3,
			0.0,
			0.0,
			0.0,

			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};
	};
	namespace GaAsSb {
		inline double Eg(double x) {
			return 1.43;
		};
		constexpr bowing bowGaAsSb{
			&Eg,
			0.6,
			0.0,
			-1.06,
			0.0,

			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};
	};
	namespace AlAsSb{
		inline double Eg(double x) {
			return 0.8;
		};
		constexpr bowing bowAlAsSb{
			&Eg,
			0.15,
			0.0,
			-1.71,
			0.0,

			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};
	};
	namespace GaPAs {
		inline double Eg(double x) {
			return 0.19;
		};
		constexpr bowing bowGaPAs{
			&Eg,
			0.0,
			0.0,
			-0.0,
			0.0,

			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};
	};
	namespace InPAs {
		inline double Eg(double x) {
			return 0.10;
		};
		constexpr bowing bowInPAs{
			&Eg,
			0.16,
			0.0,
			0.0,
			0.0,

			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};
	};
};
//--------------double compounds------------------------------
struct param {
	double SPIN_ORB;
	double EFF_MASS;//m_e
	double EG;//eV
	double VBO;//eV

	double alpha;//eV/K
	double beta; //K

	double a_c;//eV
	double a_v;//eV
	double b;//eV - deformation potential
	double C11; // GPa - wspolczynniki sprezyst w kierunku wzrostu
	double C12; // GPa - wspolczynniki sprezyst w kierunku wzrostu
	double (*a_lat)(double);
};
param substra(semiconductor parser);
//AlSb
namespace AlSb {
	inline double a_lat(double T) {
		return 6.1355 + 2.60 * 1e-5 * (T - 300);
	};
	constexpr param AlSb{
		0.676,								//SO
		0.14,								//EFF MASS
		2.386,								//EG
		-0.41,								//VBO
											
		0.42 * 1e-3, 						//alpha
		140.0, 								//beta

		-4.5, 								//ac
		-1.47, 								//av
		-1.35,								//b
		876.9,								//c11
		434.1,								//c12
		&a_lat								//a lattice
	};
}
//GaSb
namespace GaSb {
	inline double a_lat(double T) {
		return 6.0959 + 4.72 * 1e-5 * (T - 300);
	}//A
	constexpr param  GaSb{
	 0.76,								   //SO
	 0.039,//m_e						   //EFF MASS
	 0.812,//eV							   //EG
	 -0.03,//eV							   //VBO

	 0.417 * 1e-3,						   //alpha
	 140.0, //K							   //beta

	 -7.5, //eV							   //ac
	 -0.8,								   //av
	 -2.0,								   //b
	 884.2, 							   //c11
	 402.6, // GPa						   //c12
	 & a_lat							   //a lattice
	};
}
//GaAs
namespace GaAs {
	inline double a_lat(double T) {
		return 5.65325 + 3.88 * 1e-5 * (T - 300);
	}//A
	constexpr param  GaAs{
		0.341,								//SPIN ORBIT
		0.067,//m_e						    //EFF MASS
		1.519,//eV						    //EG
		-0.80,//eV						    //VBO

		0.5405 * 1e-3,					    //alpha
		204.0, //K						    //beta

		-9.3, //eV						    //ac
		-0.7, //eV -					    //av
		-2.0,//eV - de					    //b
		1221.0, // GPa					    //c11
		566.0, // GPa					    //c12
		& a_lat							    //a lattice
	};
}
//AlAs
namespace AlAs {
	inline double a_lat(double T) {
		return 5.6611 + 2.9 * 1e-5 * (T - 300);
	}//A
	constexpr param AlAs{
		0.28,								 //SPINORBIT
		0.15,//m_e							 //EFF MASS
		3.099,//eV							 //EG
		-1.33,//eV							 //VBO

		0.885 * 1e-3, 						 //alpha
		530.0, //K							 //beta

		-5.64, //eV							 //ac
		2.47, //eV -						 //av
		-2.3,//eV - de						 //b
		1250.0, // GPa						 //c11
		534.0, // GPa						 //c12
		&a_lat								 //a lattice
	};
}
//InAs
namespace InAs {
	inline double a_lat(double T) {
		return 6.0583 + 2.74 * 1e-5 * (T - 300);
	}//A
	constexpr param  InAs{
		0.39,								  //SO
		0.024,//m_e							  //EFF MASS
		0.417,//eV							  //EG
		-0.59,//eV							  //VBO

		0.276 * 1e-3,						  //alpha
		93.0, //K							  //beta

		-5.08, //eV							  //ac
		1.00, //eV 							  //av
		-1.8,//eV - 						  //b
		832.9, // GP						  //c11
		452.6, // GP						  //c12
		& a_lat								  //a lattice
	};
}
//GaP
namespace GaP {
	inline double a_lat(double T) {
		return 5.4505 + 2.92 * 1e-5 * (T - 300);
	}//A
	inline double energyT(double T) {
		if (T != 0) return 2.886 + 0.1091 * (1 - cosh(164 / T) / sinh(164 / T));
		else return 2.886;
	}
	constexpr param  GaP{
		0.08,								  //SO
		0.114,//							  //EFF MASS
		2.886, 								  //EG
		-1.27,								  //VBO
											 
		0.5771e-3,						      //alpha
		372, //K							  //beta
											 
		-8.2, 								  //ac
		1.7, 								  //av
		-1.6,//								  //b
		1405.0,								  //c11
		620.3, 								  //c12
		&a_lat								  //a lattice
	};
}
//InP
namespace InP {
	inline double a_lat(double T) {
		return 5.8697 + 2.79 * 1e-5 * (T - 300);
	}//A
	constexpr param  InP{
		0.108,		                          //SO
		0.07927,//m_e						  //EFF MASS
		1.4236,//eV							  //EG
		-0.94,//eV							  //VBO
											  //
		0.363 * 1e-3,						  //alpha
		162.0, //K							  //beta
											  //
		-6.0, //eV							  //ac
		-0.6, //eV 							  //av
		-2.0,//eV - 						  //b
		1011.0, // 							  //c11
		561.0, // G							  //c12
		&a_lat								  //a lattice
	};
}
//-------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------simplest form---------------------------------------------------
class AB {
private:
	param which;
protected:
	double a_lat;
	double Ev_hh, Ev_lh, Ev_so, Ec;
	double T;
public:
	AB();
	AB(param a,double T);
	void E_T();//temp dependence of energy included at the end
	virtual void printToFile(const char* filename);
	virtual void printToFile(ofstream& file);
	//-----------getters--------------
	double get_a_lat();
	double get_Ev_hh();
	double get_Ev_lh();
	double get_Ev_so();
	double get_Ec();
	param get_which();
};
//lattice constant is changed automatically with temperature, when one wants to change energy with temp only for this substrate simply take E_T();
//--------------------------------------three part form III III V || III V V------------------------------------------

class A_xB_1mxC:public AB {
	//when A_xB_1mxC ---> first - AC | second - BC
	//when AB_xC_1mx ---> first - AB | second - AC
private:
	AB firstAB, secondAB;//compounds
	trippleAlloyBowings::bowing bowing;//ale the bowings are inside
	double paramABC_x1mx(double firstParam, double secondParam, double x, double bowing = 0.0);
protected:
	double x;
	double so,m_eff, Eg, VBO, alpha, beta, ac, av, b, c11, c12; //parameters
public:
	
	A_xB_1mxC();
	A_xB_1mxC(double T,double x, AB fst, AB snd, trippleAlloyBowings::bowing bowing);
	void includeStrain(double a_substrate);//naprezenia
	void E_T();//temp dependence of energy included at the end
	void printToFile(const char* filename);
	void printToFile(ofstream& file);
	//----------------getters------------------
	double get_so();
	double get_m_eff();
	double get_Eg();
	double get_alpha();
	double get_beta();
	double get_ac();
	double get_av();
	double get_b();
	double get_c11();
	double get_c12();
	double get_VBO();
};
A_xB_1mxC get_ABC_2xIII(const char* A, const char* B, const char* C,double x, double T, trippleAlloyBowings::bowing bowing);
A_xB_1mxC get_ABC_2xV(const char* A, const char* B, const char* C, double x, double T, trippleAlloyBowings::bowing bowing);
//when one wants to change energy with temp only for this substrate simply take E_T(), to include strain take includeStrain(a substrate)
//------------------------------------------four part form III III V V------------------------------------------------
class ABCD_x1mx_y1my:public A_xB_1mxC {
//AxB_1-xCyD_1-y
//first = AxB_1-xD
//second = AxB_1-xC
//third ACyD_1-y
//fourth BCyD_1-y
private:
	double y;
	A_xB_1mxC first,second,third,fourth; //compounds
public:
	ABCD_x1mx_y1my();
	void printToFile(const char* filename);
	void printToFile(ofstream& file);
	ABCD_x1mx_y1my(double T, double x, double y, A_xB_1mxC fst, A_xB_1mxC snd, A_xB_1mxC trd, A_xB_1mxC frth);
	double paramABCD_x1mx_y1my(double first, double second, double third, double fourth, double x, double y);
};
ABCD_x1mx_y1my get_ABCD_2x2(const char* A, const char* B, const char* C, const char* D, double x, double y, double T, trippleAlloyBowings::bowing bABD, trippleAlloyBowings::bowing bABC, trippleAlloyBowings::bowing bACD, trippleAlloyBowings::bowing bBCD);
//get temperature and strain same way at the end;

//----------------------------------------------------------------------------------------------------------
void functionInterpolation(double a_sub, const char* A, const char* B, const char* C, const char* D, double y, double T, trippleAlloyBowings::bowing bABD, trippleAlloyBowings::bowing bABC, trippleAlloyBowings::bowing bACD, trippleAlloyBowings::bowing bBCD);
//---------------------------------------------------------------------------------------------------------------------------
/*
void printerIntegrals(long double xi, long double xf, long double step, const char* filename, long double* functionAn, long double* functionNum);
long double * setCoeffFinite(int rank);
long double * setCoeffFinite(int rank, int points);
long double * tableFunFinite(long double(*function)(long double), long double step, long double x_i, long double x_f, int gFinite);
// finite difference method coefficients
long double differentiateFinite(int rank, long double step, long double * function, int pointNum, long double* coeff);
long double simpsonInt(double a, double b, double step, long double * function);
*/










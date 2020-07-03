
#include "Parameters.h"
//Here we define parameter interpolation functions for semiconductor alloys----------------------------------------------------------


#define putABC(what) this->paramABC_x1mx(fst.get_which().what##, snd.get_which().what##, x, this->bowing.what##)
#define putABCD(what) this->paramABCD_x1mx_y1my(fst.get_##what##(), snd.get_##what##(), trd.get_##what##(), frth.get_##what##(), x, y)
//----------------------------------ABC-----------------------------------------------------------------

A_xB_1mxC::A_xB_1mxC()
{
	this->T = 0;
	this->bowing = trippleAlloyBowings::GaAsSb::bowGaAsSb;
	this->x = 1;
	this->firstAB = AB();
	this->secondAB = AB();
	AB fst = this->firstAB;
	AB snd = this->secondAB;
	this->so = putABC(SPIN_ORB);
	this->m_eff = putABC(EFF_MASS);
	this->Eg = this->paramABC_x1mx(fst.get_which().EG, snd.get_which().EG, x, this->bowing.Eg(this->x));//bowing only for EG cause it's afunction
	this->VBO = putABC(VBO);
	this->alpha = putABC(alpha);
	this->beta = putABC(beta);
	this->ac = putABC(a_c);
	this->av = putABC(a_v);
	this->b = putABC(b);
	this->c11 = putABC(C11);
	this->c12 = putABC(C12);
	this->a_lat = this->paramABC_x1mx(fst.get_a_lat(), snd.get_a_lat(), x, this->bowing.a_lat);

	this->Ev_hh = this->VBO;
	this->Ev_lh = this->VBO;
	this->Ec = this->Ev_hh + this->Eg;
	this->Ev_so = this->VBO - this->so;
	
}

A_xB_1mxC::A_xB_1mxC(double T, double x, AB fst, AB snd,trippleAlloyBowings::bowing bowing)
{
	this->T = T;
	this->bowing = bowing;
	this->x = x;
	this->firstAB = fst;
	this->secondAB = snd;
	this->so = putABC(SPIN_ORB);
	this->m_eff = putABC(EFF_MASS);
	this->Eg = this->paramABC_x1mx(fst.get_which().EG, snd.get_which().EG, x, this->bowing.Eg(this->x));//bowing only for EG cause it's afunction
	this->VBO = putABC(VBO);
	this->alpha = putABC(alpha);
	this->beta = putABC(beta);
	this->ac = putABC(a_c);
	this->av = putABC(a_v);
	this->b = putABC(b);
	this->c11 = putABC(C11);
	this->c12 = putABC(C12);
	this->a_lat = this->paramABC_x1mx(fst.get_a_lat(), snd.get_a_lat(), x, this->bowing.a_lat);

	this->Ev_hh = this->VBO;
	this->Ev_lh = this->VBO;
	this->Ec = this->Ev_hh + this->Eg;
	this->Ev_so = this->VBO - this->so;
}

double A_xB_1mxC::paramABC_x1mx(double firstParam, double secondParam, double x, double bowing)
{
	return ((x * firstParam) + ((1 - x) * secondParam) + (x * (1 - x) * bowing));
}

void A_xB_1mxC::includeStrain(double a_substrate)
{
	double e_xx = (a_substrate - this->a_lat) / this->a_lat;
	double e_yy = e_xx;
	double e_perp = -2 * (this->c12 / this->c11) * e_xx;
	double dEc_hyd = this->ac * (e_perp + 2 * e_xx);
	double dEv_hyd = this->av * (e_perp + 2 * e_xx);
	double dEv_biax = (e_perp - e_xx) * this->b;
	double dEv_biax_p = 0.5 * (dEv_biax - this->so + sqrt(9 * dEv_biax * dEv_biax + 2 * dEv_biax * this->so + this->so * this->so));
	double dEv_biax_m = 0.5 * (dEv_biax - this->so - sqrt(9 * dEv_biax * dEv_biax + 2 * dEv_biax * this->so + this->so * this->so));

	this->Ec = this->Ec + dEc_hyd;
	this->Ev_hh = this->Ev_hh + dEv_hyd - dEv_biax;
	this->Ev_lh = this->Ev_lh + dEv_hyd + dEv_biax_p;
	this->Ev_so = this->Ev_hh + dEv_hyd + dEv_biax_m;
	this->Eg = this->Ec - ((Ev_lh > Ev_hh) ? Ev_lh : Ev_hh);
}

void A_xB_1mxC::E_T()
{
	this->Eg = this->Eg - this->alpha * T * T / (T + this->beta);
	this->Ec = this->Ev_hh + this->Eg;
}

void A_xB_1mxC::printToFile(const char* filename)
{
	ofstream file;
	file.setf(3, std::ios::floatfield);
	file.open(filename, ios::out);
	if (!file)
	{
		throw std::system_error(errno, std::system_category(), "failed to open " + string(filename));
	}
	file << std::fixed << std::setprecision(3) << "x" << "\t \t";
	file << std::fixed << std::setprecision(3) << "m_eff" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_hh" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_lh" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_so" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ec" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Eg" << std::endl;

	file << std::fixed << std::setprecision(3) << x << "\t \t";
	file << std::fixed << std::setprecision(3) << m_eff << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_hh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_lh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_so << "\t \t";
	file << std::fixed << std::setprecision(3) << Ec << "\t \t";
	file << std::fixed << std::setprecision(3) << Eg << "\t \t";
	file.close();
}

void A_xB_1mxC::printToFile(ofstream& file) {
	file << std::fixed << std::setprecision(3) << x << "\t \t";
	file << std::fixed << std::setprecision(3) << m_eff << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_hh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_lh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_so << "\t \t";
	file << std::fixed << std::setprecision(3) << Ec << "\t \t";
	file << std::fixed << std::setprecision(3) << Eg << "\t \t" << std::endl;
}

double A_xB_1mxC::get_so()
{
	return this->so;
}

double A_xB_1mxC::get_m_eff()
{
	return this->m_eff;
}

double A_xB_1mxC::get_Eg()
{
	return this->Eg;
}

double A_xB_1mxC::get_alpha()
{
	return this->alpha;
}

double A_xB_1mxC::get_beta()
{
	return this->beta;
}

double A_xB_1mxC::get_ac()
{
	return this->ac;
}

double A_xB_1mxC::get_av()
{
	return this->av;
}

double A_xB_1mxC::get_b()
{
	return this->b;
}

double A_xB_1mxC::get_c11()
{
	return this->c11;
}

double A_xB_1mxC::get_c12()
{
	return this->c12;
}

double A_xB_1mxC::get_VBO()
{
	return this->VBO;
}

//----------------------------------ABCD---------------------------------------------------------------------------------------------

ABCD_x1mx_y1my::ABCD_x1mx_y1my()
{
	this->T = 0;
	this->x = 1;
	this->y = 1;
	this->first = A_xB_1mxC();
	this->second = A_xB_1mxC();
	this->third = A_xB_1mxC();
	this->fourth = A_xB_1mxC();
	this->m_eff = 1;
	this->Eg = 1;
	this->VBO = 1;
	this->alpha = 1;
	this->beta = 1;
	this->ac = 1;
	this->av = 1;
	this->b = 1;
	this->c11 = 1;
	this->c12 = 1;
	this->a_lat = 1;
	this->so = 1;

	this->Ev_hh = this->VBO;
	this->Ev_lh = this->VBO;
	this->Ec = this->Ev_hh + this->Eg;
	this->Ev_so = this->VBO - this->so;
}

void ABCD_x1mx_y1my::printToFile(const char* filename)
{
	ofstream file;
	file.setf(3, std::ios::floatfield);
	file.open(filename, ios::out);
	if (!file)
	{
		throw std::system_error(errno, std::system_category(), "failed to open " + string(filename));
	}
	file << std::fixed << std::setprecision(3) << "x" << "\t \t";
	file << std::fixed << std::setprecision(3) << "y" << "\t \t";
	file << std::fixed << std::setprecision(3) << "m_eff" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_hh" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_lh" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_so" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ec" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Eg" << std::endl;

	file << std::fixed << std::setprecision(3) << x << "\t \t";
	file << std::fixed << std::setprecision(3) << y << "\t \t";
	file << std::fixed << std::setprecision(3) << m_eff << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_hh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_lh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_so << "\t \t";
	file << std::fixed << std::setprecision(3) << Ec << "\t \t";
	file << std::fixed << std::setprecision(3) << Eg << "\t \t";

	file.close();
}

void ABCD_x1mx_y1my::printToFile(ofstream& file) {

	file << std::fixed << std::setprecision(3) << x << "\t \t";
	file << std::fixed << std::setprecision(3) << y << "\t \t";
	file << std::fixed << std::setprecision(3) << m_eff << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_hh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_lh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_so << "\t \t";
	file << std::fixed << std::setprecision(3) << Ec << "\t \t";
	file << std::fixed << std::setprecision(3) << Eg << "\t \t" << std::endl;
}

ABCD_x1mx_y1my::ABCD_x1mx_y1my(double T, double x, double y, A_xB_1mxC fst, A_xB_1mxC snd, A_xB_1mxC trd, A_xB_1mxC frth)
{
	this->T = T;
	this->x = x;
	this->y = y;
	this->first = fst;
	this->second = snd;
	this->third = trd;
	this->fourth = frth;
	this->so = putABCD(so);
	this->m_eff = putABCD(m_eff);
	this->Eg = putABCD(Eg);
	this->VBO = putABCD(VBO);
	this->alpha = putABCD(alpha);
	this->beta = putABCD(beta);
	this->ac = putABCD(ac);
	this->av = putABCD(av);
	this->b = putABCD(b);
	this->c11 = putABCD(c11);
	this->c12 = putABCD(c12);
	this->a_lat = putABCD(a_lat);

	this->Ev_hh = this->VBO;
	this->Ev_lh = this->VBO;
	this->Ec = this->Ev_hh + this->Eg;
	this->Ev_so = this->VBO - this->so;
}

double ABCD_x1mx_y1my::paramABCD_x1mx_y1my(double first, double second, double third, double fourth, double x, double y)
{
	//AxB_1-xCyD_1-y
	//first = AxB_1-xD
	//second = AxB_1-xC
	//third ACyD_1-y
	//fourth BCyD_1-y
	double result = 0.0;
	if (x == 1.0) {
		result = third;
	}
	else if (x == 0) {
		result = fourth;
	}
	else {
		if (y == 1.0) {
			result = second;
		}
		else if (y == 0) {
			result = first;
		}
		else {
			result = result = ((x * (1 - x) * ((1 - y) * first + y * second)) / (x * (1 - x) + y * (1 - y))) + ((y * (1 - y) * (x * third + (1 - x) * fourth)) / (x * (1 - x) + y * (1 - y)));;
		}
	}
	return result;
}


//-----------------------------------AB---------------------------------------------------------------------------
double AB::get_a_lat()
{
	return a_lat;
}

double AB::get_Ev_hh()
{
	return this->Ev_hh;
}

double AB::get_Ev_lh()
{
	return this->Ev_lh;
}

double AB::get_Ev_so()
{
	return this->Ev_so;
}

double AB::get_Ec()
{
	return this->Ec;
}

param AB::get_which()
{
	return this->which;
}

AB::AB()
{
	this->T = 0;
	this->which = GaAs::GaAs;
	this->a_lat = GaAs::a_lat(0);
	this->Ev_hh = which.VBO;
	this->Ev_lh = which.VBO;
	this->Ec = this->Ev_hh + which.EG;
	this->Ev_so = which.VBO - which.SPIN_ORB;
}

AB::AB(param a, double T)
{
	this->T = T;
	this->which = a;
	this->a_lat = a.a_lat(T);
	this->Ev_hh = which.VBO;
	this->Ev_lh = which.VBO;
	this->Ec = this->Ev_hh + which.EG;
	this->Ev_so = which.VBO - which.SPIN_ORB;
}

void AB::E_T()
{
	which.EG = which.EG - which.alpha * T * T / (T + which.beta);
	this->Ec = this->Ev_hh + which.EG;
}

void AB::printToFile(const char* filename)
{
	ofstream file;
	file.setf(3, std::ios::floatfield);
	file.open(filename, ios::out);
	if (!file)
	{
		throw std::system_error(errno, std::system_category(), "failed to open " + string(filename));
	}
	file << std::fixed << std::setprecision(3) << "m_eff" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_hh" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_lh" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_so" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ec" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Eg" << std::endl;

	file << std::fixed << std::setprecision(3) << this->which.EFF_MASS << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_hh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_lh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_so << "\t \t";
	file << std::fixed << std::setprecision(3) << Ec << "\t \t";
	file << std::fixed << std::setprecision(3) << Ec-Ev_hh << "\t \t";
	file.close();
}

void AB::printToFile(ofstream& file)
{

	file << std::fixed << std::setprecision(3) << this->which.EFF_MASS << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_hh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_lh << "\t \t";
	file << std::fixed << std::setprecision(3) << Ev_so << "\t \t";
	file << std::fixed << std::setprecision(3) << Ec << "\t \t";
	file << std::fixed << std::setprecision(3) << Ec - Ev_hh << "\t \t" << std::endl;
}
//-----------------------Parser to choose AB parameters from dictionary as the input is text-------------------------------
semiconductor AB_parser(const char* semic)
{
	const char* temp = semic;
	if (!strcmp(temp, "GaAs")) return semiconductor(sGaAs);
	if (!strcmp(temp, "AlSb")) return semiconductor(sAlSb);
	if (!strcmp(temp, "GaSb")) return semiconductor(sGaSb);
	if (!strcmp(temp, "InAs")) return semiconductor(sInAs);
	if (!strcmp(temp, "AlAs")) return semiconductor(sAlAs);
	if (!strcmp(temp, "GaP")) return semiconductor(sGaP);
	if (!strcmp(temp, "InP")) return semiconductor(sInP);
	else return semiconductor(nothing);
}

param substra(semiconductor parser)
{
	switch (parser)
	{
	case sAlSb:
		return AlSb::AlSb;
		break;
	case sGaSb:
		return GaSb::GaSb;
		break;
	case sGaAs:
		return GaAs::GaAs;
		break;
	case sInAs:
		return InAs::InAs;
		break;
	case sAlAs:
		return AlAs::AlAs;
		break;
	case sGaP:
		return GaP::GaP;
		break;
	case sInP:
		return InP::InP;
		break;
	case nothing:
		return GaAs::GaAs;
		break;
	default:
		return GaAs::GaAs;
		break;
	}
}

//-------------------------Create alloys-------------------------------------------------------------------------------------
//TRIPPLE==============
A_xB_1mxC get_ABC_2xIII(const char* A, const char* B, const char* C, double x, double T, trippleAlloyBowings::bowing bowing)
{
	std::string buff;

	buff = string(A) + string(C);
	semiconductor ACq = AB_parser(buff.c_str());
	buff = string(B) + string(C);
	semiconductor BCq = AB_parser(buff.c_str());
	param ACn = substra(ACq);
	param BCn = substra(BCq);

	AB ACs(ACn, T);
	AB BCs(BCn, T);

	A_xB_1mxC ABC(T, x, ACs, BCs, bowing);
	return ABC;

}

A_xB_1mxC get_ABC_2xV(const char* A, const char* B, const char* C, double x, double T, trippleAlloyBowings::bowing bowing)
{
	std::string buff;

	buff = string(A) + string(B);
	semiconductor ABq = AB_parser(buff.c_str());
	buff = string(A) + string(C);
	semiconductor ACq = AB_parser(buff.c_str());
	param ABn = substra(ABq);
	param ACn = substra(ACq);

	AB ABs(ABn, T);
	AB ACs(ACn,T);

	A_xB_1mxC ABC(T, x, ABs, ACs, bowing);
	return ABC;

}
//QUADRUPLE==============
ABCD_x1mx_y1my get_ABCD_2x2(const char* A, const char* B, const char* C, const char* D,double x, double y, double T, trippleAlloyBowings::bowing bABD, trippleAlloyBowings::bowing bABC, trippleAlloyBowings::bowing bACD, trippleAlloyBowings::bowing bBCD)
{
	A_xB_1mxC ABD = get_ABC_2xIII(A, B, D, x, T, bABD);
	A_xB_1mxC ABC = get_ABC_2xIII(A, B, C, x, T, bABC);
	A_xB_1mxC ACD = get_ABC_2xV(A, C, D, y, T, bACD);
	A_xB_1mxC BCD = get_ABC_2xV(B, C, D, y, T, bBCD);
	return ABCD_x1mx_y1my(T, x, y, ABD, ABC, ACD, BCD);
}
//--------------------------QUADRUPLE INTERPOLATION AS ONE PARAMETER IS FIXED AND ONE CHANGES----------------------------------
void functionInterpolation(double a_sub, const char* A, const char* B, const char* C, const char* D, double y, double T, trippleAlloyBowings::bowing bABD, trippleAlloyBowings::bowing bABC, trippleAlloyBowings::bowing bACD, trippleAlloyBowings::bowing bBCD)
{
	string fileName = (std::string(A) + std::string(B) + std::string(C) + std::string(D) + "_Interp.dat");
	std::ofstream file;
	file.setf(3, std::ios::floatfield);
	file.open(fileName.c_str(), std::ios::out);
	if (!file) {
		throw "cannot open a file\n";
	}
	file << std::fixed << std::setprecision(3) << "x" << "\t \t";
	file << std::fixed << std::setprecision(3) << "y" << "\t \t";
	file << std::fixed << std::setprecision(3) << "m_eff" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_hh" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_lh" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ev_so" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Ec" << "\t \t";
	file << std::fixed << std::setprecision(3) << "Eg" << std::endl;

	const double x_step = 0.001;
	const double stepNum = 1.0 / x_step;
	for (int i = 0; i < stepNum; i++) {
		double x = i * x_step;
		ABCD_x1mx_y1my ABCD = get_ABCD_2x2(A, B, C, D, x, y, T, bABD, bABC, bACD, bBCD);
		ABCD.E_T();
		ABCD.includeStrain(a_sub);
		ABCD.printToFile(file);
	}
	file.close();
}

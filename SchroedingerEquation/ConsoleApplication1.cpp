// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "classes.h"
using namespace std;
int main(int argc, char** argv)
{

	std::scientific;
	//arguments:
	//1) rank
	//2) xi
	//3) xf
	//4) step
	//5) function
	//6) filePath
	try {

		numFunction* temp;

		int rank;
		double xi;
		double xf;
		double step;
		const char* function;
		const char* filePath;
		if (argc == 7) {
			 rank = stoi(argv[1], NULL);
			if (rank > 9) throw "Rank to big, sorry";
			  xi = strtod(argv[2], NULL);
			  xf = strtod(argv[3], NULL);
			  step = strtod(argv[4], NULL);
			  function = argv[5];
			  filePath = argv[6];
		}
		else if(argc ==1) {
			rank = 4;
			if (rank > 9) throw "Rank to big, sorry";
			 xi = -2;
			  xf = 5;
			  step = 0.01;
			  function = "hermite";
			 filePath = "calculations.dat";
		}
		else {
			return -1;
		}
		string f(function);
		string p(filePath);

		funParser parse = functionParser(function);

			usage_interface * interface;
			switch (parse)
			{
			case x2:
				temp = new numx2(rank, step, xi, xf);
				interface = new usage_interface(temp);
				break;
			//case x:
				//interface = usage_interface(numFunction(rank, step, xi, xf));
				//break;
			case sinx:
				temp = new numsinx(rank, step, xi, xf);
				interface = new usage_interface(temp);
				break;
			case hermite:
				temp = new numHermite(rank, step, xi, xf);
				interface = new usage_interface(temp);		
				break;

			case nothing:
				throw "Nothing to do here. No function like that in my databank \n";
				break;
			default:
				temp = new numHermite(rank, step, xi, xf);
				interface = new usage_interface(temp);
				break;
			}
			interface->printToFile(filePath);
			//counting integral----------------------------------
			int tempRank;
			if (rank < 9 && rank >1) {
				tempRank = rank - 1;
			}
			else {
				tempRank = 3;
			}
			long double xip = -12;
			long double xfp = 12;
			long double stepp = 0.1;
			numHermite temp3(rank, stepp, xip, xfp);
			numHermite temp2(tempRank, step, xip, xfp);
			int stepNum = (static_cast<int>((xfp - xip) / stepp));
			long double* tempForIntAn = new long double[stepNum];
			long double* tempForIntNum = new long double[stepNum];
			long double stepper = 0.0;
			for (int i = 0; i < stepNum; i++) {
				long double x = xip + stepper;
				tempForIntAn[i] = temp3.getPointAn(i) * temp2.getPointAn(i) * exp_m_x2(x);
				tempForIntNum[i] = temp3.getPointNum(i) * temp2.getPointNum(i) * exp_m_x2(x);
				stepper = stepper + stepp;
			}
			printerIntegrals(xip, xfp, stepp, "integrals.dat", tempForIntAn, tempForIntNum);
			//--------------------------------------------------------------------------------

			return 0;
	}

	catch(const char * exeption){
		cout << exeption << endl;
		return 0;
	}
	catch (...) {
		cout << "Unexpected error \n";
		return -1;
	}
 }
 
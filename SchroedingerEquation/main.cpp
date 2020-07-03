#include "Parameters.h"
#include "Numerical_methods.h"
#include "useInMainTests.h"


int main(int argc, char** argv) {

	try {
		NumericalSchroedingerRun(argc, argv);
	}
	catch (string s) {
		std::cout << s;
		return -1;
	}
	catch (...) {
		cout << "something happened\n";
		return -1;
	}

}
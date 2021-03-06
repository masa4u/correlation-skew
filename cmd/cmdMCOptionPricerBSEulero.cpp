#include "MCOptionPricer.hpp"
#include "ProcessBiVariateLognormalEulero.hpp"
#include "Equity.hpp"
#include "BasketOption.hpp"
#include "MCResults.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>


using namespace std;

int main (int argc,char* argv[])
{
	if (argc < 1) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "Usage is ...\n"; // Inform the user of how to use the program
		std::cin.get();
		exit(0);
	} else { // if we got enough parameters...
		int nSim= 1000000;
		int dim = 100;
		double multiplier = 100;
		double w1 = 0.3;
		double w2 = 0.7;
		double strike = 1;
		double sigma1 = 0.2;
		double sigma2 = 0.3;
		double rho = 0.142;
		double expiry = 1;
		double riskFreeRate = 0.03;
		Option::type cp = Option::call;

		std::cout << argv[0];
		for (int i = 1; i < argc; i++) { /* We will iterate over argv[] to get the parameters stored inside.
		 * Note that we're starting on 1 because we don't need to know the
		 * path of the program, which is stored in argv[0] */
			string arg = string(argv[i]);
			if (i + 1 != argc)
			{// Check that we haven't finished parsing already
				if (arg == "-riskFree") {
					riskFreeRate = atof(argv[i + 1]);
				} else if (arg == "-s1") {
					sigma1 = atof(argv[i + 1]);
				} else if (arg == "-s2") {
					sigma2 = atof(argv[i + 1]);
				} else if (arg == "-rho") {
					rho = atof(argv[i + 1]);
				} else if (arg == "-w1") {
					w1 = atof(argv[i + 1]);
				} else if (arg == "-w2") {
					w2 = atof(argv[i + 1]);
				} else if (arg == "-T") {
					expiry = atof(argv[i + 1]);
				} else if (arg == "-Nsim") {
					nSim = atof(argv[i + 1]);
				} else if (arg == "-strike") {
					strike = atof(argv[i + 1]);
				} else if (arg == "-dim") {
					dim = atof(argv[i + 1]);
				}else {
					std::cout << "Not enough or invalid arguments, please try again.\n";
					exit(0);
				}
			std::cout << argv[i] << " ";
			}
			i = i + 1;
		}

		srand (time(NULL));


		Equity equity1 = Equity(multiplier);
		Equity equity2 = Equity(multiplier);

		Basket basket = Basket(&equity1, &equity2, w1, w2);
		BasketOption opzione = BasketOption(expiry, &basket,  strike,cp);

		NormalDistribution* N1 = new NormalDistribution();
		NormalDistribution* N2 = new NormalDistribution();

		ProcessBiVariateLognormalEulero process = ProcessBiVariateLognormalEulero(sigma1,sigma2,rho, nSim,dim,N1,N2);
		MCOptionPricer pricer = MCOptionPricer(&opzione,
												&process,
												riskFreeRate ,
												nSim,
												new MCResultsErroreMontecarlo(nSim));
		double price = pricer.getOptionPrice();
		double MCerror = pricer.getErroreMontecarlo();


		ofstream miofile;
		miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\MCPrice.csv"/*,std::ios_base::app*/);
		miofile << setprecision(11) << price << "\n" << MCerror << "\n";
		miofile.close();

		return 0;
	}
}

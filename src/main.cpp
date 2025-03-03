#include <iostream>
#include <fstream>
#include "methods.h"
#include <ginac/ginac.h>
#include <string>
#include <QApplication>
#include "window.h"

bool isNum(std::string& s) {
	int dots = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (i == 0 && s[i] == '-') {
			continue;
		}
		if (s[i] == '.') {
			dots++;
		}
		else if (s[i] < '0' || s[i] > '9') {
			return false;
		}
		if (dots > 1) {
			return false;
		}
	}
	return true;
}

bool isInt(std::string& s) {
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] < '0' || s[i] > '9') {
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	bool inpT = false;
	std::cout << "Choose input type (f for file, t for terminal):\n";
	std::string inpS = "";
	std::cin >> inpS;
	while (inpS != "f" && inpS != "t") {
		std::cout << "Sorry! Looks like your input is wrong! Try again!\n";
		std::cin >> inpS;
	}
	std::string filename = "";
	std::ifstream inp;
	if (inpS == "f") {
		std::cout << "Enter input file name:\n";
		std::cin >> filename;
		inp = std::ifstream(filename);
		if (!inp) {
			std::cout << "Error opening file!\n";
			return 0;
		}
	}
	else {
		inpT = true;
		inp.open("/dev/stdin");
	}
	std::cout << "Choose output type (f for file, t for terminal):\n";
	inpS = "";
	std::cin >> inpS;
	while (inpS != "f" && inpS != "t") {
		std::cout << "Sorry! Looks like your input is wrong! Try again!\n";
		std::cin >> inpS;
	}
	std::ofstream out;
	if (inpS == "f") {
		std::cout << "Enter output file name:\n";
		std::cin >> filename;
		out = std::ofstream(filename);
	}
	else {
		out.open("/dev/stdout");
	}
	if (inpT) {
		std::cout << "Select mode for program (1 for single equation, 2 for system of equations):\n";
	}
	int mode = 0;
	while (mode < 1 || mode > 2) {
		inp >> inpS;
		if (!isInt(inpS)) {
			std::cout << "Unexpected value entered! Try again\n";
			if (!inpT) { 
				return 0;
			}	
			continue;
		}
		mode = std::stoi(inpS);
		if (mode < 1 || mode > 2) {
			std::cout << "Unexpected value entered! Try again\n";
			if (!inpT) { 
				return 0;
			}
		}
	}
	switch (mode) {
		case 1: {
				int (*methods[3])(double, double, double, double &, GiNaC::ex &, GiNaC::symbol &, long long &);
				methods[0] = binary;
				methods[1] = simple_iter;
				methods[2] = newton;
				GiNaC::symbol x("x");
				std::vector <GiNaC::ex> ex = {3*pow(x, 3)+1.7*pow(x, 2)-15.42*x+6.89, 2.74*pow(x, 3)-1.93*pow(x, 2)-15.28*x-3.72, pow(x, 3)+2.84*pow(x, 2)+5.606*x-14.766, sin(x)};
				int ind = -1;
				while (ind < 1 || ind > ex.size()) {
					if (inpT) {
						std::cout << "Select equation:\n";
						for (size_t i = 0; i < ex.size(); ++i) {
							std::cout << i+1 << ") " << ex[i] << "\n";
						}
					}
					inp >> inpS;
					if (!isInt(inpS)) {
						std::cout << "Unexpected value entered! Try again\n";
						if (!inpT) { 
							return 0;
						}
						continue;
					}
					ind = std::stoi(inpS);
					if (ind < 1 || ind > ex.size()) {
						std::cout << "Unexpected value entered! Try again\n";
						if (!inpT) { 
							return 0;
						}
					}
				}
				ind--;
				if (inpT) {
					std::cout << "Select calculation method (1 for binary, 2 for simple iteration, 3 for Newton):\n";
				}
				int calcmode = 0;
				while (calcmode < 1 || calcmode > 3) {
					inp >> inpS;
					if (!isInt(inpS)) {
						std::cout << "Unexpected value entered! Try again\n";
						if (!inpT) { 
							return 0;
						}
						continue;
					}
					calcmode = std::stoi(inpS);
					if (calcmode < 1 || calcmode > 3) {
						std::cout << "Unexpected value entered! Try again\n";
						if (!inpT) { 
							return 0;
						}
					}
				}
				calcmode--;
				if (inpT) {
					std::cout << "Enter left and right border for interval:\n";
				}
				double l, r;
				inpS = "a";
				std::string inpS1 = "a";
				while (!isNum(inpS) || !isNum(inpS1) || std::stod(inpS) >= std::stod(inpS1)) {
					inp >> inpS >> inpS1;
					if (!isNum(inpS) || !isNum(inpS1) || std::stod(inpS) >= std::stod(inpS1)) { 
						std::cout << "Unexpected values! Try again\n";
						if (!inpT) { 
							return 0;
						}
					}
				}
				l = std::stod(inpS);
				r = std::stod(inpS1);
				double acc = -0.1;
				if (inpT) {
					std::cout << "Enter accuracy: \n";
				}
				while (acc < 0) {
					inp >> inpS;
					if (!isNum(inpS)) {
						std::cout << "Unexpected accuracy value! Try again\n";
						if (!inpT) {
							return 0;
						}
						continue;
					}
					acc = std::stod(inpS);
					if (acc < 0) {
						std::cout << "Unexpected accuracy value! Try again\n";
						if (!inpT) {
							return 0;
						}
					}
				}
				double ans = 0;
				long long iters = 0;
				switch (methods[calcmode](l, r, acc, ans, ex[ind], x, iters)) {
					case 0:
						out << x << " = " << ans << "\nF(" << ans << ") = " << subst(ex[ind], x, ans) << "\nCalculating took " << iters << " iterations" << std::endl;
						break;
					case 1:
						out << "Maximum iterations limit reached! The best possible value found is " << ans << std::endl;
						break;
					case 2:
						out << "Unable to find roots! The process doesn't add up!" << std::endl;
						break;
				}
				QApplication app(argc, argv);
				window win(ex[ind], x, l, r, 0);
				win.show();
				return app.exec();
			}
		case 2: {
				std::vector<double> a = {0, 0}, b = {1, 1}, res(2);
				std::vector<GiNaC::symbol> xes = {GiNaC::symbol("x"), GiNaC::symbol("y")};
				std::vector<std::vector<GiNaC::ex>> sys = {{0.1*pow(xes[0], 2)+xes[0]+0.2*pow(xes[1], 2)-0.3, 0.2*pow(xes[0], 2)+xes[1]+0.1*xes[0]*xes[1]-0.7}, {sin(xes[0]+1)-xes[1]-1.2, 2*xes[0]+cos(xes[1])-2}};
				std::vector<std::vector<GiNaC::ex>> phisys = {{0.3-0.1*pow(xes[0],2)-0.2*pow(xes[1], 2), 0.7-0.2*pow(xes[0], 2)-0.1*xes[1]*xes[0]}, {(2-cos(xes[1]))/2, sin(xes[0]+1)-1.2}};
				int ind = -1;
				while (ind < 1 || ind > sys.size()) {
					if (inpT) {
						std::cout << "Select system (enter a single number):\n";
						for (size_t i = 0; i < sys.size(); ++i) {
							std::cout << i+1 << ") ";
							for (size_t j = 0; j < sys[i].size(); ++j) {
								std::cout << sys[i][j] << " = 0\n";
							}
						}
					}
					inp >> inpS;
					if (!isInt(inpS)) {
						std::cout << "Unexpected system value entered! Try again\n";
						if (!inpT) {
							return 0;
						}
						continue;
					}
					ind = std::stoi(inpS);
					if (ind < 1 || ind > sys.size()) {
						std::cout << "Unexpected system value entered! Try again\n";
						if (!inpT) {
							return 0;
						}
					}
				}
				ind--;
				if (inpT) {
					std::cout << "Enter left and right borders for each variable interval:\n";
				}
				for (size_t i = 0; i < xes.size(); ++i) {
					if (inpT) {
						std::cout << xes[i] << "\n";
					}
					inpS = "a";
					std::string inpS1 = "a";
					while (!isNum(inpS) || !isNum(inpS1) || std::stod(inpS) >= std::stod(inpS1)) {
						inp >> inpS >> inpS1;
						if (!isNum(inpS) || !isNum(inpS1) || std::stod(inpS) >= std::stod(inpS1)) { 
							std::cout << "Unexpected border values! Try again\n";
							if (!inpT) {
								return 0;
							}
						}
					}
					a[i] = std::stod(inpS);
					b[i] = std::stod(inpS1);
				}
				double acc = -0.1;
				if (inpT) {
					std::cout << "Enter accuracy: \n";
				}
				while (acc < 0) {
					inp >> inpS;
					if (!isNum(inpS)) {
						std::cout << "Unexpected accuracy value! Try again\n";
						if (!inpT) {
							return 0;
						}
						continue;
					}
					acc = std::stod(inpS);
					if (acc < 0) {
						std::cout << "Unexpected accuracy value! Try again\n";
						if (!inpT) {
							return 0;
						}
					}
				}
				long long iters = 0;
				std::vector<std::vector<double>> diffs;
				switch (system_simple_iter(a, b, acc, res, phisys[ind], xes, iters, diffs)) {
					case 0:
						for (size_t i = 0; i < res.size(); ++i) {
							out << xes[i] << " = " << res[i] << "\n";
						}
						out << "This took " << iters << " iterations\n";
						for (size_t i = 0; i < diffs.size(); ++i) {
							out << "Diffs " << i+1 << ":\n";
							for (size_t j = 0; j < diffs[i].size(); ++j) {
								out << "\t" << xes[j] << ": " << diffs[i][j] << "\n";
							}
						}
						break;
                                        case 1:
                                                out << "Maximum iterations limit reached! The best possible values found are\n";
						for (size_t i = 0; i < res.size(); ++i) {
							out << xes[i] << " = " << res[i] << "\n";
						}
                                                break;
                                        case 2:
                                                out << "Unable to find roots! The process doesn't add up!\n";
                                                break;

				}
				QApplication app(argc, argv);
				window win(sys[ind], xes, a, b, 0.001, 0);
				win.show();
				return app.exec();
			}
		default:
			out << "Unexpected mode value! Try again\n";
			break;
	}
}

#include <iostream>
#include <fstream>
#include "methods.h"
#include <ginac/ginac.h>
#include <string>
#include <QApplication>
#include "window.h"
#include <vector>
#include <cmath>

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
		std::cout << "Would you like to use one of existing functions? (Y/N)\n";
	}
	inp >> inpS;
	while (inpS != "N" && inpS != "n" && inpS != "Y" && inpS != "y") {
		if (!inpT) {
			return 0;
		}
		out << "Sorry! Looks like your input is wrong! Try again!\n";
		inp >> inpS;
	}
	std::vector<double> x, y;
	int n = 0;
	double h = 0;
	if (inpS == "N" || inpS == "n") {	
		if (inpT) {
			std::cout << "Enter n:\n";
		}
		while (n <= 2) {
			inp >> inpS;
			if (!isInt(inpS)) {
				std::cout << "Unexpected value entered! Try again\n";
				if (!inpT) { 
					return 0;
				}	
				continue;
			}
			n = std::stoi(inpS);
			if (n <= 0) {
				std::cout << "Unexpected value entered! Try again\n";
				if (!inpT) { 
					return 0;
				}
			}
		}
		if (inpT) {
			std::cout << "Now enter x and y for each point:\n";
		}
		x.resize(n);
		y.resize(n);
		for (int i = 0; i < n; ++i) {
			inp >> inpS;
			while (!isNum(inpS)) {
				std::cout << "Unexpected value entered! Try again\n";
				if (!inpT) {
					return 0;
				}
				inp >> inpS;
			}
			x[i] = std::stod(inpS);
			if (i == 1) {
				h = x[i]-x[i-1];
			}
			if (i > 1 && std::abs((x[i-1]-x[i]) - (x[i-2]-x[i-1])) > 0.0001) {
				std::cout << "dx is not const! Try again!\n";
				if (!inpT) {
					return 0;	
				}
			}
			inp >> inpS;
			while (!isNum(inpS)) {
				std::cout << "Unexpected value entered! Try again\n";
				if (!inpT) {
					return 0;
				}
				inp >> inpS;
			}
			y[i] = std::stod(inpS);
		}
	}
	else {
		if (inpT) {
			std::cout << "Choose function (1 - sin(x)):\n";
		}
		while (n != 1) {
			inp >> inpS;
			if (!isInt(inpS)) {
				std::cout << "Unexpected value entered! Try again\n";
				if (!inpT) { 
					return 0;
				}	
				continue;
			}
			n = std::stoi(inpS);
			if (n <= 0) {
				std::cout << "Unexpected value entered! Try again\n";
				if (!inpT) { 
					return 0;
				}
			}
		}
		n = 5;
		h = 0.5;
		x = {0.5, 1.0, 1.5, 2.0, 2.5};
		y.resize(5);
		for (int i = 0; i < n; ++i) {
			y[i] = sin(x[i]);
			std::cout << y[i] << " ";
		}
	}
	std::vector<std::vector<double>> dy(n, std::vector<double>(n, 0));
	for (int i = 0; i < n; ++i) {
		dy[i][0] = y[i];
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < n-i; ++j) {
			dy[j][i] = dy[j+1][i-1]-dy[j][i-1];
		}
	}
	std::vector <long long> fact(n);
	std::vector <double> h_pow(n);
	fact[0] = 1;
	h_pow[0] = 1;
	std::vector <double> a(n);
	GiNaC::symbol xsymb("x");
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			out << dy[i][j] << " ";
		}
		out << "\n";
	}
	std::cout << "calculated dy" << std::endl;
	double xval;
	if (inpT) {
		std::cout << "Enter x:\n";
	}
	inp >> xval;
	GiNaC::ex newton = 0;
{
	GiNaC::ex t = (xsymb-x[0])/h;	
	for (int i = 0; i < n; ++i) {
		if (i > 0) {
			fact[i] = fact[i-1]*i;
			h_pow[i] = h_pow[i-1]*h;
		}
		GiNaC::ex coef = 1;
		for (int j = 0; j < i; ++j) {
			coef *= t-j;
		}
		newton += dy[0][i]*coef/fact[i];
	}
	out << "Newton says: " << newton.subs(xsymb == xval) << "\n";
	std::cout << "Newton over" << std::endl;
}
{
	GiNaC::ex ln = 0;
	for (int i = 0; i < n; ++i) {
		GiNaC::ex cur = 1;
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				continue;
			}
			cur *= (xsymb-x[j])/(x[i]-x[j]);
		}
		ln += y[i]*cur;
	}
	out << "Lagrange says: " << ln.subs(xsymb == xval) << "\n";
	std::cout << "Lagrange over" << std::endl;
}
{
	double gauss = 0;
	double t = (xval-x[x.size()/2])/h;
	int mid = x.size()/2;	
	double coef = 1;
	if (t >= 0) {
		for (int i = 0; i <= n/2; ++i) {
			if (mid-i < 0) {
				break;
			}
			if (2*i >= fact.size()) {
				fact.push_back(2*i*fact.back());
			}
			gauss += coef*dy[mid-i][2*i]/fact[2*i];
			coef *= (t+i);
			if (2*i+1 >= dy[mid-i].size()) {
				break;
			}
			if (2*i+1 >= fact.size()) {
				fact.push_back((2*i+1)*fact.back());
			}
			gauss += coef*dy[mid-i][2*i+1]/fact[2*i+1];
			coef *= (t-i-1);
		}
	}
	else {
		for (int i = 0; i <= n/2; ++i) {
			if (mid-i < 0) {
				break;
			}
			if (2*i >= fact.size()) {
				fact.push_back(2*i*fact.back());
			}
			gauss += coef*dy[mid-i][2*i]/fact[2*i];
			coef *= (t-i);
			if (2*i+1 >= dy[mid-i].size()) {
				break;
			}
			if (2*i+1 >= fact.size()) {
				fact.push_back((2*i+1)*fact.back());
			}
			gauss += coef*dy[mid-i-1][2*i+1]/fact[2*i+1];
			coef *= (t+i+1);
		}
	}
	out << "Gauss says: " << gauss << "\n";
}
	GiNaC::ex gauss = 0;
{
	GiNaC::ex t = (xsymb-x[x.size()/2])/h;
	int mid = x.size()/2;	
	GiNaC::ex coef = 1;
	for (int i = 0; i <= n/2; ++i) {
		if (mid-i < 0) {
			break;
		}
		if (2*i >= fact.size()) {
			fact.push_back(2*i*fact.back());
		}
		gauss += coef*dy[mid-i][2*i]/fact[2*i];
		coef *= (t+i);
		if (2*i+1 >= dy[mid-i].size()) {
			break;
		}
		if (2*i+1 >= fact.size()) {
			fact.push_back((2*i+1)*fact.back());
		}
		gauss += coef*dy[mid-i][2*i+1]/fact[2*i+1];
		coef *= (t-i-1);
	}
}
{	
	int sz = x.size();
	sz -= sz&1;
	double t = (xval-x[sz/2])/h;
	if (std::abs(t) <= 0.25) {
		int mid = sz/2;
		double coef1 = t;
		double coef2 = t*t;
		double steer = y[mid];
		for (int i = 0; i <= n/2; ++i) {
			if (mid-i-1 < 0 || 2*i+2 >= dy[mid-i-1].size()) {
				break;
			}
			steer += coef1*(dy[mid-i-1][2*i+1]+dy[mid-i][2*i+1])/(fact[1+2*i]*2);
			coef1 *= (t*t-(i+1)*(i+1));	
			steer += coef2*dy[mid-i-1][2*i+2]/fact[2+2*i];
			coef2 *= (t*t-(i+1)*(i+1));
		}
		out << "Steerling says " << steer << "\n";
	}
}
{
	int sz = x.size();
	if (sz > 1) {
		sz -= (1-sz&1);
		double t = (xval-x[sz/2])/h;
		if (std::abs(t) >= 0.25 && std::abs(t) <= 0.75) {
			int mid = sz/2;
			double coef2 = (t-0.5)*t*(t-1);
			double coef1 = t*(t-1);
			double bessel = (y[mid]+y[mid+1])/2+(t-0.5)*dy[mid][1];
			for (int i = 0; i < n; ++i) {
				if (mid-i-1 < 0 || 2*i+2 >= dy[mid-i-1].size()) {
					break;
				}
				bessel += coef1*(dy[mid-i-1][2*i+2]+dy[mid-i][2*i+2])/(fact[2+2*i]*2);
				coef1 *= (t+i+1)*(t-i-2);
				bessel += coef2*dy[mid-i-1][2*i+3]/fact[3+2*i];
				coef2 *= (t+i+1)*(t-i-2);
			}
			out << "Bessel says " << bessel << "\n";
		}
	}
}
	QApplication app(argc, argv);
	window win(&newton, &gauss, &xsymb, x[0], x.back());
	win.show();
	return app.exec();
}

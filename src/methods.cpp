#include <cmath>
#include <iostream>
#include "methods.h"
#include <ginac/ginac.h>

#define maxiter 1e5

double subst(GiNaC::ex &ex, GiNaC::symbol &x, double val) {
	return GiNaC::ex_to<GiNaC::numeric>(ex.subs(x == GiNaC::ex(val))).to_double();
}

double subst(GiNaC::ex &ex, GiNaC::exmap& map) {
	return GiNaC::ex_to<GiNaC::numeric>(ex.subs(map)).to_double();
}

int binary(double a, double b, double acc, double &res, GiNaC::ex &ex, GiNaC::symbol &x, long long& n) {
	res = (a+b)/2;
	double f = subst(ex, x, res);
	n = 0;
	while ((n <= maxiter) && (std::abs(f) > acc)) {
		if (subst(ex, x, a)*f > 0) {
			a = res;
		}
		else {
			b = res;
		}
		res = (a+b)/2;
		f = subst(ex, x, res);
		++n;
	}	
	if (std::abs(f) > acc) {
		return 1;
	}
	return 0;
}

int newton(double a, double b, double acc, double &res, GiNaC::ex &ex, GiNaC::symbol &x, long long& n) {
	GiNaC::ex fdiff = ex.diff(x, 1);
	GiNaC::ex fdiff2 = ex.diff(x, 2);
	if (subst(fdiff2, x, a)*subst(fdiff, x, a)) {
		res = a;
	}
	else {
		res = b;
	}
	n = 0;
	double f = subst(ex, x, res);
	while ((n <= maxiter) && (std::abs(f) > acc)) {
		res = res - f/subst(fdiff, x, res);
		f = subst(ex, x, res);
		++n;
	}
        if (std::abs(f) > acc) {
		return 1;
	}
	return 0;
}

int simple_iter(double a, double b, double acc, double &res, GiNaC::ex &ex, GiNaC::symbol &x, long long& n) {
	GiNaC::ex fdiff = ex.diff(x, 1);
	double maxdiff = std::max(std::abs(subst(fdiff, x, a)), std::abs(subst(fdiff, x, b)));	
	double lambda = subst(fdiff, x, (a+b)/2) > 0 ? -1/maxdiff : 1/maxdiff;
	GiNaC::ex phi = x+lambda*ex;
	GiNaC::ex phidiff = phi.diff(x, 1);
	if (std::max(std::abs(subst(phidiff, x, a)), std::abs(subst(phidiff, x, b))) > 1) {
		return 2;
	}
	GiNaC::ex fdiff2 = ex.diff(x, 2);
	if (subst(fdiff2, x, a)*subst(fdiff, x, a)) {
		res = a;
	}
	else {
		res = b;
	}
	n = 0;
	double f = subst(ex, x, res);
	while ((n <= maxiter) && (std::abs(f) > acc)) {
		res = subst(phi, x, res);
		f = subst(ex, x, res);
		++n;
	}
	if (res < a || res > b) {
		return 2;
	}
	if (std::abs(f) > acc) {
                return 1;
        }
	return 0;

}

int system_simple_iter(std::vector<double> &a, std::vector<double> &b, double acc, std::vector<double> &res, std::vector<GiNaC::ex>& phi, std::vector<GiNaC::symbol> &s, long long& n, std::vector<std::vector<double>>& diffs) {
	std::vector<GiNaC::ex> phidiffs(s.size());
	GiNaC::exmap mapa, mapb, map;
	for (size_t i = 0; i < phi.size(); ++i) {
		mapa[s[i]] = GiNaC::ex(a[i]);
		mapb[s[i]] = GiNaC::ex(b[i]);
	}
	for (size_t i = 0; i < phi.size(); ++i) {
		double suma = 0, sumb = 0;
		for (size_t j = 0; j < s.size(); ++j) {
			phidiffs[j] = phi[i].diff(s[j], 1);
			suma += std::abs(subst(phidiffs[j], mapa));
			sumb += std::abs(subst(phidiffs[j], mapb));
			if (suma > 1 || sumb > 1) {
				return 2;
			}
		}	
		if (suma > 1 || sumb > 1) {
			return 2;
		}
	}
	std::vector <double> newval(s.size());
	for (size_t i = 0; i < res.size(); ++i) {
		res[i] = a[i];
		map[s[i]] = res[i];
	}
	bool close = false;
	n = 0;
	while (!close && n < maxiter) {
		close = true;
		diffs.push_back(std::vector<double>(phi.size()));
		for (size_t i = 0; i < phi.size(); ++i) {
			newval[i] = subst(phi[i], map);
			if (std::abs(newval[i]-res[i]) > acc) {
				close = false;
			}
			diffs.back()[i] = std::abs(newval[i]-res[i]);
			res[i] = newval[i];
			map[s[i]] = res[i];
		}
		++n;
	}
	for (size_t i = 0; i < res.size(); ++i) {
		if (res[i] < a[i] || res[i] > b[i]) {
			return 2;
		}
	}
	if (n >= maxiter) {
		return 1;
	}
	return 0;
}

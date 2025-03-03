#pragma once
#include <utility>
#include <ginac/ginac.h>

double subst(GiNaC::ex &ex, GiNaC::symbol &x, double val);
double subst(GiNaC::ex &ex, GiNaC::exmap& map);
int binary(double a, double b, double acc, double &res, GiNaC::ex &ex, GiNaC::symbol &x, long long& n);
int simple_iter(double a, double b, double acc, double &res, GiNaC::ex &ex, GiNaC::symbol &x, long long &n);
int newton(double a, double b, double acc, double &res, GiNaC::ex &ex, GiNaC::symbol &x, long long &n);
int system_simple_iter(std::vector<double> &a, std::vector<double> &b, double acc, std::vector<double> &res, std::vector<GiNaC::ex>& phi, std::vector<GiNaC::symbol> &s, long long& n, std::vector<std::vector<double>>& diffs);

#include <QWidget>
#include "window.h"
#include <iostream>
#include <QPainter>
#include <QColor>
#include <QKeyEvent>
#include <cmath>
#include <vector>
#include <complex>
#include <ginac/ginac.h>
#include "methods.h"

window::window(std::vector <GiNaC::ex>& funcs, std::vector<GiNaC::symbol>& s, std::vector<double>& a, std::vector<double>& b, double acc, QWidget* parent) : QWidget(parent) {
	this->setFixedHeight(800);
	this->setFixedWidth(800);
	r = 0;
	for (size_t i = 0; i < a.size(); ++i) {
		r = std::max(r, std::max(std::abs(a[i]), std::abs(b[i])));
	}
	l = -1*r;
	coef = 700/(r-l);
	for (double yval = a[1]; yval <= b[1]; yval += (b[1]-a[1])/1e3) {
		for (double xval = a[0]; xval <= b[0]; xval += (b[0]-a[0])/1e3) {
			GiNaC::exmap map;
			map[s[0]] = xval;
			map[s[1]] = yval;
			for (size_t i = 0; i < funcs.size(); ++i) {
				double sub = subst(funcs[i], map);
				if (std::abs(sub) <= acc) {
//					std::cout << xval << " " << yval << "\n";
					arr.push_back(std::make_pair(400+xval*coef, 400-yval*coef));	
				}
			}
		}
	}
}

window::window(GiNaC::ex& func, GiNaC::symbol& s, double a, double b, QWidget* parent) : QWidget(parent) {
	this->setFixedHeight(800);
	this->setFixedWidth(800);
	r = std::max(std::abs(a),std::abs(b));	
	for (double xval = a; xval <= b; xval += (b-a)/1e5) {
		double sub = subst(func, s, xval);
		r = std::max(r, std::abs(sub));
	}
	l = -1*r;
	coef = 700/(r-l);
	for (double xval = a; xval <= b; xval += (b-a)/1e5) {
		double sub = subst(func, s, xval);
		arr.push_back(std::make_pair(400+xval*coef, 400-coef*sub));
	}
}

void window::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.drawLine(400, 15, 400, 785);
	painter.drawLine(15, 400, 785, 400);
	painter.drawLine(390, 35, 400, 15);
	painter.drawLine(410, 35, 400, 15);
	painter.drawLine(765, 390, 785, 400);
	painter.drawLine(765, 410, 785, 400);
	double d = (r-l)/13;
	double lineCoef = 700/13;
	for (int i = -6; i <= 6; ++i) {
		painter.drawLine(390, i*lineCoef+400 ,410, i*lineCoef+400);
		painter.drawLine(i*lineCoef+400, 390, i*lineCoef+400, 410);
		QString s = QString::number(i*d, 'g', 3);
		painter.drawText(370, 400-i*lineCoef, s);
		if (i == 0) continue; 
		painter.drawText(i*lineCoef+400, 420, s);
	}
	for (int i = 1; i < arr.size(); ++i) {
//		std::cout << arr[i].first << " " << arr[i].second << "\n";
		painter.drawPoint(arr[i].first, arr[i].second);
	}
}

void window::destroy() {
	std::cout << "Bye\n";
}

void window::closeEvent(QCloseEvent* event) {
	this->destroy();
}

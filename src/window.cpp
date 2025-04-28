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
#include <algorithm>

window::window(GiNaC::ex* newtonfunc, GiNaC::ex* gaussfunc, GiNaC::symbol* xsymb, double a, double b, QWidget* parent) : QWidget(parent) {
	newton = *newtonfunc;
	gauss = *gaussfunc;
	l = a;
	r = b;
	x = *xsymb;
	this->setFixedHeight(800);
	this->setFixedWidth(800);
}

void window::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.drawLine(400, 15, 400, 785);
	painter.drawLine(15, 400, 785, 400);
	painter.drawLine(390, 35, 400, 15);
	painter.drawLine(410, 35, 400, 15);
	painter.drawLine(765, 390, 785, 400);
	painter.drawLine(765, 410, 785, 400);
	double d = 2*(r+0.1)/13;
	double lineCoef = 700/13;
	double coef = 700/(2*(r+0.1));
	double maxy = -1e9;
	double delta = (r-l)/10.0;
	std::cout << "Blue - Newton\nRed - Gauss\n";
	for (double xval = l; xval <= r; xval += delta) {
		maxy = std::max(maxy, std::max(GiNaC::ex_to<GiNaC::numeric>(gauss.subs(x == l)).to_double(), GiNaC::ex_to<GiNaC::numeric>(newton.subs(x == xval)).to_double()));
	}
	double coefy = 700/(2*(maxy+0.1));
	for (int i = -6; i <= 6; ++i) {
		painter.drawLine(390, i*lineCoef+400 ,410, i*lineCoef+400);
		painter.drawLine(i*lineCoef+400, 390, i*lineCoef+400, 410);
		QString s = QString::number(i*d, 'g', 3);
		painter.drawText(370, 400-i*lineCoef, s);
		if (i == 0) continue; 
		painter.drawText(i*lineCoef+400, 420, s);
	}	
	QPen newtonpen(Qt::blue, 4);
	painter.setPen(newtonpen);
	QPointF prev(400+coef*l, 400-coefy*GiNaC::ex_to<GiNaC::numeric>(newton.subs(x == l)).to_double());	
	for (double xval = l+delta; xval <= r; xval += delta) {
		QPointF cur(400+coef*xval, 400-coefy*GiNaC::ex_to<GiNaC::numeric>(newton.subs(x == xval)).to_double());
		painter.drawLine(prev, cur);
		prev = cur;
	}
	QPen gausspen(Qt::red, 2);
	painter.setPen(gausspen);
	prev = QPointF(400+coef*l, 400-coefy*GiNaC::ex_to<GiNaC::numeric>(gauss.subs(x == l)).to_double());	
	for (double xval = l+delta; xval <= r; xval += delta) {
		QPointF cur(400+coef*xval, 400-coefy*GiNaC::ex_to<GiNaC::numeric>(gauss.subs(x == xval)).to_double());
		painter.drawLine(prev, cur);
		prev = cur;
	}
}

void window::destroy() {
	std::cout << "Bye\n";
}

void window::closeEvent(QCloseEvent* event) {
	this->destroy();
}

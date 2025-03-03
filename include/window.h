#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include <QKeyEvent>
#include <vector>
#include <utility>
#include <ginac/ginac.h>

class window : public QWidget {
	public:
		window(std::vector <GiNaC::ex>& funcs, std::vector<GiNaC::symbol>& s, std::vector<double>& a, std::vector<double>& b, double acc, QWidget* parent = 0);
		window(GiNaC::ex& func, GiNaC::symbol& s, double a, double b, QWidget* parent = 0);
	protected:
		void closeEvent(QCloseEvent* event);
		void paintEvent(QPaintEvent* event);
		std::vector <std::pair<double, double>> arr;
		double l, r;
		double accur;
		double coef;
	private slots:
		void destroy();
};
#endif	

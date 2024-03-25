#include "proxy.h"

#include <iostream>
#include <memory>
#include <string>

class ICalc {
public:
	virtual ~ICalc() {};
	virtual double add(double first, double second) = 0;
	virtual double diff(double first, double second) = 0;
	virtual double mult(double first, double second) = 0;
};

class Calc : public ICalc {
public:
	double add(double first, double second) override {
		return first + second;
	}
	double diff(double first, double second) override {
		return first - second;
	}
	double mult(double first, double second) override {
		return first * second;
	}
};

class CalcWithLog : public ICalc {
	std::unique_ptr<ICalc> calc;
	std::string log;
	void addToLog(double first, double second, double result, char op) {
		log += std::to_string(first);
		log += " ";
		log += op;
		log += " ";
		log += std::to_string(second);
		log += " = ";
		log += std::to_string(result);
		log += "\n";
	}
public:
	CalcWithLog() {
		calc = std::make_unique<Calc>();
	}

	double add(double first, double second) override {
		auto result = calc->add(first, second);
		addToLog(first, second, result, '+');		
		return result;
	}
	double diff(double first, double second) override {
		auto result = calc->diff(first, second);
		addToLog(first, second, result, '-');
		return result;
	}
	double mult(double first, double second) override {
		auto result = calc->mult(first, second);
		addToLog(first, second, result, '*');
		return result;
	}

	void showLog() {
		std::cout << log;
	}
};

void testProxy() {
	CalcWithLog calcWithLog;

	calcWithLog.add(3, 5);
	calcWithLog.diff(4, 3);
	calcWithLog.mult(5, 5);

	calcWithLog.showLog();
}
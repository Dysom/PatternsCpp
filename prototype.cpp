#include <iostream>
#include <string>

#include "prototype.h"

class Vehile {
public:
	virtual ~Vehile() {}
	virtual Vehile * Clone() = 0;
	virtual std::string getDescription() const = 0;
};

class Helicopter : public Vehile {
	std::string color = "grey";
public:
	void setColor(const std::string& newColor) {
		color = newColor;
	}

	std::string getDescription() const override {
		return color + " helicopter";
	}
	Helicopter * Clone() override {
		return new Helicopter(*this);
	}
};

void testPrototype() {	

	auto firstHelicopter = new Helicopter;

	firstHelicopter->setColor("yellow");

	auto secondHelicopter = firstHelicopter->Clone();

	std::cout << "first helicopter is " << firstHelicopter->getDescription() << "\n";
	std::cout << "second helicopter is " << secondHelicopter->getDescription() << "\n";

	delete firstHelicopter;
	delete secondHelicopter;
}
#include <memory>
#include <iostream>
#include <string>

#include "abstractFactory.h"

class Plate {
public:
	virtual std::string getName() const = 0;
	virtual ~Plate() {}
};

class Spoon {
public:
	virtual std::string getName() const = 0;	
	virtual ~Spoon() {}
};

class Cup {
public:
	virtual std::string getName() const = 0;
	virtual ~Cup() {}
};

class Factory {
public:
	virtual std::unique_ptr<Plate> createPlate() = 0;
	virtual std::unique_ptr<Spoon> createSpoon() = 0;
	virtual std::unique_ptr<Cup> createCup() = 0;
};

class WoodenPlate : public Plate {
public:
	virtual std::string getName() const {
		return "wooden plate";
	}
};

class WoodenSpoon : public Spoon {
public:
	virtual std::string getName() const {
		return "wooden spoon";
	}
};

class WoodenCup : public Cup {
public:
	virtual std::string getName() const {
		return "wooden cup";
	}
};

class WoodenFactory : public Factory {
public:
	std::unique_ptr<Plate> createPlate() override {
		return std::make_unique<WoodenPlate>();
	}

	std::unique_ptr<Spoon> createSpoon() override {
		return std::make_unique<WoodenSpoon>();
	}

	std::unique_ptr<Cup> createCup() override {
		return std::make_unique<WoodenCup>();
	}
};

class MetalPlate : public Plate {
public:
	virtual std::string getName() const {
		return "metal plate";
	}
};

class MetalSpoon : public Spoon {
public:
	virtual std::string getName() const {
		return "metal spoon";
	}
};

class MetalCup : public Cup {
public:
	virtual std::string getName() const {
		return "metal cup";
	}
};

class MetalFactory : public Factory {
public:
	std::unique_ptr<Plate> createPlate() override {
		return std::make_unique<MetalPlate>();
	}

	std::unique_ptr<Spoon> createSpoon() override {
		return std::make_unique<MetalSpoon>();
	}

	std::unique_ptr<Cup> createCup() override {
		return std::make_unique<MetalCup>();
	}
};

void printProductNames(Factory & factory) {
	auto plate = factory.createPlate();
	auto spoon = factory.createSpoon();
	auto cup = factory.createCup();
	std::cout << "Product names of factory:\n";
	std::cout << "\tPlate: " << plate->getName() << "\n";
	std::cout << "\tSpoon: " << spoon->getName() << "\n";
	std::cout << "\tCup: " << cup->getName() << "\n";
}

void testAbstractFactory() {
	WoodenFactory woodenFactory;
	MetalFactory metalFactory;

	printProductNames(woodenFactory);
	std::cout << "\n";
	printProductNames(metalFactory);
}


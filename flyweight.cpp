#include "flyweight.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>



class Figure {
private:	
	const std::string name;
public:
	Figure(const std::string & n) : name(n) {
		std::cout << "Create figure: " << name << "\n";
	}
	void ShowFigure(int x, int y, int size) const {
		std::cout << "Show " << name << " in point {" << x << ", " << y << "} with size of " << size << " units\n";
	}
};

const Figure& getFigure(const std::string& name) {
	static std::unordered_map<std::string, std::unique_ptr<Figure>> figures;

	if (figures.find(name) == figures.end()) {
		figures.insert({name, std::make_unique<Figure>(name)});
	}

	return *figures.at(name);
}

void testFlyweight() {
	getFigure("Circle").ShowFigure(3, 5, 15);
	getFigure("Square").ShowFigure(4, 5, 10);
	getFigure("Circle").ShowFigure(4, 7, 12);
	getFigure("Circle").ShowFigure(3, 9, 15);
	getFigure("Square").ShowFigure(5, 3, 18);
}
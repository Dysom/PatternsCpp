#include <iostream>
#include <string>



class Scanner {
public:
	void Scan() {
		std::cout << "Scan document\n";
	}
};

class Printer {
public:
	void Print() {
		std::cout << "Print document\n";
	}
};

class Indicator {	
public:
	void On() {
		std::cout << "Indicator is on\n";
	}
	void Off() {
		std::cout << "Indicator is off\n";
	}
};

class Copier {
	Scanner scanner;
	Printer printer;
	Indicator indicator;
public:
	void Copy(int times = 1) {
		indicator.On();
		scanner.Scan();
		while (times--) {
			printer.Print();
		}
		indicator.Off();
	}
};

void testFacade() {
	Copier copier;
	copier.Copy(3);
}

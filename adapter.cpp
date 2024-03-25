#include "adapter.h"

#include <iostream>
#include <string>
#include <vector>

class INumViewer {
public:
	virtual ~INumViewer() {}
	virtual std::string getView(int num) = 0;
};

class BitVector {
	std::vector<bool> bits;
public:
	const std::vector<bool>& reset(int num) {
		bits.clear();

		do {
			bits.push_back(num & 1);
			num >>= 1;
		} while (num);

		return bits;
	}	
};

class BinaryViewer : public INumViewer {
	BitVector bits;
public:
	std::string getView(int num) override {
		auto & seq = bits.reset(num);

		std::string str;

		for (int i = seq.size() - 1; i >= 0; i--)
			str += seq[i] ? "1" : "0";

		return str;
	}
};

void testAdapter() {
	BinaryViewer binaryViewer;

	std::cout << binaryViewer.getView(15) << "\n";
	std::cout << binaryViewer.getView(107) << "\n";
	std::cout << binaryViewer.getView(209) << "\n";
}

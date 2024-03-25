#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "factoryMethod.h"

class Product {
public:
	virtual std::string getName() = 0;

	virtual ~Product() { }
};

class ProductFactory {
public:
	virtual std::unique_ptr<Product> create() = 0;
	virtual ~ProductFactory() {	}
};

class SomeProduct : public Product {
	std::string getName() override {
		return "SomeProduct";
	}
};

class OtherProduct : public Product {
	std::string getName() override {
		return "OtherProduct";
	}
};

class SomeProductFactory : public ProductFactory {
public:
	std::unique_ptr<Product> create() override {
		return std::make_unique<SomeProduct>();
	}
};

class OtherProductFactory : public ProductFactory {
public:
	std::unique_ptr<Product> create() override {
		return std::make_unique<OtherProduct>();
	}
};

void testFactoryMethod() {
	SomeProductFactory someProductFactory;
	OtherProductFactory otherProductFactory;

	std::vector<std::unique_ptr<Product>> products;

	products.push_back( someProductFactory.create() );
	products.push_back( otherProductFactory.create() );

	for (auto& product : products) {
		std::cout << product->getName() << "\n";
	}
}


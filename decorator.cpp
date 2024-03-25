#include "decorator.h"

#include <iostream>
#include <memory>
#include <string>

class IText {
public:
	virtual ~IText() {}
	virtual std::string get() const = 0;
};

class Text : public IText {
private:
	std::string text;
public:
	Text(const std::string & t) : text(t) {}

	std::string get() const override {
		return text;
	}
};

class TextWrapper : public IText {
private:
	std::shared_ptr<IText> textElem;
public:
	TextWrapper(std::shared_ptr<IText> tElem) : textElem(tElem) {}

	std::string get() const override {
		return std::string("<<< ") + textElem->get() + " >>>";
	}
};

void testDecorator() {
	TextWrapper textWrapper(std::make_shared<Text>("This is only text"));

	std::cout << textWrapper.get() << "\n";
}


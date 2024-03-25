#include "composite.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <exception>

class IHtmlElement;

typedef std::shared_ptr<IHtmlElement> IHESPtr;

void repeat(int times, void (* func) ()) {
	while (times--) {
		func();
	}
}

class IHtmlElement {
protected:
	std::string tagName;
	void setTagName(const std::string & newTagName) {
		tagName = newTagName;
	}
public:
	virtual ~IHtmlElement() = default;
	virtual void Add(const IHESPtr& iHESPtr) = 0;
	virtual void showOuterHTML(int padd = 0) = 0;
};

class HTMLElement : public IHtmlElement {
	std::vector<IHESPtr> children;
public:
	HTMLElement(const std::string& tName) {
		setTagName(tName);
	}
	void Add(const IHESPtr& iHESPtr) override {
		std::for_each(children.begin(), children.end(),
			[&iHESPtr](auto& sPtr) { if (sPtr.get() == iHESPtr.get()) throw std::runtime_error("HTMLElement: Item has already been added"); }
		);

		children.push_back(iHESPtr);
	}
	void showOuterHTML(int padd) override {
		repeat(padd, []() { std::cout << "\t"; });
		std::cout << "<" << tagName << ">\n";
		
		std::for_each(children.begin(), children.end(),
			[&padd](auto& sPtr) { sPtr->showOuterHTML(padd + 1); }
		);

		repeat(padd, []() { std::cout << "\t"; });
		std::cout << "</" << tagName << ">\n";
	}
};

class HTMLInputElement : public IHtmlElement {
	std::string type;
	std::string name;
public:
	HTMLInputElement(const std::string& t, const std::string& n) : type(t), name(n) {
		setTagName("input");
	}
	void Add(const IHESPtr& iHESPtr) override {
		throw std::runtime_error("HTMLInputElement: Can't add to input element");
	}
	void showOuterHTML(int padd) override {
		repeat(padd, []() { std::cout << "\t"; });
		std::cout << "<" << tagName << " ";
		std::cout << "type=\"" << type << "\" ";
		std::cout << "name=\"" << name << "\" ";
		std::cout << "/>\n";
	}
};

class TextNode : public IHtmlElement {
	std::string text;	
public:
	TextNode(const std::string& t) : text(t) {}
	void Add(const IHESPtr& iHESPtr) override {
		throw std::runtime_error("HTMLTextElement: Can't add to input element");
	}
	void showOuterHTML(int padd) override {
		repeat(padd, []() { std::cout << "\t"; });
		std::cout << text << "\n";
	}
};

void testComposite() {
	IHESPtr html(std::make_shared<HTMLElement>("html"));
	IHESPtr body(std::make_shared<HTMLElement>("body"));
	IHESPtr form(std::make_shared<HTMLElement>("form"));
	IHESPtr label(std::make_shared<HTMLElement>("label"));
	IHESPtr labelText(std::make_shared<TextNode>("Name: "));
	IHESPtr button(std::make_shared<HTMLElement>("button"));
	IHESPtr buttonText(std::make_shared<TextNode>("Submit!"));
	IHESPtr inputText(std::make_shared<HTMLInputElement>("text", "txt"));

	html->Add(body);
	body->Add(form);
	label->Add(labelText);
	button->Add(buttonText);
	form->Add(label);
	form->Add(inputText);
	form->Add(button);

	html->showOuterHTML();
}
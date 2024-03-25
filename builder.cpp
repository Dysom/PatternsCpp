#include "builder.h"

#include <iostream>
#include <memory>
#include <string>

class Detail {
	std::string name;
	std::string material;
	std::string form;
	std::string size;
public:
	void setName(const std::string& newName) {
		name = newName;
	}
	void setMaterial(const std::string& newMaterial) {
		material = newMaterial;
	}
	void setForm(const std::string& newForm) {
		form = newForm;
	}
	void setSize(const std::string& newSize) {
		size = newSize;
	}
	std::string getDescription() const {
		std::string description = "Description of ";
		description += name;
		description += ":";
		description += "\n\tmaterial: ";
		description += material;
		description += "\n\tform: ";
		description += form;
		description += "\n\tsize: ";
		description += size;

		return description;
	}
};

class DetailCreator {
protected:
	std::shared_ptr<Detail> detail;
public:
	virtual ~DetailCreator() {}

	std::shared_ptr<Detail> getDetail() {
		return detail;
	}

	void createNewDetail() {
		detail.reset(new Detail);
	}

	virtual void setNameToDetail() = 0;
	virtual void setMaterialToDetail() = 0;
	virtual void setFormToDetail() = 0;
	virtual void setSizeToDetail() = 0;
};

class DetailXCreator : public DetailCreator {
public:
	void setNameToDetail() override {
		detail->setName("detail-X");
	}
	void setMaterialToDetail() override {
		detail->setMaterial("copper");
	}
	void setFormToDetail() override {
		detail->setForm("cylinder");
	}
	void setSizeToDetail() override {
		detail->setSize("medium");
	}
};

class DetailZCreator : public DetailCreator {
public:
	void setNameToDetail() override {
		detail->setName("detail-Z");
	}
	void setMaterialToDetail() override {
		detail->setMaterial("steel");
	}
	void setFormToDetail() override {
		detail->setForm("bowl");
	}
	void setSizeToDetail() override {
		detail->setSize("big");
	}
};

class Manipulator {
private:
	DetailCreator* detailCreator = nullptr;
public:
	void setDetailCreator(DetailCreator* newDetailCreator) {
		detailCreator = newDetailCreator;
	}
	std::shared_ptr<Detail> getDetail() {
		return detailCreator->getDetail();
	}
	void createDetail() {
		detailCreator->createNewDetail();
		detailCreator->setNameToDetail();
		detailCreator->setMaterialToDetail();
		detailCreator->setFormToDetail();
		detailCreator->setSizeToDetail();
	}
};

void testBuilder() {
	DetailXCreator detailXCreator;
	DetailZCreator detailZCreator;

	Manipulator manipulator;
	manipulator.setDetailCreator(&detailXCreator);
	manipulator.createDetail();
	auto detailX = manipulator.getDetail();

	manipulator.setDetailCreator(&detailZCreator);
	manipulator.createDetail();
	auto detailZ = manipulator.getDetail();

	std::cout << detailX->getDescription();
	std::cout << "\n";
	std::cout << detailZ->getDescription();
	std::cout << "\n";
}

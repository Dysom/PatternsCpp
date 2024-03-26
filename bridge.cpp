#include "bridge.h"

#include <iostream>
#include <memory>
#include <string>

class IDisplay {
public:
	virtual void Show(const std::string& player, const std::string& movie) = 0;
	virtual ~IDisplay() {}
};

class Monitor : public IDisplay {
public:
	void Show(const std::string & player, const std::string & movie) override {
		std::cout << "Show \"" << movie << "\" using " << player << " on the monitor\n";
	}
};

class Projector : public IDisplay {
public:
	void Show(const std::string & player, const std::string & movie) override {
		std::cout << "Show \"" << movie << "\" using " << player << " on the projector\n";
	}
};

class IPlayer {
protected:
	std::shared_ptr<IDisplay> display;
public:
	virtual ~IPlayer() {}
	virtual void ShowMovie(const std::string& movie) = 0;
	void setDisplay(std::shared_ptr<IDisplay> d) {
		display = d;
	}
};

class CDPlayer : public IPlayer {
public:
	void ShowMovie(const std::string& movie) override {
		display->Show("CD-Player", movie);
	}
};

class VHDPlayer : public IPlayer {
public:
	void ShowMovie(const std::string& movie) override {
		display->Show("VHD-Player", movie);
	}
};

void testBridge() {
	std::shared_ptr<IDisplay> monitor(std::make_shared<Monitor>());
	std::shared_ptr<IDisplay> projector(std::make_shared<Projector>());

	CDPlayer cdPlayer;
	VHDPlayer vhdPlayer;

	cdPlayer.setDisplay(monitor);
	cdPlayer.ShowMovie("Matrix");

	cdPlayer.setDisplay(projector);
	cdPlayer.ShowMovie("Red hot");

	vhdPlayer.setDisplay(projector);
	vhdPlayer.ShowMovie("Matrix II");
}

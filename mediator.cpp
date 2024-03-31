#include "mediator.h"

#include <iostream>
#include <string>

class IDevice;

class IConnection {
public:
	virtual void sendSignal(IDevice & device, int signal) = 0;
};

class IDevice {
protected:
	IConnection* connection = nullptr;
public:	
	void setConnection(IConnection* conn) {
		connection = conn;
	}	
	virtual void Send(int signal) = 0;
	virtual void Receive(int signal) = 0;
};

class Device : public IDevice {
	const std::string name;
public:
	Device(const std::string & n) : name(n) {}
	void Send(int signal) override {
		if (connection) {
			connection->sendSignal(*this, signal);
		}
	}

	void Receive(int signal) override {
		std::cout << name << " receive signal " << signal << "\n";
	}
};

class Connection : public IConnection {
	IDevice * firstDevice = nullptr;
	IDevice * secondDevice = nullptr;
public:
	void setDevices(IDevice* fD, IDevice* sD) {
		firstDevice = fD;
		secondDevice = sD;
		firstDevice->setConnection(this);
		secondDevice->setConnection(this);
	}

	void sendSignal(IDevice& device, int signal) override {
		if (&device == firstDevice) {
			secondDevice->Receive(signal);
		}
		else if (&device == secondDevice) {
			firstDevice->Receive(signal);
		}
	}
};

void testMediator() {
	Device device1("Device1");
	Device device2("Device2");

	Connection conn;
	conn.setDevices(&device1, &device2);
	
	device1.Send(3);
	device2.Send(4);
	device1.Send(0);
}

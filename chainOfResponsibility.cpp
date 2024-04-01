#include "chainOfResponsibility.h"

#include <iostream>
#include <string>
#include <vector>

class Event {
	friend class Handler;
	unsigned code;
	std::string description;
	bool processed = false;
public:
	Event(unsigned c, const std::string & d) : code(c), description(d) {}
	void setProcessed() {
		processed = true;
	}
	bool isProcessed() const {
		return processed;
	}
};

class Handler {
protected:	
	Handler* next = nullptr;
	unsigned getEventCode(const Event & evt) const {
		return evt.code;
	}
	std::string getEventDescription(const Event& evt) const {
		return evt.description;
	}
public:
	virtual void handleEvent(Event& evt) {
		if (next) {
			next->handleEvent(evt);
		}
		else if(evt.isProcessed() == false) {
			std::cout << "There is no handler for " << evt.description << "\n";
		}
	}
	Handler* setNext(Handler * h) {
		next = h;
		return h;
	}
	virtual ~Handler() {}
};

class HandlerA : public Handler {
public:
	void handleEvent(Event& evt) {
		if (Handler::getEventCode(evt) & 0xe) {
			std::cout << "Reaction to an " << Handler::getEventDescription(evt) << " in the handlerA" << "\n";
			evt.setProcessed();
		}
		else {
			Handler::handleEvent(evt);
		}
	};
};

class HandlerB : public Handler {
public:
	void handleEvent(Event& evt) {
		if (Handler::getEventCode(evt) < 5) {
			std::cout << "Reaction to an " << Handler::getEventDescription(evt) << " in the handlerB" << "\n";
			evt.setProcessed();
		}
		
		Handler::handleEvent(evt);		
	};
};

class HandlerC : public Handler {
public:
	void handleEvent(Event& evt) {
		if (Handler::getEventCode(evt) == 0x11) {
			std::cout << "Reaction to an " << Handler::getEventDescription(evt) << " in the handlerC" << "\n";
			evt.setProcessed();
		}
		else {
			Handler::handleEvent(evt);
		}
	};
};

void testChainOfResponsibility() {
	HandlerA handlerA;
	HandlerB handlerB;
	HandlerC handlerC;

	handlerA.setNext(&handlerB)->setNext(&handlerC);

	std::vector<Event> events;

	events.push_back({ 0x0, "Task-A" });
	events.push_back({ 0x10, "Task-B" });
	events.push_back({ 0x11, "Task-C" });
	events.push_back({ 0x12, "Task-D" });

	for (auto& evt : events) {
		handlerA.handleEvent(evt);
		std::cout << "\n";
	}	
}

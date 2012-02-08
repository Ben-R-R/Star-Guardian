#ifndef EVENT_H
#define EVENT_H

class EventListener{
public:
	virtual void doEvent(int eventNumber) = 0;
};

#endif
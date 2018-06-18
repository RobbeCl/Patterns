/**
 * @file
 * Implementation of unit tests for observer pattern.
 */

#include "gtest/gtest.h"

#include "Subject.h"

class EventObserver{
public:
	virtual void event1(){};
	virtual void event2(int a, const std::string &b)=0;
};

class MySubject: public Subject<EventObserver>{
public:
	void fireEvent1(){notify(&EventObserver::event1);}
	void fireEvent2(){notify(&EventObserver::event2, 42, "test");}
};

class MyObserver: public EventObserver{
public:
	bool event1Fired = false;
	bool event2Fired = false;

	virtual void event1() override{
		event1Fired = true;
	}

	virtual void event2(int a, const std::string &b) override{
		ASSERT_EQ(a, 42);
		ASSERT_EQ(b, "test");
		event2Fired = true;
	}
};

// Test if message is received.
TEST(OBS_Subject, test){
	MySubject subject;
	std::shared_ptr<MyObserver> observer = std::make_shared<MyObserver>();
	subject.registerObserver(observer);

	ASSERT_FALSE(observer->event1Fired);
	ASSERT_FALSE(observer->event2Fired);

	subject.fireEvent1();
	ASSERT_TRUE(observer->event1Fired);
	ASSERT_FALSE(observer->event2Fired);

	subject.fireEvent2();
	ASSERT_TRUE(observer->event1Fired);
	ASSERT_TRUE(observer->event2Fired);
}

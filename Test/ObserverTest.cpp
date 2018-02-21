/**
 * @file
 * Implementation of unit tests for observer pattern.
 */

#include "gtest/gtest.h"

#include "Subject.h"

class Topic{
public:
	virtual void func1(){};
	virtual void func2(int a, const std::string& b)=0;
};

class ActualSubject: public Subject<Topic>{
public:
	void callFunc1(){notify(&Topic::func1);}
	void callFunc2(){notify(&Topic::func2, 42, "test");}
};

class Observer: public Topic{
public:
	bool func1Called = false;
	bool func2Called = false;

	virtual void func1(){;
		func1Called = true;
	}

	virtual void func2(int a, const std::string& b){
		ASSERT_EQ(a, 42);
		ASSERT_EQ(b, "test");
		func2Called = true;
	}
};

// Test if message is received.
TEST(OBS_Subject, test){
	ActualSubject subject;
	std::shared_ptr<Observer> observer = std::make_shared<Observer>();
	subject.registerObserver(observer);

	ASSERT_FALSE(observer->func1Called);
	ASSERT_FALSE(observer->func2Called);

	subject.callFunc1();
	ASSERT_TRUE(observer->func1Called);
	ASSERT_FALSE(observer->func2Called);

	subject.callFunc2();
	ASSERT_TRUE(observer->func1Called);
	ASSERT_TRUE(observer->func2Called);
}

/*
 *  This is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *  The software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License
 *  along with the software. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2017, Willem L, Kuylen E, Stijven S & Broeckhove J
 */

/**
 * @file
 * Implementation of unit tests for observer pattern.
 */

#include "gtest/gtest.h"

#include "Subject.h"

class Topic{
public:
	virtual ~Topic() = default;

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

	virtual ~Observer(){}

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

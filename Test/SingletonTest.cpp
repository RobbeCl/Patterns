/**
 * @file
 * Implementation of unit tests for singleton pattern.
 */

#include "gtest/gtest.h"

#include "Singleton.h"


class MySingleton: public Singleton<MySingleton>{
protected:
    MySingleton() = default;        // make it so no objects can be constructed from the outside.
public:
    int a = 3;

    bool operator==(const MySingleton& other) const{
        return a == other.a;
    }
};

// Test if exactly one valid instance.
TEST(Singleton, one_valid){
    MySingleton& instance1 = MySingleton::getInstance();
    MySingleton& instance2 = MySingleton::getInstance();

    ASSERT_EQ(instance1, instance2);
    ASSERT_EQ(&instance1, &instance2);

    instance1.a = 5;

    ASSERT_EQ(instance1, instance2);
    ASSERT_EQ(&instance1, &instance2);

    instance1 = instance2;

    ASSERT_EQ(instance1, instance2);
    ASSERT_EQ(&instance1, &instance2);
}

// Test if extra instances can be made. These statements should fail
//MySingleton instance1 = MySingleton::getInstance();     // copy
//MySingleton instance2;                                  // construct

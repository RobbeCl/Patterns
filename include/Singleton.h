#ifndef PATTERNS_SINGLETON_H
#define PATTERNS_SINGLETON_H

/**
 * @file Implementation of Singleton pattern.
 */

template <class T>
class Singleton {
private:
    class A: public T{
    public:
        A() = default;
    };

public:
    Singleton() = default;
    Singleton(Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&) = default;
    Singleton& operator=(Singleton&&) = default;

    static T& getInstance(){
        static A instance;
        return instance;
    }
};


#endif //PATTERNS_SINGLETON_H

#ifndef PATTERNS_SUBJECT_H
#define PATTERNS_SUBJECT_H

/**
 * @file Implementation of Subject for observer pattern.
 */

#include <functional>
#include <map>
#include <memory>

/**
 * @brief A subject can be observed by subclasses of the Observer interface. Subjects call specific methods of the Observer interface you can subscribe to.
 */
template <class Observer>
class Subject {
private:
	/// Observers should stay alive as long as what they watch is alive. Hence shared_ptr.
	mutable std::vector<std::shared_ptr<Observer> > observers;

protected:

	/**
	 * Implementation for std::function.
	 * @brief Calls the func on all observers.
	 * @param func: Function to call.
	 * @param args: Args of the function.
	 */
	template <typename ... Args1, typename ... Args2>
	void notify(std::function<void (Observer&, Args1...)> func, Args2... args);

	/**
	 * Implementation for function pointer.
	 * @brief Calls the func on all observers.
	 * @param func: Function to call.
	 * @param args: Args of the function.
	 */
	template <typename ... Args1, typename ... Args2>
	void notify(void (Observer::*f)(Args1...), Args2&&... args);

public:

	///@param obs: Observer to register.
	void registerObserver(std::shared_ptr<Observer> obs) const;

	/// @param obs: Observer to remove from the observers list.
	void unregisterObserver(std::shared_ptr<Observer> obs);

	/// Remove all observers.
	void unregisterAll();

	virtual ~Subject(){}
};

// implementation

template <class Observer>
void Subject<Observer>::registerObserver(std::shared_ptr<Observer> obs) const{
	observers.push_back(obs);
}

template <class Observer>
void Subject<Observer>::unregisterObserver(std::shared_ptr<Observer> obs) {
	typename std::vector<Observer*>::iterator it = std::find(observers.begin(), observers.end(), obs);
	if(it != observers.end()){
		observers.erase(it);
	}else{
		std::cerr << "Tried to remove an observer that wasn't registered." << std::endl;
	}
}

template<class Observer>
void Subject<Observer>::unregisterAll() {
	observers.clear();
}

// std::function
template <class Observer>
template <typename ... Args1, typename ... Args2>
void Subject<Observer>::notify(std::function<void (Observer&, Args1...)> func, Args2... args){
	for(std::shared_ptr<Observer> obs : observers){
		func(*obs, std::forward<Args2>(args)...);
	}
}

// function pointer
template <class Observer>
template <typename ... Args1, typename ... Args2>
void Subject<Observer>::notify(void (Observer::*f)(Args1...), Args2&&... args){
	std::function<void (Observer&, Args1...)> func = f;
	for(std::shared_ptr<Observer> obs : observers){
		func(*obs, std::forward<Args2>(args)...);
	}
}

#endif // PATTERNS_SUBJECT_H

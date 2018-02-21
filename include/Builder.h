#ifndef PATTERNS_BUILDER_H
#define PATTERNS_BUILDER_H

/**
 * @file Implementation of Builder for builder pattern.
 */


#include <memory>

/**
 * @brief A builder interface for a specific class
 */
template <class Result, class Data>
class Builder: protected Data {
public:
    virtual Result getResult(){
        assert(isValid());
        return Result((Data)*this);
    }

    virtual std::shared_ptr<Result> getResultNew(){
        assert(isValid());
        return std::make_shared<Result>((Data)*this);
    };

    virtual bool isValid(){return true;}
};

#endif //PATTERNS_BUILDER_H

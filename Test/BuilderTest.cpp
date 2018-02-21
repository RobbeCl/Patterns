/**
 * @file
 * Implementation of unit tests for observer pattern.
 */

#include "gtest/gtest.h"

#include "Builder.h"

struct CarData{
protected:
    int numSeats = 4;
    bool GPS = false;

public:
    virtual bool operator==(const CarData& other) const{return numSeats == other.numSeats && GPS == other.GPS;}
};

class Car: public CarData{
public:
	explicit Car(const CarData& data):CarData(data){}

    int getNumSeats() const{return numSeats;}
    bool hasGPS() const{return GPS;}
};

class CarBuilder: public Builder<Car, CarData>{
public:
    void setNumSeats(int numSeats){
        this->numSeats = numSeats;
    }

    void setGPS(bool GPS){
        this->GPS = GPS;
    }

    virtual bool isValid() override{
        return numSeats < 8;
    }
};

// Test builder methods
TEST(Builder, test){
	CarBuilder builder;
    builder.setNumSeats(5);
    builder.setGPS(true);

    ASSERT_TRUE(builder.isValid());

    builder.setNumSeats(100);
    ASSERT_DEATH(builder.getResult(), "Assertion .* failed.");

    builder.setNumSeats(5);
    Car car = builder.getResult();
    std::shared_ptr<Car> car_p = builder.getResultNew();

    ASSERT_EQ(car.getNumSeats(), 5);
    ASSERT_EQ(car.hasGPS(), true);
    ASSERT_EQ(car, *car_p);
}

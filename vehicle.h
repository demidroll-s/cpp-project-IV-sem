#include <iostream>
#include <string.h>

using namespace std;

enum veh_size {mini = 1, small = 2, midsize = 3, large = 4};
enum veh_type {two_door = 1, four_door = 2, luxury = 3, sportcar = 4, van = 5};

class Vehicle
{
protected:
    std::string model;
    veh_size size;
    veh_type type;
    double collision;
    double property_damage;
    double comprehensive;
    double personal_injury;
    double medical_payment;
    double bodily_injury;
public:
    Vehicle(std::string model, double collision, double property_damage, double comprehensive, double personal_injury, double medical_payment, double bodily_injury)
    {
        this->model = model;
        this->collision = collision;
        this->property_damage = property_damage;
        this->comprehensive = comprehensive;
        this->personal_injury = personal_injury;
        this->medical_payment = medical_payment;
        this->bodily_injury = bodily_injury;
    };
};
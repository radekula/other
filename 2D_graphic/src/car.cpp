#include <cstdlib>
#include <iostream>
#include "car.hpp"



Car::Car(int car_id)
{
    id = car_id;
    pos_x = -1;
}




Car::~Car()
{
};




void Car::drive(std::vector<std::shared_ptr<Car>> &all_cars)
{
    if(pos_x >= 0 && pos_x <= 24)
    {
        for(auto car : all_cars)
        {
            if(car->get_id() == id)
                continue;

            if(car->get_direction() != direction)
                continue;

            auto car_pos_x = car->get_pos_x();
            auto car_pos_y = car->get_pos_x();

            auto distance = std::abs(pos_x - car_pos_x);
            auto in_front = direction == 1 ? car_pos_x < pos_x : car_pos_x > pos_x;
            
            if(!in_front)
                continue;

            if(std::abs(car_pos_y) < 0.6 && std::abs(pos_y) > 0.6)
                continue;
            
            if(distance < 1)
            {
                if(car->get_curr_speed() < curr_speed)
                    acceleration -= 0.5;
                else
                    acceleration = 0;

                break;
            }
        };


        if(acceleration < -10)
            acceleration = -10;

        if(acceleration > 10)
            acceleration = 10;

        curr_speed += acceleration;
        if(curr_speed >= max_speed)
        {
            curr_speed = max_speed;
            acceleration = 0;
        }

        pos_x += ((-direction * curr_speed) / 2400.0);
    }
    else
    {
        type = rand() % 5;
        direction = rand() % 2 ? 1 : -1;

        pos_x = direction == 1 ? 24 : 0;
        pos_y = direction == 1 ? -0.3 : 0.3;

        curr_speed = max_speed = rand() % 50 + 100;
        acceleration = 0;

        for(auto car : all_cars)
        {
            if(car->get_id() == id)
                continue;

            auto pos = car->get_pos_x();
            if(pos < 0 || pos > 24)
                continue;

            if((direction == 1 && pos >= 23) || (direction == -1 && pos <= 1))
            {
                pos_x = -1;
                break;
            }
        }
    }
};




int Car::get_direction()
{
    return direction;
};




int Car::get_id()
{
    return id;
};




int Car::get_type()
{
    return type;
};




float Car::get_pos_x()
{
    return pos_x;
};




float Car::get_pos_y()
{
    return pos_y;
};




float Car::get_curr_speed()
{
    return curr_speed;
};

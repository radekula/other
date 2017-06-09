#include <cstdlib>
#include <iostream>
#include <cmath>
#include "car.hpp"



Car::Car(int car_id)
{
    id = car_id;
    pos_x = -1;
}




Car::~Car()
{
};



void Car::look_around(std::vector<std::shared_ptr<Car>> &all_cars)
{
    car_in_front = false;
    in_fast_line = false;
    can_accelerate = true;
    need_breaking = false;
    can_change_line = true;
    
    for(auto car : all_cars)
    {
        // check if car is active
        if(car->get_pos_x() < 0)
            continue;

        // check if car is driving in same way
        if(car->get_direction() != direction)
            continue;
        
        auto car_pos_x = car->get_pos_x();
        auto car_pos_y = car->get_pos_y();

        // check if i'm in fast line
        if(std::fabs(pos_y) > 0.65)
            in_fast_line = true;

        auto in_front = direction == 1 ? pos_x > car_pos_x : pos_x < car_pos_x;
        auto distance = std::fabs(pos_x - car_pos_x);
        auto line_distance = std::fabs(pos_y - car_pos_y);
        auto same_line = line_distance < 0.35;
        auto different_line = line_distance > 0.35;

        // check if car is in front of me
        if(in_front && distance < 1.4 && same_line)
            car_in_front = true;

        // check if i need to brake
        if(car_in_front && car->get_curr_speed() < curr_speed)
            need_breaking = true;

        // check if i can accelerate
        if(car_in_front && car->get_curr_speed() <= curr_speed && curr_speed < max_speed)
            can_accelerate = false;

        // check if I can change line
        if(different_line && distance < 1.5)
            can_change_line = false;
    };
};





void Car::drive(std::vector<std::shared_ptr<Car>> &all_cars)
{
    if(pos_x >= 0 && pos_x <= 25)
    {
        look_around(all_cars);

        // car in front and need breaking
        if(car_in_front && need_breaking)
        {
            // can I change line?
            if(can_change_line)
                // yes - change line
                acceleration_y = 0.01;

            acceleration -= 0.05;
        };

        // don't need to brake anymore
        if(!need_breaking && acceleration < 0)
            acceleration = 0;

        // can I accelerate?
        if(can_accelerate)
            acceleration += 0.01;

        // if I'm in fast line can I change to slow line?
        if(in_fast_line && can_change_line && !acceleration_y)
            acceleration_y = -0.01;

        // stay in lines
        if(direction == -1)
        {
            if(pos_y > 1)
            {
                pos_y = 1;
                acceleration_y = 0;
            }

            if(pos_y < 0.3)
            {
                pos_y = 0.3;
                acceleration_y = 0;
            }
        }
        else
        {
            if(pos_y < -1)
            {
                pos_y = -1;
                acceleration_y = 0;
            }

            if(pos_y > -0.3)
            {
                pos_y = -0.3;
                acceleration_y = 0;
            }
        };

        // check if I not breaking or accelerating to quick
        if(acceleration < -10)
            acceleration = -10;

        if(acceleration > 5)
            acceleration = 5;

        curr_speed += acceleration;
        if(curr_speed >= max_speed)
        {
            curr_speed = max_speed;
            acceleration = 0;
        }
        
        if(curr_speed < 100)
            curr_speed = 100;

        pos_x += ((-direction * curr_speed) / 2400.0);
        auto change_y = acceleration_y * (curr_speed / 140);
        pos_y = pos_y > 0 ? pos_y + change_y : pos_y - change_y;
    }
    else
    {
        type = 4;
        direction = rand() % 2 ? 1 : -1;

        pos_x = direction == 1 ? 25 : 0;
        pos_y = direction == 1 ? -0.3 : 0.3;

        curr_speed = max_speed = rand() % 50 + 100;
        acceleration = 0;
        acceleration_y = 0;

        for(auto car : all_cars)
        {
            if(car->get_id() == id)
                continue;

            auto pos = car->get_pos_x();
            if(pos < 0)
                continue;

            if((direction == 1 && pos >= 23.5) || (direction == -1 && pos <= 1.5))
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

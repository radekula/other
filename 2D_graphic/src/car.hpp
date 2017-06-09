#ifndef __CAR_HPP__
#define __CAR_HPP__


#include <vector>
#include <memory>



class Car
{
private:
    int id;
    int type;
    float max_speed;
    float curr_speed;
    float acceleration;
    float acceleration_y;
    float car_in_front_speed_delta;

    float pos_x;
    float pos_y;
    int direction;

private:
    bool car_in_front;
    bool in_fast_line;
    bool can_accelerate;
    bool need_breaking;
    bool can_change_line;
    

private:
    void look_around(std::vector<std::shared_ptr<Car>> &all_cars);

public:
    Car(int car_id);
    ~Car();

public:
    void drive(std::vector<std::shared_ptr<Car>> &all_cars);

public:
    int get_id();
    int get_type();
    int get_direction();

    float get_pos_x();
    float get_pos_y();

    float get_curr_speed();
    float get_rotation();
};



#endif

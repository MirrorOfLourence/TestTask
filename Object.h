#pragma once
#include <iostream>
#include "Point.h"

class Object
{
public:
    Object();
    Object(std::string name, float x, float y, std::string type);

    bool compareByDistance(Object i, Object j);
    float getDistanceFromOrigin();
    void print(std::ofstream &out);
private:
    std::string m_name;
    std::string m_type;
    Point m_coordinates;
    time_t m_timeOfCreating;
    float m_distanceFromOrigin;
};


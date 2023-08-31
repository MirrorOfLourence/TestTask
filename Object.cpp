#include <fstream>
#include "Object.h"

Object::Object()
    :m_name(""), m_coordinates(0, 0), m_type(""), m_timeOfCreating(0), m_distanceFromOrigin(0)
{
};

Object::Object(std::string name, float x, float y, std::string type)
    :m_name(name), m_coordinates(x,y), m_type(type)
{
    time_t timeOfCreating;
    m_timeOfCreating = time(&timeOfCreating);
    m_distanceFromOrigin = m_coordinates.getDistanceFromOrigin();
};

bool Object::compareByDistance(Object i, Object j) 
{ 
    return (i.m_distanceFromOrigin < j.m_distanceFromOrigin);
}

float Object::getDistanceFromOrigin()
{
    return m_distanceFromOrigin;
}

void Object::print(std::ofstream& out)
{
    if (out.is_open())
        out << m_name << "\t" << m_distanceFromOrigin << "\t" << m_type << "\n";
    else
        return;
}

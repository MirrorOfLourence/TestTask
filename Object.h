#pragma once
#include <iostream>
#include <string>
#include "Point.h"

class Object
{
public:
    Object();
    Object(std::string name, long double x, long double y, std::string type);
    Object(const std::string& line);

    long double getDistanceFromOrigin();
    std::string getFieldFromLine(const std::string& line, size_t& posOfSpace);
    std::string getName();
    std::string getType();
    long double  getTimeOfCreation();

    bool checkIfValid();
    void print(std::ofstream &fout);
private:
    std::string m_name;
    std::string m_type;
    Point m_coordinates;
    long double m_timeOfCreation;
    long double m_distanceFromOrigin;
    bool m_isValid;
};


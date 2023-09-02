#include <fstream>
#include <iomanip>
#include "Object.h"

Object::Object()
    :m_name(""), m_coordinates(0, 0), m_type(""), m_timeOfCreation(0), m_distanceFromOrigin(0), m_isValid(true)
{
};

Object::Object(std::string name, long double x, long double y, std::string type)
    :m_name(name), m_coordinates(x,y), m_type(type), m_isValid(true)
{
    m_distanceFromOrigin = m_coordinates.getDistanceFromOrigin();
	time_t timeOfCreation;
	time(&timeOfCreation);
	m_timeOfCreation = (long double)timeOfCreation;
}

Object::Object(const std::string& line)
{
	m_isValid = false;
	size_t posOfSpace = line.find(' ');
	m_name = (posOfSpace != std::string::npos) ? line.substr(0, posOfSpace) : "";
	if (m_name != "")
	{
		std::string xCoord = getFieldFromLine(line, posOfSpace);
		if (xCoord != "")
		{
			std::string yCoord = getFieldFromLine(line, posOfSpace);
			if (yCoord != "")
			{
				m_type = getFieldFromLine(line, posOfSpace);
				if (m_type != "")
				{
					std::string timeOfCreation = getFieldFromLine(line, posOfSpace);
					if(timeOfCreation != "")
					{
						m_coordinates = Point(std::stold(xCoord), std::stold(yCoord));
						m_timeOfCreation = std::stold(timeOfCreation);
						m_distanceFromOrigin = m_coordinates.getDistanceFromOrigin();
						m_isValid = true;
					}
				}
			}	
		}
	}
}

long double Object::getDistanceFromOrigin()
{
    return m_distanceFromOrigin;
}

std::string Object::getFieldFromLine(const std::string& line, size_t& posOfSpace)
{
	posOfSpace++;
	size_t temp = line.find(' ', posOfSpace);
	std::string result;
	if(temp != std::string::npos)
		result = line.substr(posOfSpace, temp-posOfSpace);
	else
	{
		temp = line.length() - 1;
		result = (posOfSpace > temp) ? "" : line.substr(posOfSpace, temp);
	}
	posOfSpace = temp;
	return result;
}

std::string Object::getName()
{
    return m_name;
}

std::string Object::getType()
{
    return m_type;
}

long double  Object::getTimeOfCreation()
{
    return m_timeOfCreation;
}

bool Object::checkIfValid()
{
	return m_isValid;
}

void Object::print(std::ofstream& fout)
{
    if (fout.is_open())
	{
		fout << std::setw(15) << m_name << "\t" << std::setw(15) << m_type << "\t"
		<< std::setw(15) << round(m_distanceFromOrigin*1000)/1000 << "\t"
		<< std::setw(20) << std::setprecision(15) << round(m_timeOfCreation*1000)/1000 << std::endl;
	}
    else
        return;
}

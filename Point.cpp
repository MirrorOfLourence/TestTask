#include "Point.h"
#include <cmath>

long double Point::getDistanceFromOrigin()
{
    return sqrt(m_x*m_x + m_y*m_y);
}

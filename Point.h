#pragma once
class Point
{
public:
    Point()
        :m_x(0.f), m_y(0.f)
    {
    };
    Point(long double x, long double y)
        :m_x(x), m_y(y)
    {
    };
    long double getDistanceFromOrigin();
private:
    long double m_x;
    long double m_y;
};



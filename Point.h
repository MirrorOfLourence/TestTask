#pragma once
class Point
{
public:
    Point()
        :m_x(0.f), m_y(0.f)
    {
    };
    Point(float x, float y)
        :m_x(x), m_y(y)
    {
    };
    float getDistanceFromOrigin();
private:
    float m_x;
    float m_y;
};



/* Module: point / File: point.cpp
 * Includes the execution of the functionality of a point.
 */

#include "point.hh"

Point::Point(std::string name, int x, int y, int height, char marker)
{
    name_ = name;
    x_ = x;
    y_ = y;
    height_ = height;
    marker_ = marker;
}

Point::~Point()
{

}

char Point::get_marker() const
{
    return marker_;
}

std::string Point::get_name() const
{
    return name_;
}

int Point::get_x() const
{
    return x_ - 1;
}

int Point::get_y() const
{
    return y_ - 1;
}

int Point::get_height() const
{
    return height_;
}

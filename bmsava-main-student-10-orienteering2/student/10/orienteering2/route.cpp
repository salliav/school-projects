/* Module: route / File: route.cpp
 * Includes the execution of the functionality of a route.
 */

#include "route.hh"
#include "point.hh"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>



Route::Route(std::string route_name)
{
    route_name_ = route_name;
}

Route::~Route()
{

}

bool Route::add_point_to_route(Point* from, Point* to)
{
    if (points.empty()) {
        points.push_back(from);
        points.push_back(to);
        return true;
    } else if (points.back() == from) {
        points.push_back(to);
        return true;
    } else {
       return false;
    }
}

void Route::print() const
{
    if (!points.empty()) {
        std::cout << points.at(0)->get_name() << std::endl;
    }
    if (!points.empty() and points.size() > 1) {
        for (uint i = 1; i < points.size(); i++) {
          std::cout << " -> " << points.at(i)->get_name() << std::endl;
        }
    }
    return;
}

double Route::calculate_length()
{
    double final_result = 0.0;
    for (uint i= 0; i < points.size()-1; i++) {
        double x1 = 0;
        double y1 = 0;
        double x2 = 0;
        double y2 = 0;
        x1 = points.at(i)->get_x();
        y1 = points.at(i)->get_y();
        x2 = points.at(i + 1)->get_x();
        y2 = points.at(i + 1)->get_y();

        double part_result = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
        final_result += part_result;
    }
    return final_result;
}

bool Route::find_point(Point* current_point) const
{
    for (auto& point : points) {
        if (point == current_point) {
            return true;
        }
    }
    return false;
}

int Route::calculate_rise(Point* current_point)
{
    // Searches where the point locates on the route.
    uint place = 0;
    for (uint i = 0; i < points.size(); i++) {
        if (current_point == points.at(i)) {
            place = i;
        }
    }

    int rise = 0;
    for (uint i = place; i < points.size()-1; i++) {
        int point1 = points.at(i)->get_height();
        int point2 = points.at(i+1)-> get_height();
        if (point2 >= point1) {
           rise += (point2 - point1);
        } else {
            break;
        }
    }
    return rise;
}


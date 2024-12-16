/* Module: orienteeringmap / File: orienteeringmap.cpp
 * Includes the execution of the functionality of the
 * orienteeringmap.
 */

#include "orienteeringmap.hh"
#include "point.hh"
#include "route.hh"
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>


OrienteeringMap::OrienteeringMap()
{

}

OrienteeringMap::~OrienteeringMap() // Annetaanko mapit parametrina? Ei saanu muuttaa?
{
    for (auto& data_unit : all_points){
        delete data_unit.second;
        data_unit.second = nullptr;
    }

    for (auto& data : all_routes){
        delete data.second;
        data.second = nullptr;
    }
}

void OrienteeringMap::set_map_size(int width, int height)
{
    height_ = height;
    width_ = width;
}

void OrienteeringMap::add_point(std::string name,int x, int y,
                                int height, char marker)
{
    if (all_points.find(name) == all_points.end()) {
            Point* new_point = new Point(name, x, y, height, marker);
            all_points.insert({name, new_point});
    } else {
        return;
    }
}

bool OrienteeringMap::connect_route(std::string from,
                                    std::string to,
                                    std::string route_name)
{
    // Checks if the given points exist on the orienteeringmap.
    if (all_points.find(from) == all_points.end() or
         all_points.find(to) == all_points.end()) {
        return false;
    }

    // Adds a new route into the all_routes library.
    if (all_routes.find(route_name) == all_routes.end()) {
        Route* new_route = new Route(route_name);
        all_routes.insert({route_name, new_route});
    }

    Point* from_point = nullptr;
    Point* to_point = nullptr;
    for (auto& point : all_points) {
        if (from == point.first){
           from_point = point.second;
        }
        if (to == point.first){
           to_point = point.second;
        }
    }
    if (!all_routes.at(route_name)->
            add_point_to_route(from_point, to_point)) {
        return false;
    }
    return true;
}

void OrienteeringMap::print_map() const
{
    std::cout << " ";
    for(int x = 1; x <= width_; ++x)
    {
        std::cout << std::setw(3);
        std::cout << x;
    }
    std::cout << std::endl;


    for(int y = 0; y < height_; ++y) {
        std::cout << std::setw(2);
        std::cout << y+1;
        for(int x = 0; x < width_; ++x) {
            bool point_found = false;
            for (auto& point : all_points) {
                if (x == point.second ->get_x() and
                     y == point.second->get_y()) {
                    point_found = true;
                    std::cout << std::setw(3);
                    std::cout << point.second->get_marker();
                }
             }
             if (!point_found){
                std::cout << std::setw(3);
                std::cout << ".";
             }
         }
         std::cout << std::endl;
    }
}

void OrienteeringMap::print_routes() const
{
    std::cout << "Routes: " << std::endl;
    for (auto& route_name : all_routes) {
        std::cout << " - " << route_name.first << std::endl;
    }
    return;
}

void OrienteeringMap::print_points() const
{
    std::cout << "Points:" << std::endl;
    for (auto& data_unit : all_points){
        std::cout << " - " << data_unit.first << " : ";
        std::cout << data_unit.second->get_marker() << std::endl;
    }
}

void OrienteeringMap::print_route(const std::string &name) const
{
    if (all_routes.find(name) == all_routes.end()) {
        std::cout << "Error: Route named " << name << " can't be found" << std::endl;
        return;
    }
    all_routes.at(name)->print();
}

void OrienteeringMap::route_length(const std::string &name) const
{
    if (all_routes.find(name) == all_routes.end()) {
        std::cout << "Error: Route named " << name << " can't be found" << std::endl;
        return;
    }
    std::cout << "Route " << name << " length was ";
    std::cout << std::setprecision(2);
    std::cout << all_routes.at(name)->calculate_length() << std::endl;
    return;
}

void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    // Checks if the given point exists on the orienteeringmap.
    Point* current_point = nullptr;
    for (auto& point : all_points) {
        if (point_name == point.first) {
            current_point = point.second;
            break;
        }
    }
    if (current_point == nullptr) {
        std::cout << "Error: Point named " << point_name;
        std::cout << " can't be found" << std::endl;
        return;
    }

    // Creates a helper vector to collect the imformation about
    // rises and the names of the routes where the given points exists.
    std::vector<std::pair<int, std::string>> helper;
    for (auto& route : all_routes) {
        if (route.second->find_point(current_point)) {
            helper.push_back(std::make_pair(
                route.second->calculate_rise(current_point),
                route.first));
        }
    }

    std::sort(helper.begin(), helper.end());

    int greatest = helper.back().first;
    if (greatest == 0) {
        std::cout << "No route rises after point " << point_name << std::endl;
    } else {
        std::cout << "Greatest rise after point " << point_name;
        std::cout << ", " << greatest << " meters, is on route(s):" << std::endl;
        for (auto& pair : helper) {
            if (pair.first == greatest) {
                std::cout << " - " << pair.second << std::endl;
            }
        }
    }
    return;
}

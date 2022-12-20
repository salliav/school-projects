/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project3: Suunnistus / Orienteering                                       #
#                                                                           #
# Module: orienteeringmap / File: orienteerinmap.hh                         #
#                                                                           #
# Description: Datastructure that represents an orienteering map and        #
#        handles information of points and routes. The program reads the    #
#        information from a given file into the datastucture and after that #
#        it is possible to make searches for point and route data, for      #
#        example examine the length of a given route. The program also      #
#        performs the points' locations on the orienteering map.            #
# Notes:  The data file's lines should be in designated format: The first   #
#     line defines the width and height of the orienteerin map. The next    #
#     lines include infromation of each point, in format: Point name;x-     #
#     coordinate;y-coordinate;rise of the ground on that point in numbers;  #
#     marker with one letter. The file must include definition "ROUTES".    #
#     Lines after that include information of each route, in format: Route  #
#     name; and after that point names on that route, separated with        #
#     ";" -marks. The program execution terminates instantly if the file    #
#     contains incorrect lines.                                             #
# Program author:  Name: Salli Valkama                                      #
#                  Student number:  150427834                               #
#                  UserID: bmsava                                           #
#                  E-Mail: salli.valkama@tuni.fi                            #
#############################################################################
*/

#ifndef ORIENTEERINGMAP_HH
#define ORIENTEERINGMAP_HH

#include "point.hh"
#include "route.hh"
#include <string>
#include <map>


class OrienteeringMap
{
public:
    // Constructor and destructor
    OrienteeringMap();
    ~OrienteeringMap();

    // Sets the width and height for the map.
    void set_map_size(int width, int height);

    // Adds a new point in the map, with the given name, position (x and y
    // coordinates), height and marker.
    void add_point(std::string name, int x, int y, int height, char marker);

    // Connects two existing points such that the point 'to' will be
    // immediately after the point 'from' in the route 'route_name'.
    // The given route can be either a new or an existing one,
    // if it already exists, the connection between points will be
    // updated in the aforementioned way.
    // Returns true, if connection was successful, i.e. if both the points
    // exist, otherwise returns false.
    bool connect_route(std::string from,
                       std::string to,
                       std::string route_name);

    // Prints the map.
    void print_map() const;

    // Prints all routes' names, ordered alphabetically.
    void print_routes() const;

    // Prints all points' names and their markers on the map.
    void print_points() const;

    // Prints points belonging to the given route in the order they are
    // in the route.
    void print_route(const std::string& name) const;

    // Prints the given route's combined length,
    // the length is counted as a sum of the distances of adjacent points.
    void route_length(const std::string& name) const;

    // Finds and prints the highest rise in any of the routes after the given
    // point.
    void greatest_rise(const std::string& point_name) const;

private:
    // Attributes for map's width and height. Containers for point and
    // route libaries.
    int width_;
    int height_;
    std::map<std::string, Point*> all_points;
    std::map<std::string, Route*> all_routes;
};

#endif // ORIENTEERINGMAP_HH

/* Module: route / File: route.hh
 * Includes the data and functionality of a route.
 */

#ifndef ROUTE_HH
#define ROUTE_HH

#include "point.hh"
#include <string>
#include <vector>


class Route
{
public:

    // Constructor and destructor
    Route(std::string route_name);
    ~Route();

    // Adds a point to the route. Connects two points if point
    // "from" exists on that route. Takes two points as parameters
    // and returns true if the connection was successful. Returns
    // false if not.
    bool add_point_to_route(Point* to,
                            Point* from);

    // Prints the point names on that route, in order where the points
    // locate on that route.
    void print() const;

    // Calculates the length between points and returns the total
    // length of the route.
    double calculate_length();

    // Checks if a point exists on the route. Takes a point as
    // a parameter and return true if the point exists on the route,
    // false if not.
    bool find_point(Point* current_point) const;

    // Calculates the continuous rise after a point. Takes a point as
    // a parameter and returns the total rise. Returns zero if there was
    // no rise between the point and the next point.
    int calculate_rise(Point* current_point);

private:
    // A route has a name and points collected in a library.
    std::string route_name_;
    std::vector<Point*> points;
};

#endif // ROUTE_HH

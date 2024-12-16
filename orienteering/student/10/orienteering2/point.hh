/* Module: point / File: point.hh
 * Includes the data and functionality of a single
 * point on the orienteerin map.
 */

#ifndef POINT_HH
#define POINT_HH

#include <string>

class Point
{
public:
    // Constructor and destructor
    Point(std::string name, int x, int y, int height, char marker);
    ~Point();

    // Returns data about the point (marker, point's name, coordinates
    // and the height on that point.
    char get_marker() const;
    std::string get_name() const;
    int get_x() const;
    int get_y() const;
    int get_height() const;

private:
    // The point is defined by name, coordinates, height and marker.
    std::string name_;
    int x_;
    int y_;
    int height_;
    char marker_;
};

#endif // POINT_HH

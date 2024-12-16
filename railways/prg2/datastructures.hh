// Datastructures.hh
//
// Student name: Salli Valkama
// Student email: salli.valkama@tuni.fi
// Student number: 150427834

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <map>
#include <tuple>
#include <cmath>
#include <utility>
#include <limits>
#include <functional>
#include <exception>

// Types for IDs
using StationID = std::string;
using TrainID = std::string;
using RegionID = unsigned long long int;
using Name = std::string;
using Time = unsigned short int;

// Return values for cases where required thing was not found
StationID const NO_STATION = "---";
TrainID const NO_TRAIN = "---";
RegionID const NO_REGION = -1;
Name const NO_NAME = "!NO_NAME!";
Time const NO_TIME = 9999;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();


// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    //
    // Old assignment 1 operations
    //

    // Estimate of performance:
    // Short rationale for estimate:
    unsigned int station_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> all_stations();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_station_name(StationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance:
    // Short rationale for estimate:
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> all_regions();

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_region_name(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> station_in_regions(StationID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_station(StationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);

    //
    // New assignment 2 operations
    //

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Function iterates throug the data performing
    // linear operations in the loop
    bool add_train(TrainID trainid, std::vector<std::pair<StationID, Time>> stationtimes);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Function iterates through the data performing
    // constant time operations in the loop
    std::vector<StationID> next_stations_from(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Function iterates through the data performing
    // constant time operations in the loop
    std::vector<StationID> train_stations_from(StationID stationid, TrainID trainid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Function iterates over train and station data
    void clear_trains();

    // Estimate of performance: O(E+V)
    // Short rationale for estimate: Function is implemented as breath first search which is
    // will operate every edge and node in the worst case
    std::vector<std::pair<StationID, Distance>> route_any(StationID fromid, StationID toid);

    // Non-compulsory operations

    // Estimate of performance: O(E+V)
    // Short rationale for estimate: Function is implemented as breath first search which is
    // will operate every edge and node in the worst case
    std::vector<std::pair<StationID, Distance>> route_least_stations(StationID fromid, StationID toid);

    // Estimate of performance: O(E+V)
    // Short rationale for estimate: Function is implemented as depth first search which is
    // will operate every edge and node in the worst case
    std::vector<StationID> route_with_cycle(StationID fromid);

    // Estimate of performance: O(E+V log E)
    // Short rationale for estimate: Function is implemented with Dijkstra's algorithm which is
    // will operate every edge and node in the worst case
    std::vector<std::pair<StationID, Distance>> route_shortest_distance(StationID fromid, StationID toid);

    // Estimate of performance: O(E+V log E)
    // Short rationale for estimate: Function is implemented with Dijkstra's algorithm which is
    // will operate every edge and node in the worst case
    std::vector<std::pair<StationID, Time>> route_earliest_arrival(StationID fromid, StationID toid, Time starttime);

private:

    struct Region
    {
       RegionID id;
       std::string name;
       std::vector<Coord> coordinates;
       std::vector<Region*> children;
       Region* parent = nullptr;
    };

    struct Station
    {
        StationID id;
        std::string name;
        Coord coordinates;
        std::vector<std::pair<StationID, Station*>> next_stations = {};
        std::multimap<TrainID, Time> trains = {};
        Region* parent = nullptr;
        std::string color = "white";
        Distance distance = -1;
        Station* from = nullptr;
    };
    
    struct Train
    {
        TrainID id;
        std::vector<std::pair<StationID, Time>> stationtimes;    
    };

    // Datastructures for station, region land train libraries
    std::unordered_map<StationID, Station> stations;
    std::unordered_map<RegionID, Region> regions;
    std::unordered_map<TrainID, Train> trains;

    // Calcultaes distance between two stations based on their coordinates
    Distance calculate_distance(Coord s1, Coord s2)
    {
        int x = std::pow(s1.x - s2.x, 2);
        int y = std::pow(s1.y - s2.y, 2);
        return floor(sqrt(x+y));
    }

    // Comparison function for route_shortest_distance
    struct Compare {
        bool operator()(Station* const& s1, Station* const& s2)
        {
            return s1->distance > s2->distance;
        }
    };

    // Comparison function for route_shortest_distance
    void Relax(Station*& s1, Station*& s2)
    {
        Distance dist = calculate_distance(s1->coordinates, s2->coordinates);
        if (s2->distance == -1 or (s2->distance > (s1->distance + dist)))
        {
            s2->distance = (s1->distance + dist);
            s2->from = s1;
        }
    }

    // Functions for route_earliest_arrival
    /*void Relax_time(Station*& s1, Station*& s2, Time traveltime)
    {
        if (s2->time == 0 or s2->time > s1->time + traveltime)
        {
            s2->time = s1->time + traveltime;
            s2->from = s1;
        }
    }

    Time train_between(Station*& s1, Station*& s2)
    {
        Time traveltime = 0;
        for (auto i1 = s1->trains.begin(); i1 != s1->trains.end(); i1++)
        {
            for (auto i2 = s2->trains.begin(); i2 != s2->trains.end(); i2++)
            {
                if ((i1->first == i2->first)
                        and (i1->second >= s1->time) and (i2->second > s1->time))
                {
                   // s1->time = i1->second;
                    s2->time = i2->second;
                   // s2->from = s1;
                    traveltime = i2->second - i1->second;
                    return traveltime;
                }
            }
        }
        return traveltime;
    }

    struct Compare_times {
        bool operator()(Station* const& s1, Station* const& s2)
        {
            return s1->time > s2->time;
        }
    };
*/
};

#endif // DATASTRUCTURES_HH

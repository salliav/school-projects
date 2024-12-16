// Datastructures.cc
//
// Student name: Salli Valkama
// Student email: salli.valkama@tuni.fi
// Student number: 150427834

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::station_count()
{
    return stations.size();
}

void Datastructures::clear_all()
{
    stations.clear();
    regions.clear();
}

std::vector<StationID> Datastructures::all_stations()
{
    std::vector<StationID> station_ids;
    station_ids.reserve(stations.size());
    if (!stations.empty())
    {
        transform(stations.begin(), stations.end(),
                  back_inserter(station_ids),
                [](auto &elem){return elem.first;});
    }
    return station_ids;
}

bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    if (stations.find(id) != stations.end())
    {
        return false;
    }
    Station station = {id, name, xy};
    stations.insert({id, station});
    return true;
}

Name Datastructures::get_station_name(StationID id)
{
    if (stations.find(id) == stations.end())
    {
        return NO_NAME;
    }
    return stations.at(id).name;
}

Coord Datastructures::get_station_coordinates(StationID id)
{
    if (stations.find(id) == stations.end())
    {
        return NO_COORD;
    }
    return stations.at(id).coordinates;
}

std::vector<StationID> Datastructures::stations_alphabetically()
{
    std::vector<StationID> alph_ord_stations;
    if (stations.empty())
    {
        return alph_ord_stations;
    }

    // Create helper vector for sorting stations by name
    std::vector<std::pair<std::string, std::string>> name_id_pairs;
    name_id_pairs.reserve(stations.size());

    for (auto& elem : stations)
    {
        name_id_pairs.push_back({elem.second.name, elem.first});
    }

    // Sort stations by name
    std::sort(name_id_pairs.begin(), name_id_pairs.end(),
              [](auto elem1, auto elem2){ return elem1.first < elem2.first;});

    // Transfer stations to vector to be returned
    std::transform(name_id_pairs.begin(), name_id_pairs.end(),
                   std::back_inserter(alph_ord_stations),
                   [](auto elem) {return elem.second;});

    return alph_ord_stations;
}

std::vector<StationID> Datastructures::stations_distance_increasing()
{
    std::vector<StationID> dist_ord_stations;
    if (stations.empty())
    {
        return dist_ord_stations;
    }

    // Create helper vector for sorting stations by coords
    std::vector<std::pair<Coord, std::string>> coord_id_pairs;
    coord_id_pairs.reserve(stations.size());
    dist_ord_stations.reserve(stations.size());

    for (auto& elem : stations)
    {
        coord_id_pairs.push_back({elem.second.coordinates, elem.first});
    }

    // Calculating distances for stations and sorting them
    std::sort(coord_id_pairs.begin(), coord_id_pairs.end(),
              [](auto elem1, auto elem2){
        auto dist1 = elem1.first.x*elem1.first.x + elem1.first.y*elem1.first.y;
        auto dist2 = elem2.first.x*elem2.first.x + elem2.first.y*elem2.first.y;
        if (dist1 == dist2){return elem1.first.y < elem2.first.y;}
        else{return dist1 < dist2;}});

    // Transfer ordered stations to vector to be returned
    std::transform(coord_id_pairs.begin(), coord_id_pairs.end(),
                   std::back_inserter(dist_ord_stations),
                   [](auto elem) {return elem.second;});

    return dist_ord_stations;
}

StationID Datastructures::find_station_with_coord(Coord xy)
{
    if (!stations.empty())
    {
        for (auto iter = stations.begin(); iter != stations.end(); iter++)
        {
            if(iter->second.coordinates == xy)
            {
                return iter->first;
            }
        }
    }
    return NO_STATION;
}

bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    if (stations.find(id) == stations.end())
    {
        return false;
    }
    stations.at(id).coordinates = newcoord;
    return true;
}

bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{
    if (stations.find(stationid) == stations.end())
    {
        return false;
    }

    if (!stations.at(stationid).trains.empty())
    {
       // Find all trains with same id but different departure time
       auto first = stations.at(stationid).trains.lower_bound(trainid);
       auto last = stations.at(stationid).trains.upper_bound(trainid);
       for (auto iter = first; iter != last; iter++)
       {
           if (iter->second == time)
           {
               return false;
           }
       }
    }
    stations.at(stationid).trains.insert({trainid, time});
    return true;
}

bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    if (stations.find(stationid) == stations.end())
    {
            return false;
    }

    if (!stations.at(stationid).trains.empty())
    {
       // Find all trains with same id but different departure time
       auto first = stations.at(stationid).trains.lower_bound(trainid);
       auto last = stations.at(stationid).trains.upper_bound(trainid);
       for (auto iter = first; iter != last; iter++)
       {
            if (iter->second == time)
            {
                stations.at(stationid).trains.erase(iter);
                return true;
            }
        }
    }
    return false;
}

std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{
    std::vector<std::pair<Time, TrainID>> depart_after;
    if (stations.find(stationid) == stations.end())
    {
        depart_after.push_back({NO_TIME, NO_TRAIN});
        return depart_after;
    }

    if (!stations.at(stationid).trains.empty())
    {
        for (auto& elem : stations.at(stationid).trains)
        {
            if (elem.second >= time)
            {
                depart_after.push_back({elem.second, elem.first});
            }
         }

    //sorting ids and times
    std::sort(depart_after.begin(), depart_after.end(),
                  [](auto a, auto b){if (a.first == b.first)
                    {return a.second < b.second;} else {return a.first < b.first;}});
    }
    return depart_after;
}

bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    if (regions.find(id) != regions.end())
    {
        return false;
    }
    Region region = {id, name, coords,{}};
    regions.insert({id, region});
    return true;
}

std::vector<RegionID> Datastructures::all_regions()
{
    std::vector<RegionID> region_ids;
    if (!regions.empty())
    {
        region_ids.reserve(regions.size());
        transform(regions.begin(), regions.end(),
                  back_inserter(region_ids),
                [](auto &elem){return elem.first;});
    }
    return region_ids;
}

Name Datastructures::get_region_name(RegionID id)
{
    if (regions.find(id) == regions.end())
    {
        return NO_NAME;
    }
    return regions.at(id).name;
}

std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    if (regions.find(id) == regions.end())
    {
        std::vector<Coord> empty_vec = {NO_COORD};
        return empty_vec;
    }
    return regions.at(id).coordinates;
}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    auto end = regions.end();
    if (regions.empty() or regions.find(id) == end
                    or regions.find(parentid) == end)
    {
        return false;
    }

    Region* child = &regions.at(id);
    Region* parent = &regions.at(parentid);
    if (child->parent != nullptr)
    {
        return false;
    }
    parent->children.push_back(child);
    child->parent = parent;
    return true;
}

bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
    if (regions.empty() or stations.empty()
            or regions.find(parentid) == regions.end()
            or stations.find(id) ==  stations.end())
    {
        return false;
    }

    if (stations.at(id).parent == nullptr)
    {
        Region* parent = &regions.at(parentid);
        stations.at(id).parent = parent;
        return true;
    }
    return false;
}


std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    std::vector<RegionID> belongsto;
    if (stations.find(id) == stations.end())
    {
        belongsto.push_back(NO_REGION);
    }

    else if (stations.at(id).parent != nullptr)
    {
        belongsto.reserve(regions.size());
        Region* tmp = stations.at(id).parent;
        while( tmp->parent != nullptr)
        {
            belongsto.push_back(tmp->id);
            tmp = tmp->parent;
        }
        belongsto.push_back(tmp->id);
    }
    return belongsto;
}

std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id)
{
    std::vector<RegionID> subregions;
    if (regions.find(id) == regions.end())
    {
        subregions.push_back(NO_REGION);
        return subregions;
    }

    if (!regions.at(id).children.empty())
    {
        subregions.reserve(regions.size());
        std::stack<Region*> nodestack;
        Region* root = &regions.at(id);
        nodestack.push(root);

        while (!nodestack.empty())
        {
            Region* tmp = nodestack.top();
            if (tmp != root)
            {
               subregions.push_back(tmp->id);
            }
            nodestack.pop();
            for (uint i = 0; i < tmp->children.size(); i++)
            {
                nodestack.push(tmp->children[i]);
            }
        }
    }
    return subregions;
}

std::vector<StationID> Datastructures::stations_closest_to(Coord xy)
{
    // Create helper vector for sorting stations by distance
    std::vector<std::pair<Coord, StationID>> all_coords;
    all_coords.reserve(stations.size());
    for (auto& elem : stations)
    {
        all_coords.push_back({elem.second.coordinates, elem.first});
    }

    // Calculates stations distances and sorts them
    std::sort(all_coords.begin(), all_coords.end(), [xy](auto e1, auto e2)
            {auto dist1 = (xy.x-e1.first.x)*(xy.x-e1.first.x) + (xy.y-e1.first.y)*(xy.y-e1.first.y);
             auto dist2 = (xy.x-e2.first.x)*(xy.x-e2.first.x) + (xy.y-e2.first.y)*(xy.y-e2.first.y);
             if (dist1 == dist2){return e1.first.y < e2.first.y;}
             else{return dist1 < dist2;}});

    // Only 3 closest stations are needed
    if(all_coords.size()> 3)
    {
        all_coords.erase(all_coords.begin()+3, all_coords.end());
    }

    std::vector<StationID> ids;
    for (auto iter = all_coords.begin(); iter != all_coords.end(); iter++)
    {
        ids.push_back(iter->second);
    }
    return ids;
}

bool Datastructures::remove_station(StationID id)
{
    if (!stations.empty())
    {
        if (stations.find(id) != stations.end())
        {
            stations.erase(id);
            return true;
        }
    }
    return false;
}

RegionID Datastructures::common_parent_of_regions(RegionID id1, RegionID id2)
{
    if (regions.find(id1) == regions.end()
            or regions.find(id2)== regions.end())
    {
        return NO_REGION;
    }
    Region* reg1 = &regions.at(id1);
    Region* reg2 = &regions.at(id2);
    std::map<RegionID, int> parents;

    // Collects all parents of region1
    while (reg1->parent!= nullptr)
    {
        parents[reg1->parent->id] += 1;
        reg1 = reg1->parent;
    }
    while (reg2->parent!= nullptr)
    {
        parents[reg2->parent->id] += 1;
        if (parents[reg2->parent->id] > 1)
        {
            return reg2->parent->id;
        }
        reg2 = reg2->parent;
    }
    return NO_REGION;
}


/*!
 * \brief add_train inserts new train into the train container and adds departure information
 * \of the train to right stations
 * \param trainid unique id of a train, type TrainID
 * \param stationtimes information about stations and departure times, type vector<pair<StationID, Time>>
 * \return true if insertion succeed, false otherwise, type bool
 */
bool Datastructures::add_train(TrainID trainid, std::vector<std::pair<StationID, Time> > stationtimes)
{
    if (trains.find(trainid) != trains.end())
    {
        return false;
    }

    // Checks if all stations of a train exist
    for (auto& elem : stationtimes)
    {
        auto id = elem.first;
        if (stations.find(id) == stations.end())
        {
            return false;
        }
    }

    // Adds the departure for the station and adds information about next neighbor
    //for the station
    for (uint i = 0; i < stationtimes.size()-1; i++)
    {
        auto id = stationtimes[i].first;
        auto d_time = stationtimes[i].second;
        add_departure(id, trainid, d_time);

        auto next_id = stationtimes[i+1].first;
        Station*  next_station = &stations.at(next_id);
        stations.at(id).next_stations.push_back(std::make_pair(next_id, next_station));
    }

    trains[trainid] = {trainid, stationtimes};
    return true;
}


/*!
 * \brief next_stations_from returns list of neighbor stations of a station
 * \param trainid unique id of a train, type TrainID
 * \return list of station ids, type vector<StationID>
 */
std::vector<StationID> Datastructures::next_stations_from(StationID id)
{
    std::vector<StationID> neighbor_stations;

    if (!stations.count(id))
    {
        neighbor_stations.push_back(NO_STATION);
        return neighbor_stations;
    }

    if (stations.at(id).trains.empty())
    {
        return neighbor_stations;
    }

    if (!stations.at(id).next_stations.empty())
    {
        for (auto& elem : stations.at(id).next_stations)
        {
            auto to_push = elem.first;
            neighbor_stations.push_back(to_push);
        }
    }
    return neighbor_stations;
}


/*!
 * \brief train_stations_from returns list of train's next stations after a given station
 * \param stationid unique id of a station, type StationID
 * \param trainid unique id of a train, type TrainID
 * \return list of station ids of next stations, type vector<StationID>
 */
std::vector<StationID> Datastructures::train_stations_from(StationID stationid, TrainID trainid)
{
        std::vector<StationID> trainstations;

        if (stations.empty() or trains.empty() or
            !stations.count(stationid) or !trains.count(trainid))
        {
            trainstations.push_back(NO_STATION);
            return trainstations;
        }

        // Searches the right station and saves all stations after it into a vector
        bool found = false;
        std::vector<std::pair<StationID, Time>>::iterator right_station;
        if (!trains.at(trainid).stationtimes.empty())
        {
            for (auto iter = trains.at(trainid).stationtimes.begin(); iter !=
                 trains.at(trainid).stationtimes.end(); iter++)
            {
                if (iter->first == stationid)
                {
                    right_station = iter +1;
                    found = true;
                    break;
                }
            }

            if (found)
            {
                while(right_station != trains.at(trainid).stationtimes.end())
                {
                    trainstations.push_back(right_station->first);
                    right_station++;
                }
             }
        }
        if (trainstations.empty())
        {
            trainstations.push_back(NO_STATION);
        }
        return trainstations;

}


/*!
 * \brief clear_trains removes all trains of the stations
 */
void Datastructures::clear_trains()
{
    trains.clear();

    // Removes information about trains also from the stations
    for (auto& elem : stations)
    {
        elem.second.trains.clear();
    }
}


/*!
 * \brief route_any finds a route between two stations
 * \param fromid unique id of a station, type StationID
 * \param toid unique id of a station, type StationID
 * \return list a stations along the route, type vector<pair<StationID, Distance>>
 */
std::vector<std::pair<StationID, Distance>> Datastructures::route_any(StationID fromid, StationID toid)
{
    std::vector<std::pair<StationID, Distance>> route;
    std::queue<Station*> queue;

    if (!stations.count(fromid) or !stations.count(toid))
    {
        route.push_back(std::make_pair(NO_STATION, NO_DISTANCE));
        return route;
    }
    if (fromid == toid)
    {
        return route;
    }

    // Initializing stations
    for (auto &elem : stations)
    {
        elem.second.color = "white";
        elem.second.distance = -1;
        elem.second.from = nullptr;
    }
    Station* fromstation = &stations.at(fromid);
    Station* tostation = &stations.at(toid);
    fromstation->color = "gray";
    fromstation->distance = 0;
    fromstation->from = nullptr;
    queue.push(fromstation);

    while (!queue.empty())
    {
        Station* current = queue.front();
        queue.pop();

        // Collects the route data if the right station is found
        if (current == tostation)
        {
            Station* tmp = current;
            while (tmp != nullptr)
            {
                route.push_back(std::make_pair(tmp->id, tmp->distance));
                tmp = tmp->from;
            }
            std::reverse(route.begin(), route.end());
            return route;
        }
        for (auto iter = current->next_stations.begin(); iter != current->next_stations.end(); iter++)
        {
            if (iter->second->color == "white")
            {
                iter->second->color = "gray";
                Distance dist = calculate_distance(current->coordinates, iter->second->coordinates);
                iter->second->distance = current->distance + dist;
                iter->second->from = current;
                queue.push(iter->second);
            }
        }
        current->color = "black";
    }
    return route;
}


/*!
 * \brief route_least_stations finds a route between two stations with least stations
 * \param fromid unique id of a station, type StationID
 * \param toid unique id of a station, type StationID
 * \return list a stations along the route, type vector<pair<StationID, Distance>>
 */
std::vector<std::pair<StationID, Distance>> Datastructures::route_least_stations(StationID fromid, StationID toid)
{
   // rote_any is implemented with bfs and it already finds the shortest route
    return route_any(fromid, toid);
}


/*!
 * \brief route_with cykle finds a route with cykle on it
 * \param fromid unique id of a station, type StationID
 * \return list a stations along the cyckled route, type vector<StationID>
 */
std::vector<StationID> Datastructures::route_with_cycle(StationID fromid)
{
    std::stack<Station*> stack;
    std::vector<StationID> route;

    if (stations.empty() or !stations.count(fromid))
    {
        route.push_back(NO_STATION);
        return route;
    }

    // Initializing stations
    for (auto &elem : stations)
    {
        elem.second.color = "white";
        elem.second.from = nullptr;
    }
    Station* fromstation = &stations.at(fromid);
    stack.push(fromstation);
    while (!stack.empty())
    {
        Station* current = stack.top();
        stack.pop();
        if (current->color == "white")
        {
            current->color = "gray";
            stack.push(current);
            for (auto iter = current->next_stations.begin(); iter != current->next_stations.end(); iter++)
            {
                if (iter->second->color == "white")
                {
                    iter->second->from = current;
                    stack.push(iter->second);
                }
                // Saves the stations along the route if a cycle is found
                else if (iter->second->color == "gray")
                {
                    Station* tmp = current;
                    while (tmp != nullptr)
                    {
                       route.push_back(tmp->id);
                       tmp = tmp->from;
                    }
                    std::reverse(route.begin(), route.end());
                    route.push_back(iter->second->id);
                    return route;
                }
            }
        }
        else
        {
            current->color = "black";
        }
    }
    return route;
}


/*!
 * \brief route_shortest_distance finds the shortest route between two stations
 * \param fromid unique id of a station, type StationID
 * \param toid unique id of a station, type StationID
 * \return list a stations along the route, type vector<pair<StationID, Distance>>
 */
std::vector<std::pair<StationID, Distance>> Datastructures::route_shortest_distance(StationID fromid, StationID toid)
{
    std::vector<std::pair<StationID, Distance>> route;
    std::priority_queue<Station*, std::vector<Station*>, Compare> queue;

    if (!stations.count(fromid) or !stations.count(toid))
    {
        route.push_back(std::make_pair(NO_STATION, NO_DISTANCE));
        return route;
    }

    // Initializing stations
    for (auto &elem : stations)
    {
        elem.second.color = "white";
        elem.second.distance = -1;
        elem.second.from = nullptr;
    }
    Station* fromstation = &stations.at(fromid);
    Station* tostation = &stations.at(toid);
    fromstation->color = "gray";
    fromstation->distance = 0;
    fromstation->from = nullptr;
    queue.push(fromstation);

    while (!queue.empty())
    {
        Station* current = queue.top();
        queue.pop();
        if (current->color == "black")
        {
            continue;
        }

        // Collects the route data if the right station is found
        if (current == tostation)
        {
            Station* tmp = current;
            while (tmp != nullptr)
            {
                route.push_back(std::make_pair(tmp->id, tmp->distance));
                tmp = tmp->from;
            }
            std::reverse(route.begin(), route.end());
            return route;
        }
        for (auto iter = current->next_stations.begin(); iter != current->next_stations.end(); iter++)
        {
            Relax(current, iter->second);
            if (iter->second->color == "white")
            {
                iter->second->color = "gray";
                queue.push(iter->second);
            }
            else
            {
               queue.push(iter->second);
            }
        }
        current->color = "black";
    }
    return route;
}



/*!
 * \brief route_earliest_arrival finds the route between two stations with earliest arrival
 * \ after a given time
 * \param fromid unique id of a station, type StationID
 * \param toid unique id of a station, type StationID
 * \param starttime time after which the arliest route is searched, type Time
 * \return list a stations and arrival times of trains along the route, type vector<pair<StationID, Time>>
 */
std::vector<std::pair<StationID, Time>> Datastructures::route_earliest_arrival(StationID /*fromid*/, StationID /*toid*/, Time /*starttime*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_earliest_arrival()");
    /*std::vector<std::pair<StationID, Time>> route;
    std::priority_queue<Station*, std::vector<Station*>, Compare_times> queue;

    if (!stations.count(fromid) or !stations.count(toid))
    {
        route.push_back(std::make_pair(NO_STATION, NO_DISTANCE));
        return route;
    }

    // Initializing stations
    for (auto &elem : stations)
    {
        elem.second.color = "white";
        elem.second.time = 0;
        elem.second.from = nullptr;
    }
    Station* fromstation = &stations.at(fromid);
    Station* tostation = &stations.at(toid);
    fromstation->color = "gray";
    fromstation->time = starttime;
    fromstation->whole_time = starttime;
    fromstation->from = nullptr;
    queue.push(fromstation);

    while (!queue.empty())
    {
        Station* current = queue.top();
        queue.pop();
        if (current->color == "black")
        {
            continue;
        }

        // Collects the route data if the right station is found
        if (current == tostation)
        {
            Station* tmp = current;
            while (tmp != nullptr)
            {
                route.push_back(std::make_pair(tmp->id, tmp->time));
                tmp = tmp->from;
            }
            std::reverse(route.begin(), route.end());
            return route;
        }
        for (auto iter = current->next_stations.begin(); iter != current->next_stations.end(); iter++)
        {
            Time traveltime = train_between(current, iter->second);
            if (traveltime == 0)
            {
                continue;
            }
            Relax_time(current, iter->second, traveltime);
            if (iter->second->color == "white")
            {
                iter->second->color = "gray";
                queue.push(iter->second);
            }
            else
            {
               queue.push(iter->second);
            }
        }
        current->color = "black";
    }
    return route;*/
}

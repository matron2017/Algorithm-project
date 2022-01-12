// Datastructures.hh
//

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH


#include <list>
#include <math.h>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <unordered_map>
#include <stack>
#include <queue>
#include <limits>
// Types for IDs
using TownID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";
// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

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


//Everything below this I have implemented by myself until mark *
//
//

//Hash function for pair so that it can be used
// as key for std::unordered_map/set, if needed
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator () (std::pair<T1, T2> const &pair) const
    {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);

        return h1 ^ h2;
    }
};

//
//
// *My own implementations ends here, but continue below again.



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



//Everything below this I have implemented by myself until mark *
//
//


//Colours for graph algorithms.
enum Colour {WHITE, GRAY, BLACK};

// Unordered_Map with the city ID as the search key and the valueis
// Town_info struct, which contains essential information about the city.
// Using unordered_map because
// accessing it's values is usually constant time (O (n) ≈Theta (1)).

struct Town_info {
    Name name_;
    TownID id_;
    Coord coord_;
    int tax_;
    TownID master_town_;
    // Used for saving information about town vassals.
    // Using unordered_set because deleting operation time
    // complexity is (O(n)≈Theta(1))  much more efficient
    // compared to equivalent operation with vectors O(n).
    std::unordered_set<TownID> vassal_towns_;
    int net_tax;

    // Information about which neighboring cities can be reached from specific city
    // and the distance between these neighboring cities.
    std::unordered_map<TownID, int> to_neighbours;


    //Parameter for graph algorithms.
    int distance = -1; //For BFS.
    TownID path_back = "";
    Colour colour = WHITE;

    TownID cycle_town_latest_path_back;
};


struct id_distance{
    TownID id;
    int dist;
};

//
//
// *My own implementations ends here, but continue below again.


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



// I have impelemented all the datastructures and functions below by myself. *
//
//

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();


    unsigned int town_count();

    bool add_town(TownID id, Name const& name, Coord coord, int tax);
    Name get_town_name(TownID id);

    Coord get_town_coordinates(TownID id);

    int get_town_tax(TownID id);

    std::vector<TownID> all_towns();

    std::vector<TownID> find_towns(Name const& name);

    bool change_town_name(TownID id, Name const& newname);

    std::vector<TownID> towns_alphabetically();

    std::vector<TownID> towns_distance_increasing();

    TownID min_distance();

    TownID max_distance();

    bool add_vassalship(TownID vassalid, TownID masterid);

    std::vector<TownID> get_town_vassals(TownID id);

    std::vector<TownID> taxer_path(TownID id);

    bool remove_town(TownID id);

    std::vector<TownID> towns_nearest(Coord coord);

    std::vector<TownID> longest_vassal_path(TownID id);

    int total_net_tax(TownID id);

    void clear_all();

    void clear_roads();

    std::vector<std::pair<TownID, TownID>> all_roads();

    bool add_road(TownID town1, TownID town2);

    std::vector<TownID> get_roads_from(TownID id);

    std::vector<TownID> any_route(TownID fromid, TownID toid);

    bool remove_road(TownID town1, TownID town2);

    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    std::vector<TownID> road_cycle_route(TownID startid);


    // Not implemented
    std::vector<TownID> shortest_route(TownID, TownID);
    Distance trim_road_network();

private:

    // The key is the city id, and the value is struct,
    // which has relevant information.
    using Towns = std::unordered_map<TownID, Town_info>;

    Towns towns;

    // Comparison function for using the sort algorithm.
    bool compare_town_name(TownID& town_b, TownID& town_a);

    // Compares the distance of two different points to the origo
    bool compare_origo_distance(TownID& town_b, TownID& town_a);

    // Calculates the distance of a point from the origo
    int origo_distance(Coord &coord);

    // Compares the distance between two different points
    bool compare_distance(id_distance &town_b, id_distance &town_a);

    // Calculates the distance between two points
    int points_distance(Coord &coord_a, Coord &coord_b);

    // Go through the vassal cities recursively and returns
    // vector of the longest vassal town connection.
    std::vector<TownID> longest_path(TownID id);

    //Depth-first-search for function any_route
    std::stack<TownID> DFS_for_any_route(TownID fromid, TownID destination_id);

    //Breadth-First Search for function least_towns_route
    void BFS(TownID fromid, std::queue<TownID> queue_);

    //Depth-first Search for finding a cycle
    TownID DFS_for_cycle_road(TownID fromid);


};

#endif // DATASTRUCTURES_HH

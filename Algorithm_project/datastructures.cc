// Datastructures.cc

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

// I have implemented every function below by myself.
//
//



Datastructures::Datastructures()
{
     Towns towns = Towns();
}

Datastructures::~Datastructures()
{
}

unsigned int Datastructures::town_count()
{
    //
    // size () Counts the number of items in a container, according to the cpp reference O (1)
    return towns.size();
}



bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{

    // count algorithm looks to see if the parameter is already in the map. Its effectiveness is
    // O (n)≈Theta (1), because in unordered_map the value is is accessed with time complexity of Theta(1).
    // The other operations below are also constant-time, so in total O (n)≈Theta (1);
    if((!towns.count(id))){
        Town_info Town_info_ = Town_info();
        Town_info_.id_ = id;
        Town_info_.name_ = name;
        Town_info_.coord_ = coord;
        Town_info_.tax_ = tax;
        Town_info_.net_tax = tax;
        towns[id] = Town_info_;
        return true;
    }
    return false;

}

Name Datastructures::get_town_name(TownID id)
{
    //  count algorithm is used to check if the parameter is in the map. O(n)≈Theta(1)
    if(towns.count(id)){
        return towns[id].name_;
    }
    return NO_NAME;

}

Coord Datastructures::get_town_coordinates(TownID id)
{

    //  count algorithm is used to check if the parameter is in the map. O(n)≈Theta(1)
    if(towns.count(id)){
        return towns[id].coord_;
    }

    return NO_COORD;
}

int Datastructures::get_town_tax(TownID id)
{

    //count algorithm is used to check if the parameter is in the map. O(n)≈Theta(1)
    if(towns.count(id)){
        return towns[id].tax_;
    }
    return NO_VALUE;

}

std::vector<TownID> Datastructures::all_towns()
{
    std::vector<TownID> all_towns_vector;
    // O(n)
    for(auto it = towns.begin();  it != towns.end(); it++){
                   all_towns_vector.push_back((*it).first);
    }
    return all_towns_vector;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    // For iterators, the loop efficiency is O (n)
    std::vector<TownID> certain_named_towns;
    for(auto it = towns.begin();  it != towns.end(); it++){
        if(((*it).second).name_== name){
             certain_named_towns.push_back((*it).first);
        }
    }
    return certain_named_towns;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{

    //count algorithm is used to check if the parameter is in the map. O(n)≈Theta(1)
    if(towns.count(id)){
        towns[id].name_ = newname;
        return true;
    }
    return false;

}



bool Datastructures::compare_town_name(TownID &town_b, TownID &town_a)
{return towns[town_a].name_<towns[town_b].name_;}



std::vector<TownID> Datastructures::towns_alphabetically()
{
    std::vector<TownID> all_towns_vector;

    //O(n)
    for(auto it = towns.begin();  it != towns.end(); it++){
                  all_towns_vector.push_back(((*it).first));
    }

    // The time complexity of sort algorithm in this case is O (n log n).
    // In the case of unordered_map, we don't get a more efficient way to do this.
    // So we have to sacrifice efficiency here, but the operations often performed by this
    // program are O(n)≈Theta(1), so the loss isn't that big.
    sort(all_towns_vector.begin(), all_towns_vector.end(), [this](TownID id_a, TownID id_b){return this->compare_town_name(id_b, id_a);});
    return all_towns_vector;


}

// O(n)≈Theta(1)
int Datastructures::origo_distance(Coord &coord){
    return floor(sqrt(double(pow(0 - coord.x, 2) + pow(0 - coord.y, 2))));
}

// O(n)≈Theta(1)
bool Datastructures::compare_origo_distance(TownID &town_b, TownID &town_a){
    if(origo_distance(towns[town_a].coord_) < origo_distance(towns[town_b].coord_)){
        return true;
    }
    return false;
}


std::vector<TownID> Datastructures::towns_distance_increasing()
{

    std::vector<TownID> all_towns_vector;
    for(auto it = towns.begin();  it != towns.end(); it++){
                   all_towns_vector.push_back(((*it).first));
    }
    // sotring algorithm, O(n log n)
    sort(all_towns_vector.begin(), all_towns_vector.end(), [this](TownID id_a, TownID id_b){return this->compare_origo_distance(id_b, id_a);});
    return all_towns_vector;

}


TownID Datastructures::min_distance()
{
    if(towns.empty()){
        return NO_TOWNID;
    }

    TownID min_town;
    int min_value = -1;

    // O(n)
    for(auto it = towns.begin();  it != towns.end(); it++){
        int town_origo_dist = origo_distance(it->second.coord_);
        if(min_value == -1 || min_value > town_origo_dist){
            min_value = town_origo_dist;
            min_town = it->first;
        }
    }

    return min_town;
}

TownID Datastructures::max_distance()
{
    if(towns.empty()){
        return NO_TOWNID;
    }

    TownID max_town;
    int max_value = -1;

    //O(n)
    for(auto it = towns.begin();  it != towns.end(); it++){
        int town_origo_dist = origo_distance(it->second.coord_);
        if(max_value < town_origo_dist){
            max_value = town_origo_dist;
            max_town = it->first;
        }
    }
    return max_town;
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    // O(n)≈Theta(1)
    if(towns[vassalid].master_town_ != "" || !towns.count(vassalid) || !towns.count(masterid)){
        return false;
    }
    towns[vassalid].master_town_ = masterid;
    towns[masterid].vassal_towns_.insert(vassalid);

    int& vassal_tax = towns[vassalid].net_tax;
    int& master_tax = towns[masterid].net_tax;
    master_tax = master_tax + floor(vassal_tax/10);
    vassal_tax = vassal_tax - floor(vassal_tax/10);

    return true;
}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    std::vector<TownID> vassal_towns_vector;
    if(!towns.count(id)){
        vassal_towns_vector.push_back(NO_TOWNID);
        return  vassal_towns_vector;
    }
    //O(n)
    else{
    for(auto it = towns[id].vassal_towns_.begin();  it != towns[id].vassal_towns_.end(); it++){
        vassal_towns_vector.push_back(*it);
    }
    return vassal_towns_vector;
    }

}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{

    std::vector<TownID> master_id_vector;
    std::vector<TownID>& vector = master_id_vector;

    if(!towns.count(id)){
         vector.push_back(NO_TOWNID);
        return vector;
    }
    // O(n^2)≈Theta(n)
    vector.push_back(id);
    TownID master_town = towns[id].master_town_;
    while(master_town!= ""){
        vector.push_back(master_town);
        master_town = towns[master_town].master_town_;
    }

    return vector;
}

bool Datastructures::remove_town(TownID id)
{
    auto& town=towns[id];

    // O(n)≈Theta(1)
    if(!towns.count(id)){
        return false;
    }
    else if(town.master_town_ != "" && size(town.vassal_towns_) > 0){
        int tax = 0;
        // O(n^2)≈Theta(n)
        for(auto it = town.vassal_towns_.begin();  it != town.vassal_towns_.end(); it++){
            towns[*it].master_town_ = town.master_town_;
            tax = floor(tax + towns[*it].net_tax);
        }
        // O(n)≈Theta(1)
        towns[town.master_town_].vassal_towns_.erase(id);
        towns[town.master_town_].vassal_towns_.insert(town.vassal_towns_.begin(), town.vassal_towns_.end());
        towns[town.master_town_].net_tax = floor(towns[town.master_town_].net_tax - (town.tax_-(tax/9))/9);
        towns.erase(id);
        return true;
    }

    else if(town.master_town_ == "" && size(town.vassal_towns_) > 0){
        // O(n^2)≈Theta(n)
        for(auto it = town.vassal_towns_.begin();  it != town.vassal_towns_.end(); it++){
            towns[*it].master_town_ = "";
            int &tax = towns[*it].net_tax;
            tax = floor(tax/9 + tax);
        }

        towns.erase(id);
        return true;
    }

    else{
        // O(n)≈Theta(1)
        towns[town.master_town_].vassal_towns_.erase(town.id_);
        towns[town.master_town_].net_tax = floor(towns[town.master_town_].net_tax - town.tax_ /9);
        towns.erase(id);
        return true;
    }

}

// O(n)≈Theta(1)
int Datastructures::points_distance(Coord &coord_a, Coord &coord_b){
    return floor(sqrt(double(pow(coord_b.x - coord_a.x, 2) + pow(coord_b.y - coord_a.y, 2))));
}

bool Datastructures::compare_distance(id_distance &town_b, id_distance &town_a){
    if(town_a.dist < town_b.dist){
        return true;
    }
    return false;
}

std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{

    std::vector<id_distance> all_towns_vector;
    std::vector<id_distance>& vector = all_towns_vector;
    std::vector<TownID> output_vector;

    //O(n)
    for(auto it = towns.begin();  it != towns.end(); it++){
        id_distance town = {it->first, points_distance(it->second.coord_, coord)};
        vector.push_back(town);
    }
    // sotring algorithm, O(n log n)
    sort(vector.begin(), vector.end(), [this](id_distance id_a, id_distance id_b){return this->compare_distance(id_b, id_a);});

    // O(n)
    for(auto it = vector.begin();  it != vector.end(); it++){
        output_vector.push_back(it->id);
    }
    return output_vector;

}


std::vector<TownID> Datastructures::longest_path(TownID id)
    {

        //
        // Starts at the root node which is the give TownID.
        // Recursively goes through nodes (towns in this case),
        // and marks which part of the route is the longest.
        std::vector<std::string> longest;
        for (auto vassal : towns[id].vassal_towns_)
        {
            auto next = longest_path(vassal);
            if (next.size() > longest.size())
                longest = std::move(next);
        }
        longest.insert(longest.begin(), id);
        return longest;
    }

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    //O(V^2)≈Theta(V)

    std::vector<TownID> longest_path_ = longest_path(id);
    return longest_path_;
}


int Datastructures::total_net_tax(TownID id)
{
    // O(n)≈Theta(1)
    return towns[id].net_tax;
}



//
//
//
//
//
// Phase 2 operations
//
//
//
//


void Datastructures::clear_all()
{
    // The clear () algorithm removes each member from the container. Approximately O(n),
    // because each key-value pair is deleted separately, so
    // there will be as many operations as there are items in this container.
    // Information about routes are stored in the same container,
    // so they are removed at the same time.
    if(!towns.empty()){
        towns.clear();
    }
}


// Removes every road.
// O(n^2)
void Datastructures::clear_roads()
{
    for(auto it = towns.begin();  it != towns.end(); it++){
             (*it).second.to_neighbours.clear();
    }
}



// O(n^2)
std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    std::vector<std::pair<TownID, TownID>> pairs;

    std::unordered_set<std::pair<TownID, TownID>, pair_hash> found_towns;

    std::pair<TownID, TownID> town_id_pair;

    for (auto town = towns.begin(); town != towns.end(); town++){
        for(auto neighbour_id = (*town).second.to_neighbours.begin();  neighbour_id !=(*town).second.to_neighbours.end(); neighbour_id++){
            if((*neighbour_id).first > (*town).first){
                town_id_pair.first = (*town).first;
                town_id_pair.second = (*neighbour_id).first;
            }
            else{
                town_id_pair.first = (*neighbour_id).first;
                town_id_pair.second = (*town).first;
            }
            if(!found_towns.count(town_id_pair)){
                pairs.push_back(town_id_pair);
                found_towns.insert(town_id_pair);
            }
        }
    }
    return pairs;
}


bool Datastructures::add_road(TownID town1, TownID town2)
{

    //count -algorithm checks if parameter is in map. O(n)≈Theta(1)
    if(towns.count(town1) && towns.count(town2)){
        if(!towns[town1].to_neighbours.count(town2) or !towns[town2].to_neighbours.count(town1))
        {
           //Add routes to a neighboring city if there isn't one yet
           // and if both cities exist.
           // Time complexity for a single addition for single addition is O(n)≈Theta (1)

           int distance = points_distance(towns[town1].coord_,towns[town2].coord_);
           towns[town1].to_neighbours.insert({town2, distance});
           towns[town2].to_neighbours.insert({town1, distance});

           return true;
        }
    }
    return false;

}

std::vector<TownID> Datastructures::get_roads_from(TownID fromid)
{
    std::vector<TownID> neighbours;

    //O(n)
    if(towns.count(fromid)){
        if(!towns[fromid].to_neighbours.empty()){
            for(auto neighbour_id = towns[fromid].to_neighbours.begin(); neighbour_id != towns[fromid].to_neighbours.end(); neighbour_id++)
            {
                neighbours.push_back((*neighbour_id).first);
            }
            return neighbours;
        }

        return neighbours;
    }
    neighbours.push_back(NO_TOWNID);
    return neighbours;
}




// Depth-first search performance is O(E)
// (E (comes from the word edge) means the number of roads in this case)

std::stack<TownID> Datastructures::DFS_for_any_route(TownID fromid, TownID destination_id){
    // If the destination_id is found, the stack is returned recursively
    // and the function ends

     std::stack<TownID> pile_;

    //Turns all nodes to white and clears memory of routes
    for(auto it = towns.begin();  it != towns.end(); it++){
             (*it).second.colour = WHITE;
             (*it).second.path_back = "";

    }

    pile_.push(fromid);

    if(pile_.top() == destination_id){
        return pile_;
    }

    while(!pile_.empty()){
        TownID top_node = pile_.top();
        pile_.pop();
        if(towns[top_node].colour == WHITE){
            towns[top_node].colour = GRAY;
            pile_.push(top_node);

            for(auto neighbour_id = towns[top_node].to_neighbours.begin(); neighbour_id != towns[top_node].to_neighbours.end(); neighbour_id++){
                if(towns[(*neighbour_id).first].colour == WHITE){
                    pile_.push((*neighbour_id).first);
                    towns[(*neighbour_id).first].path_back = top_node;
                    //Returns route if the correct destination is found
                    if((*neighbour_id).first == destination_id){
                        return pile_;
                    }
                }
                //Marks a loop
                else if(towns[(*neighbour_id).first].colour == GRAY){
                }
            }
        }
        else{
            towns[top_node].colour = BLACK;
        }
    }
    return pile_;
}



std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{
    std::vector<TownID> route_;
    if(!towns.count(fromid) or !towns.count(toid)){
        route_.push_back(NO_TOWNID);
        return route_;
    }

    //DFS, which returns the route as a stack (destination is on top),
    // O(E)
     std::stack<TownID> pile_ = DFS_for_any_route(fromid, toid);
    //O(n)

    if(towns[toid].path_back == ""){
        return route_;

    }

    bool routes_added = false;

    TownID &path_back_town = toid;
    // O(N)
    while(!routes_added){
        route_.push_back(path_back_town);
        path_back_town = towns[path_back_town].path_back;
        if(path_back_town == fromid){
            route_.push_back(path_back_town);
            routes_added = true;
        }
    }

    //O(n)
    std::reverse(route_.begin(), route_.end());

    return route_;
}

bool Datastructures::remove_road(TownID town1, TownID town2)
{
    //count algorithm checks if parameter is already in map. O(n)≈Theta(1)
    if(towns.count(town1) && towns.count(town2)){
        if(towns[town1].to_neighbours.count(town2) && towns[town2].to_neighbours.count(town1))
        {
           // Delete the route to a neighboring city.
           // Erase function's time complexity is  O(n)≈Theta(1)

           towns[town1].to_neighbours.erase(town2);
           towns[town2].to_neighbours.erase(town1);

           return true;
        }
    }
    return false;

}

// Breadth-First Search performance is (O(E))
//       (E  means number of routes in this case)

void Datastructures::BFS(TownID fromid,std::queue<TownID> queue_){

    //Marks every node as white and clears memory of routes. O(n)
    for(auto it = towns.begin();  it != towns.end(); it++){
             (*it).second.colour = WHITE;
             (*it).second.path_back = "";
             (*it).second.distance = std::numeric_limits<int>::max();;

    }

    towns[fromid].colour = GRAY;
    towns[fromid].distance = 0;
    queue_.push(fromid);

    while(!queue_.empty()){
        TownID front_id = queue_.front();
        queue_.pop();
        for(auto neighbour_id = towns[front_id].to_neighbours.begin(); neighbour_id != towns[front_id].to_neighbours.end(); neighbour_id++){
            if(towns[(*neighbour_id).first].colour == WHITE){
                towns[(*neighbour_id).first].colour = GRAY;
                towns[(*neighbour_id).first].distance = towns[front_id].distance + 1;
                towns[(*neighbour_id).first].path_back = front_id;
                queue_.push((*neighbour_id).first);
            }
        }
        towns[front_id].colour = BLACK;
    }
}

std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{
    std::vector<TownID> route_;
    if(!towns.count(fromid) or !towns.count(toid)){
        route_.push_back(NO_TOWNID);
        return route_;
    }

    std::queue<TownID> queue_;

    //BFS, marks distance to "fromid" town.
    // If there isn't a route , then distance is marked as -1.
    // O(E)
    BFS(fromid, queue_);

    if(towns[toid].distance == -1){
        return route_;

    }

    bool routes_added = false;
    TownID &path_back_town = toid;

    // O(E)
    while(!routes_added){

        route_.push_back(path_back_town);
        path_back_town = towns[path_back_town].path_back;
        if(path_back_town == fromid){
            route_.push_back(path_back_town);
            routes_added = true;
        }
    }

    //O(n)
    std::reverse(route_.begin(), route_.end());

    return route_;
}

TownID Datastructures::DFS_for_cycle_road(TownID fromid){

     std::stack<TownID> pile_;

     //Marks every node as white and clears memory of routes. O(n)
    for(auto it = towns.begin();  it != towns.end(); it++){
             (*it).second.colour = WHITE;
             (*it).second.path_back = "";
             (*it).second.cycle_town_latest_path_back = "";

    }

    pile_.push(fromid);

    while(!pile_.empty()){
        TownID top_node = pile_.top();
        pile_.pop();
        if(towns[top_node].colour == WHITE){
            towns[top_node].colour = GRAY;
            pile_.push(top_node);
            for(auto neighbour_id = towns[top_node].to_neighbours.begin(); neighbour_id != towns[top_node].to_neighbours.end(); neighbour_id++){
                if(towns[(*neighbour_id).first].colour == WHITE){
                    pile_.push((*neighbour_id).first);
                    towns[(*neighbour_id).first].path_back = top_node;

                }
                //End function if cycle is found between town routes.
                // Then returns the town that caused the cycle.
                else if(towns[(*neighbour_id).first].colour == GRAY && towns[(top_node)].path_back != (*neighbour_id).first){
                    towns[(*neighbour_id).first].cycle_town_latest_path_back = top_node;
                    return (*neighbour_id).first;
                }
            }
        }
        else{
            towns[top_node].colour = BLACK;
        }
    }
    return "";
}

std::vector<TownID> Datastructures::road_cycle_route(TownID startid)
{
    std::vector<TownID> route_;

    if(!towns.count(startid)){
        route_.push_back(NO_TOWNID);
        return route_;
    }

    // DFS_for_cycle_road marks route before cycle, and when
    // cycle is found, returns town which caused it.
    // Performance is at worst the amount of routes. (O(E))
    TownID cycle_town = DFS_for_cycle_road(startid);
    //O(n)

    if(cycle_town == ""){
        return route_;
    }

    bool routes_added = false;

    // There is a separate memory storage in the data structure
    // for situations where you have to remember what came last
    // for this cycle.
    TownID path_back_town = towns[cycle_town].cycle_town_latest_path_back;

    route_.push_back(cycle_town);

    // O(E)
    while(!routes_added){
        route_.push_back(path_back_town);
        path_back_town = towns[path_back_town].path_back;
        if(path_back_town == startid){
            route_.push_back(path_back_town);
            routes_added = true;
        }
    }

    //O(n)
    std::reverse(route_.begin(), route_.end());

    return route_;
}












//Not implemented
std::vector<TownID> Datastructures::shortest_route(TownID /*fromid*/, TownID /*toid*/)
{
    throw NotImplemented("shortest_route()");
}

Distance Datastructures::trim_road_network()
{
    throw NotImplemented("trim_road_network()");
}


#include "../datastructures.hh"
#include <cassert>
#include <iostream>
#include <set>
#include <utility>

// Helper to normalize a pair of town IDs for comparison
std::pair<TownID, TownID> normalize_pair(TownID a, TownID b) {
    return a < b ? std::make_pair(a, b) : std::make_pair(b, a);
}

int main()
{
    // Test 1: Connected graph
    {
        Datastructures ds;
        
        // Create towns: t1, x1, t2, x2
        ds.add_town("t1", "Town1", {0, 0}, 0);
        ds.add_town("x1", "TownX1", {0, 3}, 0);
        ds.add_town("t2", "Town2", {2, 2}, 0);
        ds.add_town("x2", "TownX2", {4, 0}, 0);
        
        // Add roads
        ds.add_road("t1", "x1");  // distance 3
        ds.add_road("x1", "t2");  // distance 2
        ds.add_road("x2", "t1");  // distance 4
        ds.add_road("t1", "t2");  // distance 2
        ds.add_road("x2", "t2");  // distance 2
        ds.add_road("x1", "x2");  // distance 5
        
        // Trim the network
        Distance total = ds.trim_road_network();
        assert(total == 6);
        
        // Check remaining roads
        std::set<std::pair<TownID, TownID>> remaining_roads;
        auto roads = ds.all_roads();
        for (auto& road : roads) {
            remaining_roads.insert(normalize_pair(road.first, road.second));
        }
        
        std::set<std::pair<TownID, TownID>> expected_roads;
        expected_roads.insert(normalize_pair("t1", "t2"));
        expected_roads.insert(normalize_pair("t2", "x1"));
        expected_roads.insert(normalize_pair("t2", "x2"));
        
        assert(remaining_roads == expected_roads);
        
        // Trim again - should return same total
        Distance total2 = ds.trim_road_network();
        assert(total2 == 6);
        
        // Check that roads are unchanged
        std::set<std::pair<TownID, TownID>> remaining_roads2;
        auto roads2 = ds.all_roads();
        for (auto& road : roads2) {
            remaining_roads2.insert(normalize_pair(road.first, road.second));
        }
        assert(remaining_roads2 == expected_roads);
        
        std::cout << "trim_road_network tests passed" << std::endl;
    }
    
    // Test 2: Disconnected graph
    {
        Datastructures ds;
        
        // Create towns: A, B, C, D, E, F
        ds.add_town("A", "TownA", {0, 0}, 0);
        ds.add_town("B", "TownB", {1, 0}, 0);
        ds.add_town("C", "TownC", {3, 0}, 0);
        ds.add_town("D", "TownD", {0, 10}, 0);
        ds.add_town("E", "TownE", {4, 10}, 0);
        ds.add_town("F", "TownF", {20, 20}, 0);
        
        // Add roads
        ds.add_road("A", "B");  // distance 1
        ds.add_road("B", "C");  // distance 2
        ds.add_road("A", "C");  // distance 3
        ds.add_road("D", "E");  // distance 4
        // F is isolated - no roads
        
        // Trim the network
        Distance total = ds.trim_road_network();
        assert(total == 7);
        
        // Check remaining roads
        std::set<std::pair<TownID, TownID>> remaining_roads;
        auto roads = ds.all_roads();
        for (auto& road : roads) {
            remaining_roads.insert(normalize_pair(road.first, road.second));
        }
        
        std::set<std::pair<TownID, TownID>> expected_roads;
        expected_roads.insert(normalize_pair("A", "B"));
        expected_roads.insert(normalize_pair("B", "C"));
        expected_roads.insert(normalize_pair("D", "E"));
        
        assert(remaining_roads == expected_roads);
        
        // Verify A-C was removed (creates cycle)
        assert(remaining_roads.count(normalize_pair("A", "C")) == 0);
        
        // Verify all towns still exist
        auto all_towns = ds.all_towns();
        assert(all_towns.size() == 6);
        
        // Verify F is still isolated
        auto f_roads = ds.get_roads_from("F");
        assert(f_roads.empty());
        
        std::cout << "trim_road_network tests passed" << std::endl;
    }
    
    // Test 3: Empty graph
    {
        Datastructures ds;
        
        Distance total = ds.trim_road_network();
        assert(total == 0);
        
        auto roads = ds.all_roads();
        assert(roads.empty());
        
        std::cout << "trim_road_network tests passed" << std::endl;
    }
    
    return 0;
}

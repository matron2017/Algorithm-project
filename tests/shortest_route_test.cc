#include "../datastructures.hh"
#include <cassert>
#include <iostream>
#include <cmath>

int main()
{
    Datastructures ds;
    
    // Create test graph with towns at specified coordinates
    // Towns:
    //   A = (0, 0)
    //   B = (3, 0)
    //   C = (7, 0)
    //   D = (10, 0)
    //   X = (0, 10)
    //   Z = (20, 20)
    
    assert(ds.add_town("A", "Town A", {0, 0}, 0));
    assert(ds.add_town("B", "Town B", {3, 0}, 0));
    assert(ds.add_town("C", "Town C", {7, 0}, 0));
    assert(ds.add_town("D", "Town D", {10, 0}, 0));
    assert(ds.add_town("X", "Town X", {0, 10}, 0));
    assert(ds.add_town("Z", "Town Z", {20, 20}, 0));
    
    // Add roads with calculated distances (rounded down):
    // A-X: sqrt((0-0)^2 + (0-10)^2) = sqrt(100) = 10
    // X-D: sqrt((0-10)^2 + (10-0)^2) = sqrt(200) ≈ 14.14 -> 14 (rounded down)
    // A-B: sqrt((0-3)^2 + (0-0)^2) = sqrt(9) = 3
    // B-C: sqrt((3-7)^2 + (0-0)^2) = sqrt(16) = 4
    // C-D: sqrt((7-10)^2 + (0-0)^2) = sqrt(9) = 3
    // Z has no roads
    
    assert(ds.add_road("A", "X"));
    assert(ds.add_road("X", "D"));
    assert(ds.add_road("A", "B"));
    assert(ds.add_road("B", "C"));
    assert(ds.add_road("C", "D"));
    
    // Test 1: Weighted shortest path that differs from fewest-edges route
    // A-X-D: 10 + 14 = 24 (two edges)
    // A-B-C-D: 3 + 4 + 3 = 10 (three edges)
    // Dijkstra should return A-B-C-D (shortest by distance)
    std::vector<TownID> route_AD = ds.shortest_route("A", "D");
    assert(!route_AD.empty());
    assert(route_AD.size() == 4);
    assert(route_AD[0] == "A");
    assert(route_AD[1] == "B");
    assert(route_AD[2] == "C");
    assert(route_AD[3] == "D");
    
    // Test 2: Reverse route (D to A)
    // Should return D, C, B, A
    std::vector<TownID> route_DA = ds.shortest_route("D", "A");
    assert(!route_DA.empty());
    assert(route_DA.size() == 4);
    assert(route_DA[0] == "D");
    assert(route_DA[1] == "C");
    assert(route_DA[2] == "B");
    assert(route_DA[3] == "A");
    
    // Test 3: Unreachable destination (Z has no roads)
    std::vector<TownID> route_AZ = ds.shortest_route("A", "Z");
    assert(route_AZ.empty());
    
    // Test 4: Route from town to itself
    std::vector<TownID> route_AA = ds.shortest_route("A", "A");
    assert(route_AA.size() == 1);
    assert(route_AA[0] == "A");
    
    // Test 5: Missing source town
    std::vector<TownID> route_missing = ds.shortest_route("missing", "A");
    assert(route_missing.size() == 1);
    assert(route_missing[0] == NO_TOWNID);
    
    // Test 6: Missing destination town
    std::vector<TownID> route_A_missing = ds.shortest_route("A", "missing");
    assert(route_A_missing.size() == 1);
    assert(route_A_missing[0] == NO_TOWNID);
    
    // Test 7: A to D again after an unreachable route
    // Verify state doesn't carry over from previous calls
    std::vector<TownID> route_AD_2 = ds.shortest_route("A", "D");
    assert(!route_AD_2.empty());
    assert(route_AD_2.size() == 4);
    assert(route_AD_2[0] == "A");
    assert(route_AD_2[1] == "B");
    assert(route_AD_2[2] == "C");
    assert(route_AD_2[3] == "D");
    
    std::cout << "shortest_route tests passed" << std::endl;
    return 0;
}

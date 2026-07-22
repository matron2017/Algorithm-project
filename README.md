# Town network

This repository contains a C++ course project for storing town data and
relationships between towns. The program models both a master–vassal tax
hierarchy and an undirected road network.

I implemented the data structures and algorithms in
`Algorithm_project/datastructures.cc` and
`Algorithm_project/datastructures.hh`. The command parser and Qt interface
were provided as part of the course framework.

## Features

- Adding, removing, searching, and sorting towns
- Managing master–vassal relationships
- Calculating tax paths, net tax, and the longest vassal chain
- Adding and removing undirected roads
- Finding an arbitrary route with depth-first search
- Finding a route with the fewest towns using breadth-first search
- Finding shortest routes by road length using Dijkstra's algorithm
- Detecting cycles in the road network

Road lengths are calculated from the Euclidean distance between town
coordinates and rounded down to an integer.

## Build and run

The project requires Qt 5, `qmake`, Make, and a C++17-compatible compiler.

```bash
cd Algorithm_project
qmake program.pro
make
./prg2
```

The program can also execute commands from an example file:

```bash
./prg2 example_inputs/example_input_1.txt
```

## Unfinished operations

trim_road_network is declared but not implemented yet.

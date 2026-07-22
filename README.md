# Town network algorithms

This repository contains a C++ course project for storing town data and
relationships between towns. The program models both a master–vassal tax
hierarchy and an undirected road network.

I implemented the data structures and algorithms in `datastructures.cc` and
`datastructures.hh`. The command parser and Qt interface were provided as part
of the course framework.

## Features

- Adding, removing, searching, and sorting towns
- Managing master–vassal relationships
- Calculating tax paths, net tax, and the longest vassal chain
- Adding and removing undirected roads
- Finding an arbitrary route with depth-first search
- Finding a route with the fewest towns using breadth-first search
- Finding shortest routes by road length using Dijkstra's algorithm
- Detecting cycles in the road network
- Reducing the road network to a minimum spanning forest with Kruskal's
  algorithm

Road lengths are calculated from the Euclidean distance between town
coordinates and rounded down to an integer.

## Project files

- `datastructures.cc` and `datastructures.hh` contain the town data structures,
  taxation logic, and graph algorithms.
- `mainprogram.cc` and `mainprogram.hh` contain the course-provided command
  framework.
- `mainwindow.cc`, `mainwindow.hh`, and `mainwindow.ui` contain the
  course-provided Qt interface.
- `tests/` contains focused regression tests.
- `example_inputs/` contains example command sequences.
- `example-data.txt` and `towns-data.txt` contain sample town data.
- `program.pro` is the qmake build configuration.

## Build and run

The project requires Qt 5, `qmake`, Make, and a C++17-compatible compiler.

```bash
qmake program.pro
make
./prg2
```

The program can also execute commands from an example file:

```bash
./prg2 example_inputs/example_input_1.txt
```

## Tests

Compile and run the shortest-route test with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
  datastructures.cc tests/shortest_route_test.cc \
  -I. -o /tmp/shortest_route_test

/tmp/shortest_route_test
```

Compile and run the road-network trimming test with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
  datastructures.cc tests/trim_road_network_test.cc \
  -I. -o /tmp/trim_road_network_test

/tmp/trim_road_network_test
```

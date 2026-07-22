# Town Network: Data Structures and Graph Algorithms

A C++17 and Qt course project for managing towns, hierarchical taxation
relationships, and a weighted road network.

The project demonstrates hash-based data storage, recursive tree operations,
sorting, graph traversal, route finding, and cycle detection.

**Technologies:** C++17 · Qt 5 · qmake · C++ Standard Library

## Overview

Each town has a unique identifier, name, coordinates, and tax value. Towns can
form master–vassal relationships, creating a hierarchy used to calculate tax
flows and paths.

Towns can also be connected by undirected roads. Each road is weighted by the
Euclidean distance between its endpoints, rounded down to an integer.

## Implemented algorithms

| Capability | Approach | Status |
|---|---|---|
| Arbitrary route between towns | Depth-first search | Implemented |
| Route with the fewest towns | Breadth-first search | Implemented |
| Road-cycle detection | Depth-first search | Implemented |
| Longest vassal path | Recursive tree traversal | Implemented |
| Weighted shortest route | Dijkstra's algorithm | Pending |
| Road-network trimming | — | Pending |

The project also supports:

- Adding, removing, and querying towns
- Alphabetical and distance-based ordering
- Master–vassal relationship management
- Recursive net-tax calculation
- Adding and removing roads
- Querying neighboring towns

## Quick start

### Requirements

- Qt 5 development tools
- `qmake`
- A C++17-compatible compiler
- Make

### Build

```bash
cd Algorithm_project
qmake program.pro
make
```

### Run

Start the application interactively:

```bash
./prg2
```

Alternatively, execute commands from an included example file:

```bash
./prg2 example_inputs/example_input_1.txt
```

## Project scope and authorship

This repository originated as a course project.

My implementation is primarily contained in:

- `Algorithm_project/datastructures.cc`
- `Algorithm_project/datastructures.hh`

These files contain the data structures, town operations, taxation logic, and
graph algorithms.

The following Qt interface and command-processing files were provided as course
scaffolding and are retained to run and visualize the implementation:

- `mainwindow.cc`, `mainwindow.hh`, and `mainwindow.ui`
- `mainprogram.cc` and `mainprogram.hh`

## Repository structure

```text
Algorithm_project/
├── datastructures.cc       Data structures and algorithm implementations
├── datastructures.hh       Public interface and internal data types
├── mainprogram.cc/.hh      Course-provided command framework
├── mainwindow.cc/.hh/.ui   Course-provided Qt user interface
├── example_inputs/         Example command sequences
├── example-data.txt        Small example dataset
├── towns-data.txt          Larger example dataset
└── program.pro             qmake project configuration
```

## Current limitations

The following declared operations currently throw `NotImplemented`:

- `shortest_route`
- `trim_road_network`

`shortest_route` will be implemented using Dijkstra's algorithm in a separate,
tested change. `trim_road_network` remains pending.

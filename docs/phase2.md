# Phase 2 --- Real City Map Integration (Codex Implementation Guide)

## Objective

Replace the fake grid world from Phase 1.5 with a real road network
using OpenStreetMap (OSM). Vehicles should navigate only along valid
roads.

## Deliverables

-   OSM map loader
-   Road graph builder
-   Graph data structures
-   Route planner (A\*)
-   Vehicle route follower
-   Visualization-ready coordinates
-   Unit tests for graph and planner

------------------------------------------------------------------------

# Architecture

    OpenStreetMap (.osm/.pbf)
              |
          OSM Parser
              |
         Road Graph Builder
              |
          Graph Structure
              |
            A* Planner
              |
         Vehicle Route Queue
              |
         Vehicle Simulation

------------------------------------------------------------------------

# Repository Layout

    simulator/
    ├── src/
    │   ├── map/
    │   │   ├── Graph.h
    │   │   ├── Graph.cpp
    │   │   ├── Node.h
    │   │   ├── Edge.h
    │   │   ├── OSMParser.h
    │   │   ├── OSMParser.cpp
    │   │   └── AStar.h
    │   ├── vehicle/
    │   ├── simulation/
    │   └── tests/

------------------------------------------------------------------------

# Tasks

## Task 1 --- Download a city

Choose a small city or district.

Acceptance: - OSM file added to `assets/maps/`.

## Task 2 --- Graph Model

Implement:

``` cpp
struct Node {
    long long id;
    double lat;
    double lon;
};

struct Edge {
    long long from;
    long long to;
    double length;
    double speedLimit;
};

class Graph {
public:
    void addNode(const Node&);
    void addEdge(const Edge&);
};
```

Acceptance: - Graph stores nodes and edges correctly.

## Task 3 --- Parse OSM

Extract: - Road intersections - Drivable roads - Coordinates

Ignore: - Buildings - Parks - Footpaths (initially)

Acceptance: - Parser prints node/edge counts.

## Task 4 --- Implement A\*

Input: - Start node - Goal node

Output: - Ordered list of graph node IDs.

Acceptance: - Shortest route found between two connected nodes.

## Task 5 --- Vehicle Route Following

Each vehicle maintains:

``` cpp
std::vector<long long> route;
size_t currentWaypoint;
```

Vehicle advances toward current waypoint and switches to the next when
close enough.

Acceptance: - Vehicle reaches destination following roads.

## Task 6 --- Telemetry

Extend telemetry with:

``` json
{
  "vehicle_id": 1,
  "lat": 0.0,
  "lon": 0.0,
  "speed": 0.0,
  "current_node": 12345,
  "remaining_waypoints": 42
}
```

Acceptance: - Telemetry reflects graph navigation.

## Task 7 --- Tests

Write tests for: - Graph insertion - Neighbor lookup - A\* correctness -
Route following

Acceptance: - All tests pass.

------------------------------------------------------------------------

# Stretch Goals

-   One-way roads
-   Speed limits
-   Traffic lights
-   Lane metadata
-   Dynamic rerouting
-   Multiple simultaneous vehicles

------------------------------------------------------------------------

# Definition of Done

-   [ ] OSM map loads successfully
-   [ ] Road graph built
-   [ ] A\* implemented
-   [ ] Vehicle follows computed path
-   [ ] Telemetry updated
-   [ ] Tests passing
-   [ ] Code documented

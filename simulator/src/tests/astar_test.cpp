#include <catch2/catch_test_macros.hpp>

#include "AStar.h"
#include "Graph.h"

TEST_CASE("A* finds shortest route", "[astar]") {
  Graph graph;
  graph.addNode(Node{1, 41.3110, 69.2790});
  graph.addNode(Node{2, 41.3110, 69.2800});
  graph.addNode(Node{3, 41.3110, 69.2810});
  graph.addNode(Node{4, 41.3120, 69.2810});

  graph.addEdge(Edge{1, 2, 100.0, 50.0});
  graph.addEdge(Edge{2, 1, 100.0, 50.0});
  graph.addEdge(Edge{2, 3, 100.0, 50.0});
  graph.addEdge(Edge{3, 2, 100.0, 50.0});
  graph.addEdge(Edge{3, 4, 100.0, 50.0});
  graph.addEdge(Edge{4, 3, 100.0, 50.0});

  const auto route = AStar::findPath(graph, 1, 4);
  REQUIRE(route.has_value());
  REQUIRE(route->size() == 4);
  REQUIRE(route->front() == 1);
  REQUIRE(route->back() == 4);
}

TEST_CASE("A* returns empty for disconnected nodes", "[astar]") {
  Graph graph;
  graph.addNode(Node{1, 0.0, 0.0});
  graph.addNode(Node{2, 1.0, 1.0});

  const auto route = AStar::findPath(graph, 1, 2);
  REQUIRE_FALSE(route.has_value());
}

#include <catch2/catch_test_macros.hpp>

#include "Graph.h"

TEST_CASE("Graph stores nodes and edges", "[graph]") {
  Graph graph;

  graph.addNode(Node{1, 41.0, 69.0});
  graph.addNode(Node{2, 41.1, 69.1});
  graph.addEdge(Edge{1, 2, 100.0, 50.0});

  REQUIRE(graph.nodeCount() == 2);
  REQUIRE(graph.edgeCount() == 1);

  auto node = graph.getNode(1);
  REQUIRE(node.has_value());
  REQUIRE(node->lat == 41.0);
  REQUIRE(node->lon == 69.0);
}

TEST_CASE("Graph neighbor lookup", "[graph]") {
  Graph graph;
  graph.addNode(Node{1, 0.0, 0.0});
  graph.addNode(Node{2, 0.0, 0.001});
  graph.addNode(Node{3, 0.0, 0.002});
  graph.addEdge(Edge{1, 2, 10.0, 40.0});
  graph.addEdge(Edge{2, 3, 10.0, 40.0});

  const auto &neighbors = graph.getEdgesFrom(2);
  REQUIRE(neighbors.size() == 1);
  REQUIRE(neighbors.front().to == 3);
}

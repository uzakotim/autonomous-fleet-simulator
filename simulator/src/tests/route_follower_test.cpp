#include <catch2/catch_test_macros.hpp>

#include "AStar.h"
#include "OSMParser.h"
#include "Vehicle.h"

TEST_CASE("OSM parser builds graph from sample map", "[osm]") {
  OSMParser parser;
  REQUIRE(parser.load("../../assets/maps/sample_city.osm"));

  const Graph &graph = parser.getGraph();
  REQUIRE(graph.nodeCount() == 7);
  REQUIRE(graph.edgeCount() > 0);
}

TEST_CASE("Vehicle follows computed route", "[route]") {
  OSMParser parser;
  REQUIRE(parser.load("../../assets/maps/sample_city.osm"));
  const Graph &graph = parser.getGraph();

  const auto route = AStar::findPath(graph, 1, 5);
  REQUIRE(route.has_value());

  Vehicle vehicle(1);
  vehicle.setRoute(*route, graph);

  for (int i = 0; i < 5000; ++i) {
    vehicle.update(0.1, graph);
    if (vehicle.getState().status == "arrived") {
      break;
    }
  }

  const VehicleState state = vehicle.getState();
  REQUIRE(state.status == "arrived");
  REQUIRE(state.remainingWaypoints == 0);
  REQUIRE(state.currentNode == 5);
}

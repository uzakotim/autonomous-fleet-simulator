#pragma once

#include <vector>

#include "Edge.h"
#include "Node.h"

class RoadGraph {

public:
  void addNode(Node node);

  void addEdge(Edge edge);

  Node getNode(long id);

private:
  std::vector<Node> nodes;

  std::vector<Edge> edges;
};
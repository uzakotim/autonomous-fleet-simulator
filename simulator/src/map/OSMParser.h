#pragma once

#include "Graph.h"
#include <string>

class OSMParser {
public:
  bool load(const std::string &filename);

  const Graph &getGraph() const { return graph; }

private:
  bool isDrivableHighway(const char *highwayType) const;
  double parseSpeedLimit(const char *maxspeed) const;

  Graph graph;
};

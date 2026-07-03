#pragma once

#include "RoadGraph.h"
#include <string>

class OSMParser {
public:
  bool load(const std::string &filename);

  const RoadGraph &getGraph() const;

private:
  RoadGraph graph;
};
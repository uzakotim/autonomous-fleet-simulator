#pragma once

#include <optional>
#include <unordered_map>
#include <vector>

#include "Edge.h"
#include "Node.h"

class Graph {
public:
  void addNode(const Node &node);
  void addEdge(const Edge &edge);

  std::optional<Node> getNode(long long id) const;
  const std::vector<Edge> &getEdgesFrom(long long nodeId) const;
  const std::unordered_map<long long, Node> &getNodes() const { return nodes; }
  size_t nodeCount() const { return nodes.size(); }
  size_t edgeCount() const { return edgeCount_; }

private:
  std::unordered_map<long long, Node> nodes;
  std::unordered_map<long long, std::vector<Edge>> adjacency;
  size_t edgeCount_ = 0;
};

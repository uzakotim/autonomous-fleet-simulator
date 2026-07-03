#include "Graph.h"

void Graph::addNode(const Node &node) { nodes[node.id] = node; }

void Graph::addEdge(const Edge &edge) {
  adjacency[edge.from].push_back(edge);
  edgeCount_++;
}

std::optional<Node> Graph::getNode(long long id) const {
  auto it = nodes.find(id);
  if (it == nodes.end()) {
    return std::nullopt;
  }
  return it->second;
}

const std::vector<Edge> &Graph::getEdgesFrom(long long nodeId) const {
  static const std::vector<Edge> empty;
  auto it = adjacency.find(nodeId);
  if (it == adjacency.end()) {
    return empty;
  }
  return it->second;
}

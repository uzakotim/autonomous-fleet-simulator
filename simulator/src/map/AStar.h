#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
#include <optional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "GeoUtils.h"
#include "Graph.h"

class AStar {
public:
  static std::optional<std::vector<long long>>
  findPath(const Graph &graph, long long startId, long long goalId) {
    auto startNode = graph.getNode(startId);
    auto goalNode = graph.getNode(goalId);
    if (!startNode || !goalNode) {
      return std::nullopt;
    }

    struct QueueEntry {
      double fScore;
      long long nodeId;
    };

    auto cmp = [](const QueueEntry &a, const QueueEntry &b) {
      return a.fScore > b.fScore;
    };

    std::priority_queue<QueueEntry, std::vector<QueueEntry>, decltype(cmp)> open(
        cmp);

    std::unordered_map<long long, double> gScore;
    std::unordered_map<long long, long long> cameFrom;

    gScore[startId] = 0.0;
    open.push({heuristic(*startNode, *goalNode), startId});

    while (!open.empty()) {
      const long long current = open.top().nodeId;
      open.pop();

      if (current == goalId) {
        return reconstructPath(cameFrom, current);
      }

      for (const Edge &edge : graph.getEdgesFrom(current)) {
        const double tentativeG = gScore[current] + edge.length;
        const auto existing = gScore.find(edge.to);
        if (existing != gScore.end() && tentativeG >= existing->second) {
          continue;
        }

        cameFrom[edge.to] = current;
        gScore[edge.to] = tentativeG;

        auto neighbor = graph.getNode(edge.to);
        if (!neighbor) {
          continue;
        }

        const double fScore = tentativeG + heuristic(*neighbor, *goalNode);
        open.push({fScore, edge.to});
      }
    }

    return std::nullopt;
  }

private:
  static double heuristic(const Node &from, const Node &to) {
    return haversineDistance(from.lat, from.lon, to.lat, to.lon);
  }

  static std::vector<long long>
  reconstructPath(const std::unordered_map<long long, long long> &cameFrom,
                    long long current) {
    std::vector<long long> path;
    path.push_back(current);
    while (cameFrom.contains(current)) {
      current = cameFrom.at(current);
      path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }
};

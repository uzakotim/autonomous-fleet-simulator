#include "AStar.h"
#include "FleetManager.h"
#include "Logger.h"
#include "OSMParser.h"
#include "network/UdpClient.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

namespace {

std::vector<long long> collectNodeIds(const Graph &graph) {
  std::vector<long long> ids;
  ids.reserve(graph.getNodes().size());
  for (const auto &[id, _] : graph.getNodes()) {
    ids.push_back(id);
  }
  return ids;
}

} // namespace

int main(int argc, char **argv) {

  UdpClient udp("127.0.0.1", 5005);

  const std::string mapPath =
      argc > 1 ? argv[1] : "assets/maps/sample_city.osm";

  OSMParser parser;
  if (!parser.load(mapPath)) {
    return 1;
  }

  const Graph &graph = parser.getGraph();
  const auto nodeIds = collectNodeIds(graph);
  if (nodeIds.size() < 2) {
    std::cerr << "Map graph needs at least two nodes\n";
    return 1;
  }

  const long long startId = nodeIds.front();
  const long long goalId = nodeIds.back();

  auto route = AStar::findPath(graph, startId, goalId);
  if (!route) {
    std::cerr << "No route found between nodes " << startId << " and " << goalId
              << '\n';
    return 1;
  }

  std::cout << "Planned route with " << route->size() << " waypoints\n";

  FleetManager fleet;

  UdpCommandListener commandListener(

      5006,

      [&fleet](const std::string &message)

      { fleet.handleCommand(message); }

  );

  commandListener.start();

  Vehicle car(1);
  car.setRoute(*route, graph);
  fleet.addVehicle(car);

  Logger logger;

  while (true) {
    fleet.update(0.1, graph);
    const auto &vehicles = fleet.getVehicles();
    for (auto &vehicle : vehicles) {
      const VehicleState state = vehicle.getState();
      logger.log(state);
      udp.sendTelemetry(state);

      std::cout << "Vehicle " << state.id << " lat=" << state.lat
                << " lon=" << state.lon << " node=" << state.currentNode
                << " remaining=" << state.remainingWaypoints
                << " status=" << state.status << '\n';

      if (state.status == "arrived") {
        std::cout << "Vehicle reached destination\n";
        commandListener.stop();
        return 0;
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

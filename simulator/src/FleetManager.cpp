#include "FleetManager.h"
#include "CollisionManager.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void FleetManager::addVehicle(Vehicle vehicle) { vehicles.push_back(vehicle); }

void FleetManager::update(double dt, const Graph &graph) {

  for (auto &vehicle : vehicles) {
    vehicle.update(dt, graph);
  }

  CollisionManager detector;

  for (int i = 0; i < static_cast<int>(vehicles.size()); i++) {

    for (int j = i + 1; j < static_cast<int>(vehicles.size()); j++) {

      if (detector.checkCollision(vehicles[i].getState(),
                                  vehicles[j].getState())) {

        std::cout << "COLLISION WARNING" << std::endl;
        vehicles[i].stop();

        vehicles[j].stop();
      }
    }
  }
}
const std::vector<Vehicle> &FleetManager::getVehicles() const {
  return vehicles;
}

void FleetManager::handleCommand(const std::string &message) {
  json cmd = json::parse(message);

  std::string command = cmd["command"];

  std::cout << "Received command: " << command << std::endl;

  if (command == "stop") {
    std::cout << "Stop requested\n";
  }

  if (command == "resume") {
    std::cout << "Resume requested\n";
  }

  if (command == "reroute") {
    std::cout << "Destination " << cmd["latitude"] << ", " << cmd["longitude"]
              << std::endl;
  }
}
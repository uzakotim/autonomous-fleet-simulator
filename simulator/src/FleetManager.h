#pragma once

#include "./map/Graph.h"
#include "Vehicle.h"
#include "network/UdpCommandListener.h"
#include <vector>

class FleetManager {

public:
  void addVehicle(Vehicle vehicle);
  void update(double dt, const Graph &graph);
  const std::vector<Vehicle> &getVehicles() const;
  void handleCommand(const std::string &message);

private:
  std::vector<Vehicle> vehicles;
};

#pragma once

#include "./map/Graph.h"
#include "Vehicle.h"
#include <vector>

class FleetManager {

public:
  void addVehicle(Vehicle vehicle);

  void update(double dt, const Graph &graph);
  std::vector<Vehicle> getVehicles();

private:
  std::vector<Vehicle> vehicles;
};

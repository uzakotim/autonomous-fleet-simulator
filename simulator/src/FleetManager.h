#pragma once

#include "Vehicle.h"
#include <vector>

class FleetManager {

public:
  void addVehicle(Vehicle vehicle);

  void update(double dt);
  std::vector<Vehicle> getVehicles();

private:
  std::vector<Vehicle> vehicles;
};
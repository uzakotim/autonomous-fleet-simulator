#include "FleetManager.h"
#include "CollisionManager.h"
#include <iostream>

void FleetManager::addVehicle(Vehicle vehicle) { vehicles.push_back(vehicle); }

void FleetManager::update(double dt) {

  for (auto &vehicle : vehicles) {
    vehicle.update(dt);
  }

  CollisionManager detector;

  for (int i = 0; i < vehicles.size(); i++) {

    for (int j = i + 1; j < vehicles.size(); j++) {

      if (detector.checkCollision(vehicles[i].getState(),
                                  vehicles[j].getState())) {

        std::cout << "COLLISION WARNING" << std::endl;
        vehicles[i].stop();

        vehicles[j].stop();
      }
    }
  }
}
std::vector<Vehicle> FleetManager::getVehicles() { return vehicles; }

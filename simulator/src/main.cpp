#include "FleetManager.h"
#include "Logger.h"
#include <chrono>
#include <iostream>
#include <thread>

int main() {

  FleetManager fleet;

  Vehicle car1(1);
  Vehicle car2(2);
  Vehicle car3(3);
  car1.setDestination({100, 100});
  car2.setDestination({-100, 50});
  car3.setDestination({50, -100});

  car1.setInitialPosition({0, 0});
  car2.setInitialPosition({20, 20});
  car3.setInitialPosition({-20, -20});

  fleet.addVehicle(car1);
  fleet.addVehicle(car2);
  fleet.addVehicle(car3);

  Logger logger;

  while (true) {

    fleet.update(0.1);

    for (auto vehicle : fleet.getVehicles()) {

      VehicleState state = vehicle.getState();
      logger.log(state);
      auto sensorData = vehicle.sensor.readSensors(state.position);

      std::cout << "Vehicle " << state.id

                << " Position: " << state.position.x << ", " << state.position.y
                << std::endl;

      std::cout << "Sensor " << sensorData.gps_x << ", " << sensorData.gps_y
                << std::endl;
      std::cout << "Obstacle " << sensorData.obstacle_distance << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return 0;
}
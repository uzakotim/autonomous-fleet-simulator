#include <chrono>
#include <iostream>
#include <thread>

#include "Logger.h"

int main() {

  Vehicle car(1);
  Logger logger;

  while (true) {

    car.update(0.1);

    auto state = car.getState();

    logger.log(state);

    auto sensorData = car.sensor.readSensors(state.position);

    std::cout << "Vehicle " << state.id

              << " Position: " << state.position.x << ", " << state.position.y
              << std::endl;

    std::cout << "Sensor " << sensorData.gps_x << ", " << sensorData.gps_y
              << std::endl;
    std::cout << "Obstacle " << sensorData.obstacle_distance << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
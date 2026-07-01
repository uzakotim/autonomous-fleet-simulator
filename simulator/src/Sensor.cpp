#include "Sensor.h"

#include <cstdlib>

SensorData Sensor::readSensors(Point position) {

  SensorData data;

  data.gps_x = position.x;

  data.gps_y = position.y;

  data.obstacle_distance = 5 + rand() % 100;

  return data;
}
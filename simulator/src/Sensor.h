#pragma once
#include "Point.h"

struct SensorData {

  double gps_x;

  double gps_y;

  double obstacle_distance;
};

class Sensor {
public:
  SensorData readSensors(Point position);
};

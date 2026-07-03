#pragma once

#include "Point.h"
#include "Sensor.h"
#include <string>
#include <vector>

struct VehicleState {
  int id;

  Point position;

  double lat;
  double lon;

  double speed;

  double heading;

  std::string status;

  long long currentNode = -1;
  size_t remainingWaypoints = 0;
};

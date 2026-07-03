#pragma once

#include "Graph.h"
#include "Point.h"
#include "Sensor.h"
#include "State.h"

#include <vector>

class Vehicle {

public:
  Vehicle(int id);
  Sensor sensor;
  void update(double dt, const Graph &graph);

  VehicleState getState() const;
  void setRoute(const std::vector<long long> &route, const Graph &graph);
  void setInitialPosition(double lat, double lon);
  void stop();

private:
  void syncPositionFromLatLon();
  void refreshWaypointTarget(const Graph &graph);
  bool hasReachedCurrentWaypoint() const;

  VehicleState state;
  std::vector<long long> route;
  size_t currentWaypoint = 0;
  double targetLat = 0.0;
  double targetLon = 0.0;
  bool emergencyStop = false;
  static constexpr double kWaypointReachMeters = 8.0;
};

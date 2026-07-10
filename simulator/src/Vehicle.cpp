#include "Vehicle.h"

#include "GeoUtils.h"

#include <cmath>

Vehicle::Vehicle(int id) {
  state.id = id;
  state.position = {0.0, 0.0};
  state.lat = 0.0;
  state.lon = 0.0;
  state.speed = 100.0;
  state.heading = 0.0;
  state.status = "idle";
  emergencyStop = false;
}

void Vehicle::setRoute(const std::vector<long long> &newRoute,
                       const Graph &graph) {
  route = newRoute;
  currentWaypoint = route.size() > 1 ? 1 : 0;

  if (!route.empty()) {
    if (auto node = graph.getNode(route.front())) {
      state.lat = node->lat;
      state.lon = node->lon;
      state.currentNode = route.front();
      syncPositionFromLatLon();
    }
  }

  refreshWaypointTarget(graph);
  state.remainingWaypoints =
      route.size() > currentWaypoint ? route.size() - currentWaypoint : 0;
  state.status = route.empty() ? "idle" : "moving";
}

void Vehicle::setInitialPosition(double lat, double lon) {
  state.lat = lat;
  state.lon = lon;
  syncPositionFromLatLon();
}

void Vehicle::syncPositionFromLatLon() {
  state.position.x = state.lon;
  state.position.y = state.lat;
}

void Vehicle::refreshWaypointTarget(const Graph &graph) {
  if (currentWaypoint >= route.size()) {
    return;
  }

  if (auto node = graph.getNode(route[currentWaypoint])) {
    targetLat = node->lat;
    targetLon = node->lon;
    state.currentNode = route[currentWaypoint];
  }
}

bool Vehicle::hasReachedCurrentWaypoint() const {
  return haversineDistance(state.lat, state.lon, targetLat, targetLon) <=
         kWaypointReachMeters;
}

void Vehicle::update(double dt, const Graph &graph) {
  if (emergencyStop) {
    state.speed = 0.0;
    state.status = "stopped";
    return;
  }

  if (route.empty() || currentWaypoint >= route.size()) {
    state.speed = 0.0;
    state.status = "arrived";
    state.remainingWaypoints = 0;
    return;
  }

  if (hasReachedCurrentWaypoint()) {
    ++currentWaypoint;
    state.remainingWaypoints =
        route.size() > currentWaypoint ? route.size() - currentWaypoint : 0;

    if (currentWaypoint >= route.size()) {
      state.speed = 0.0;
      state.status = "arrived";
      return;
    }

    refreshWaypointTarget(graph);
  }

  state.heading = bearingDegrees(state.lat, state.lon, targetLat, targetLon);

  const double speedMs = state.speed * 1000.0 / 3600.0;
  const double stepMeters = speedMs * dt;
  const double totalDistance =
      haversineDistance(state.lat, state.lon, targetLat, targetLon);

  if (totalDistance <= stepMeters) {
    state.lat = targetLat;
    state.lon = targetLon;
  } else {
    const double fraction = stepMeters / totalDistance;
    state.lat += (targetLat - state.lat) * fraction;
    state.lon += (targetLon - state.lon) * fraction;
  }

  syncPositionFromLatLon();
  state.status = "moving";
  state.battery -= 0.00001;
  if (state.battery < 0) {
    state.battery = 0;
  }
}

void Vehicle::stop() {
  state.speed = 0.0;
  state.status = "stopped";
  emergencyStop = true;
}

VehicleState Vehicle::getState() const { return state; }

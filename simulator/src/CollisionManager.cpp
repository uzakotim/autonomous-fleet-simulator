#include "CollisionManager.h"

#include <cmath>

bool CollisionManager::checkCollision(VehicleState a, VehicleState b) {

  double dx = a.position.x - b.position.x;

  double dy = a.position.y - b.position.y;

  double distance = sqrt(dx * dx + dy * dy);

  return distance < 5.0;
}
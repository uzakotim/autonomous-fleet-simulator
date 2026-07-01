#pragma once

#include "Vehicle.h"

class CollisionManager {

public:
  bool checkCollision(VehicleState a, VehicleState b);
};
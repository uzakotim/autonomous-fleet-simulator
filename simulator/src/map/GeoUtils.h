#pragma once

#include <cmath>

constexpr double kEarthRadiusMeters = 6371000.0;

inline double toRadians(double degrees) { return degrees * M_PI / 180.0; }

inline double toDegrees(double radians) { return radians * 180.0 / M_PI; }

inline double haversineDistance(double lat1, double lon1, double lat2,
                                double lon2) {
  const double dLat = toRadians(lat2 - lat1);
  const double dLon = toRadians(lon2 - lon1);
  const double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
                   std::cos(toRadians(lat1)) * std::cos(toRadians(lat2)) *
                       std::sin(dLon / 2) * std::sin(dLon / 2);
  const double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
  return kEarthRadiusMeters * c;
}

inline double bearingDegrees(double lat1, double lon1, double lat2,
                             double lon2) {
  const double lat1Rad = toRadians(lat1);
  const double lat2Rad = toRadians(lat2);
  const double dLon = toRadians(lon2 - lon1);
  const double y = std::sin(dLon) * std::cos(lat2Rad);
  const double x = std::cos(lat1Rad) * std::sin(lat2Rad) -
                   std::sin(lat1Rad) * std::cos(lat2Rad) * std::cos(dLon);
  return std::fmod(toDegrees(std::atan2(y, x)) + 360.0, 360.0);
}

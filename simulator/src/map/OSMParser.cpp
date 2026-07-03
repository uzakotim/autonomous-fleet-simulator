#include "OSMParser.h"

#include "GeoUtils.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <tinyxml2.h>

using namespace tinyxml2;

namespace {

constexpr double kDefaultSpeedLimitKmh = 50.0;

bool parseLongLong(const char *value, long long &out) {
  if (value == nullptr) {
    return false;
  }
  try {
    out = std::stoll(value);
    return true;
  } catch (...) {
    return false;
  }
}

bool parseDouble(const char *value, double &out) {
  if (value == nullptr) {
    return false;
  }
  try {
    out = std::stod(value);
    return true;
  } catch (...) {
    return false;
  }
}

const char *findTagValue(XMLElement *element, const char *key) {
  for (XMLElement *tag = element->FirstChildElement("tag"); tag != nullptr;
       tag = tag->NextSiblingElement("tag")) {
    const char *k = tag->Attribute("k");
    if (k != nullptr && std::string(k) == key) {
      return tag->Attribute("v");
    }
  }
  return nullptr;
}

} // namespace

bool OSMParser::isDrivableHighway(const char *highwayType) const {
  if (highwayType == nullptr) {
    return false;
  }

  static const char *kDrivableTypes[] = {
      "motorway",      "trunk",       "primary",     "secondary",
      "tertiary",      "unclassified", "residential", "living_street",
      "service",       "motorway_link", "trunk_link", "primary_link",
      "secondary_link", "tertiary_link"};

  for (const char *type : kDrivableTypes) {
    if (std::string(highwayType) == type) {
      return true;
    }
  }
  return false;
}

double OSMParser::parseSpeedLimit(const char *maxspeed) const {
  if (maxspeed == nullptr) {
    return kDefaultSpeedLimitKmh;
  }

  std::string value(maxspeed);
  if (value.ends_with(" mph")) {
    value = value.substr(0, value.size() - 4);
    try {
      return std::stod(value) * 1.60934;
    } catch (...) {
      return kDefaultSpeedLimitKmh;
    }
  }

  try {
    return std::stod(value);
  } catch (...) {
    return kDefaultSpeedLimitKmh;
  }
}

bool OSMParser::load(const std::string &filename) {
  XMLDocument doc;
  if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
    std::cerr << "Failed to load map: " << filename << '\n';
    return false;
  }

  XMLElement *osm = doc.FirstChildElement("osm");
  if (osm == nullptr) {
    std::cerr << "Invalid OSM file: missing root <osm> element\n";
    return false;
  }

  std::unordered_map<long long, Node> parsedNodes;

  for (XMLElement *nodeElement = osm->FirstChildElement("node");
       nodeElement != nullptr; nodeElement = nodeElement->NextSiblingElement("node")) {
    long long id = 0;
    double lat = 0.0;
    double lon = 0.0;
    if (!parseLongLong(nodeElement->Attribute("id"), id) ||
        !parseDouble(nodeElement->Attribute("lat"), lat) ||
        !parseDouble(nodeElement->Attribute("lon"), lon)) {
      continue;
    }

    parsedNodes[id] = Node{id, lat, lon};
  }

  for (XMLElement *wayElement = osm->FirstChildElement("way");
       wayElement != nullptr; wayElement = wayElement->NextSiblingElement("way")) {
    const char *highwayType = findTagValue(wayElement, "highway");
    if (!isDrivableHighway(highwayType)) {
      continue;
    }

    const double speedLimit = parseSpeedLimit(findTagValue(wayElement, "maxspeed"));

    std::vector<long long> nodeRefs;
    for (XMLElement *nd = wayElement->FirstChildElement("nd"); nd != nullptr;
         nd = nd->NextSiblingElement("nd")) {
      long long ref = 0;
      if (parseLongLong(nd->Attribute("ref"), ref)) {
        nodeRefs.push_back(ref);
      }
    }

    for (size_t i = 1; i < nodeRefs.size(); ++i) {
      const long long fromId = nodeRefs[i - 1];
      const long long toId = nodeRefs[i];

      const auto fromIt = parsedNodes.find(fromId);
      const auto toIt = parsedNodes.find(toId);
      if (fromIt == parsedNodes.end() || toIt == parsedNodes.end()) {
        continue;
      }

      graph.addNode(fromIt->second);
      graph.addNode(toIt->second);

      const double length =
          haversineDistance(fromIt->second.lat, fromIt->second.lon, toIt->second.lat,
                            toIt->second.lon);

      graph.addEdge(Edge{fromId, toId, length, speedLimit});
      graph.addEdge(Edge{toId, fromId, length, speedLimit});
    }
  }

  std::cout << "Map loaded successfully\n";
  std::cout << "Nodes: " << graph.nodeCount() << '\n';
  std::cout << "Edges: " << graph.edgeCount() << '\n';
  return graph.nodeCount() > 0;
}

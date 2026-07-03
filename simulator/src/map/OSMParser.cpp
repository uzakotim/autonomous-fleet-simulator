#include "OSMParser.h"

#include <iostream>
#include <tinyxml2.h>

using namespace tinyxml2;

bool OSMParser::load(const std::string &filename) {
  XMLDocument doc;

  auto result = doc.LoadFile(filename.c_str());

  if (result != XML_SUCCESS) {
    std::cout << "Failed to load map\n";
    return false;
  }

  std::cout << "Map loaded successfully\n";

  return true;
}
#pragma once
#include "String.h"
#include "structs.h"

void loadSize(Map *m);
void loadMap(Map *m);
void loadCities(Map *m);
String findCityName(int x, int y, Map *m);
bool isCityNameFound(int x, int y, Map *m, Citycoords *currCityCords);
void setBegAndEnd(Citycoords *currCityCords, Map *m);
void loadAirConnections(Map *m);
bool checkIfIsRoad(int x, int y, bool **visited, Path *p, City *currCity, int dist, Map *m);
void loadLandNeighbours(Map *m, String &name, bool **visited);
bool isConectedToRoads(Map *m, int x, int y);
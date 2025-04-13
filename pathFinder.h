#pragma once
#include "String.h"
#include "structs.h"
#define DIST_ONLY 0
#define DIST_AND_PATH 1

void processTask(Map *map);

int findCityPos(PriorityQueue *pq, String &name, int pos);
void displayPath(Map *map,PriorityQueue *pq, int destPos, int dist);
void dijkstra(Map *map, String &from, String &to, int type);
#pragma once
#include "String.hpp"
#define NOT_FOUND -1

struct Neighbour
{
    int dist;
    String name;
    Neighbour *next = nullptr;
};

struct City
{
    Neighbour *neighbours = nullptr;
    City *next = nullptr;
    int x;
    int y;
    String name;
};

struct HashTable
{
    City *city = nullptr;
};

struct Map
{
    int width;
    int height;
    char **map;
    HashTable *cities;
    int cityCounter = 0;
};

struct Path // do BFS przy szukaniu sąsiadów
{
    int x;
    int y;
    Path *next = nullptr;
};

struct PriorityQueue
{
    String name;
    int dist = 1000000000;
    bool visited = false;
    PriorityQueue *prev = nullptr;
};

struct Citycoords // do znaleźenia nazwy miasta na mapie
{
    int beg = NOT_FOUND;
    int end = NOT_FOUND;
    int cityNameYPos = NOT_FOUND;
};

void addCityToHashTable(City *c, Map *m);
void addNeighbour(String &from, String &to, int dist, Map *m);
bool isInsideMap(Map *m, int x, int y);

int hashify(String &name, Map *m);
City *getCity(String &name, Map *m);

void deleteCityList(City **head);
void deleteNeighboursList(Neighbour **head);

void addNewNodeToPath(Path *head, Path *newNode);
void clearPath(Path **head);
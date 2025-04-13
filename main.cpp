#include "String.h"
#include "loader.h"
#include "structs.h"
#include "pathFinder.h"

using namespace std;

int main()
{
    Map map;
    loadSize(&map);
    map.map = new char *[map.height];
    for (int i = 0; i < map.height; i++)
    {
        map.map[i] = new char[map.width];
    }
    loadMap(&map);
    map.cities = new HashTable[map.cityCounter];
    loadCities(&map);
    loadAirConnections(&map);
    processTask(&map);

    for (int i = 0; i < map.height; i++)
    {
        delete[] map.map[i];
    }
    delete[] map.map;

    for (int i = 0; i < map.cityCounter; i++)
    {
        deleteCityList(&(map.cities[i].city));
    }
    delete[] map.cities;
    return 0;
}
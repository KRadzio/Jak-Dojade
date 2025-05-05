#include "loader.hpp"
#define CITY_SIGN '*'
#define ROAD_SIGN '#'

void loadSize(Map *m)
{
    String currLine;
    std::cin >> currLine;
    String w = currLine.subStr(0, ' ');
    String h = currLine.subStr(w.getLength() + 1, '\0');
    m->width = w.stoi();
    m->height = h.stoi();
}

void loadMap(Map *m)
{
    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width + 1; j++)
        {
            char input = (char)getchar();
            if (input == CITY_SIGN)
                m->cityCounter++;
            if (isspace(input) == 0)
                m->map[i][j] = input;
        }
    }
}

bool isConectedToRoads(Map *m, int x, int y)
{
    int connections = 0;
    if (isInsideMap(m, x + 1, y) && (m->map[y][x + 1] == ROAD_SIGN || m->map[y][x + 1] == CITY_SIGN))
        connections++;
    if (isInsideMap(m, x, y + 1) && (m->map[y + 1][x] == ROAD_SIGN || m->map[y + 1][x] == CITY_SIGN))
        connections++;
    if (isInsideMap(m, x - 1, y) && (m->map[y][x - 1] == ROAD_SIGN || m->map[y][x - 1] == CITY_SIGN))
        connections++;
    if (isInsideMap(m, x, y - 1) && (m->map[y - 1][x] == ROAD_SIGN || m->map[y - 1][x] == CITY_SIGN))
        connections++;
    if (connections == 0)
        return false;
    else
        return true;
}

void loadCities(Map *m)
{
    int foundCities = 0;
    bool **visited;
    visited = new bool *[m->height];
    for (int i = 0; i < m->height; i++)
    {
        visited[i] = new bool[m->width];
    }
    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            if (m->map[i][j] == CITY_SIGN)
            {
                foundCities++;
                String name = findCityName(j, i, m);
                City *c = new City;
                c->name = name;
                c->x = j;
                c->y = i;
                addCityToHashTable(c, m);
                if (isConectedToRoads(m, j, i))
                    loadLandNeighbours(m, name, visited);
                if (foundCities == m->cityCounter)
                {
                    for (int k = 0; k < m->height; k++)
                    {
                        delete[] visited[k];
                    }
                    delete[] visited;
                    return;
                }
            }
        }
    }
}

bool isCityNameFound(int x, int y, Map *m, Citycoords *currCityCords)
{
    if (isInsideMap(m, x, y) && m->map[y][x] >= 'A' && m->map[y][x] <= 'Z')
    {
        currCityCords->beg = x;
        currCityCords->end = x;
        currCityCords->cityNameYPos = y;
        return true;
    }
    return false;
}

String findCityName(int x, int y, Map *m)
{
    Citycoords currCityCords;
    if (isCityNameFound(x + 1, y, m, &currCityCords)) // prawa
        setBegAndEnd(&currCityCords, m);
    else if (isCityNameFound(x, y + 1, m, &currCityCords)) // dół
        setBegAndEnd(&currCityCords, m);
    else if (isCityNameFound(x - 1, y, m, &currCityCords)) // lewa
        setBegAndEnd(&currCityCords, m);
    else if (isCityNameFound(x, y - 1, m, &currCityCords)) // góra
        setBegAndEnd(&currCityCords, m);
    else if (isCityNameFound(x + 1, y + 1, m, &currCityCords)) // prawa-dół
        setBegAndEnd(&currCityCords, m);
    else if (isCityNameFound(x - 1, y + 1, m, &currCityCords)) // lewa-dół
        setBegAndEnd(&currCityCords, m);
    else if (isCityNameFound(x - 1, y - 1, m, &currCityCords)) // lewa-góra
        setBegAndEnd(&currCityCords, m);
    else if (isCityNameFound(x + 1, y - 1, m, &currCityCords)) // prawa-góra
        setBegAndEnd(&currCityCords, m);
    String name(currCityCords.end - currCityCords.beg + 1);
    for (int i = 0; i < name.getLength(); i++)
    {
        name.setTabIndex(i, m->map[currCityCords.cityNameYPos][i + currCityCords.beg]);
    }
    return name;
}

void setBegAndEnd(Citycoords *currCityCords, Map *m)
{
    int i = currCityCords->beg;
    while (m->map[currCityCords->cityNameYPos][i] >= '0' && m->map[currCityCords->cityNameYPos][i] <= 'Z')
    {
        currCityCords->end = i;
        i++;
    }
    int j = currCityCords->beg;
    while (m->map[currCityCords->cityNameYPos][j] >= '0' && m->map[currCityCords->cityNameYPos][j] <= 'Z')
    {
        currCityCords->beg = j;
        j--;
    }
}

void loadAirConnections(Map *m)
{
    String currLine;
    std::cin >> currLine;
    int airConCounter = currLine.stoi();
    for (int i = 0; i < airConCounter; i++)
    {
        std::cin >> currLine;
        int pos = 0;
        String from = currLine.subStr(pos, ' ');
        pos += from.getLength() + 1;
        String to = currLine.subStr(pos, ' ');
        pos += to.getLength() + 1;
        int dist = currLine.subStr(pos, '\0').stoi();
        addNeighbour(from, to, dist, m);
    }
}

bool checkIfIsRoad(int x, int y, bool **visited, Path *p, City *currCity, int dist, Map *m)
{
    if (isInsideMap(m, x, y) && (m->map[y][x] == ROAD_SIGN || m->map[y][x] == CITY_SIGN) && visited[y][x] == false)
    {
        if (m->map[y][x] == ROAD_SIGN) // droga
        {
            Path *newNode = new Path;
            newNode->x = x;
            newNode->y = y;
            visited[y][x] = true;
            addNewNodeToPath(p, newNode);
            return true;
        }
        else // miasto
        {
            String neigbourName = findCityName(x, y, m);
            addNeighbour(currCity->name, neigbourName, dist + 1, m);
            return false;
        }
    }
    return false;
}

void loadLandNeighbours(Map *m, String &name, bool **visited)
{
    City *currCity = getCity(name, m);
    int dist = 0;
    Path *beg = new Path; // kolejka pól do odwiedzania
    beg->x = currCity->x;
    beg->y = currCity->y;
    int nodesLeftInLayer = 1;
    int nodesLeftInNextLayer = 0;
    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            visited[i][j] = false;
        }
    }
    visited[beg->y][beg->x] = true;
    Path *currNode = beg;
    while (currNode != nullptr)
    {
        if (checkIfIsRoad(currNode->x + 1, currNode->y, visited, currNode, currCity, dist, m)) // prawa
            nodesLeftInNextLayer++;
        if (checkIfIsRoad(currNode->x, currNode->y + 1, visited, currNode, currCity, dist, m)) // dół
            nodesLeftInNextLayer++;
        if (checkIfIsRoad(currNode->x - 1, currNode->y, visited, currNode, currCity, dist, m)) // lewa
            nodesLeftInNextLayer++;
        if (checkIfIsRoad(currNode->x, currNode->y - 1, visited, currNode, currCity, dist, m)) // góra
            nodesLeftInNextLayer++;
        nodesLeftInLayer--;
        if (nodesLeftInLayer == 0)
        {
            nodesLeftInLayer = nodesLeftInNextLayer;
            nodesLeftInNextLayer = 0;
            dist++;
        }
        currNode = currNode->next;
    }
    clearPath(&beg);
}

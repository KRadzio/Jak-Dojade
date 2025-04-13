#include "pathFinder.h"

void processTask(Map *map)
{
    String currLine;
    std::cin >> currLine;
    int tasksAmount = currLine.stoi();
    for (int i = 0; i < tasksAmount; i++)
    {
        std::cin >> currLine;
        int pos = 0;
        String from = currLine.subStr(pos, ' ');
        pos += from.getLength() + 1;
        String to = currLine.subStr(pos, ' ');
        pos += to.getLength() + 1;
        int type = currLine.subStr(pos, '\0').stoi();
        dijkstra(map, from, to, type);
    }
}

int findCityPos(PriorityQueue *pq, String &name, int pos)
{
    for (int i = 0; i < pos; i++)
    {
        if (pq[i].name == name)
        {
            return i;
        }
    }
    return NOT_FOUND;
}

void dijkstra(Map *map, String &from, String &to, int type)
{
    City *currCity = getCity(from, map);
    City *destination = getCity(to, map);
    int dist = 0;
    PriorityQueue *pq = new PriorityQueue[map->cityCounter];
    pq[0].name = from;
    pq[0].dist = 0;
    pq[0].visited = true;
    int pos = 1;
    while (currCity != destination)
    {
        Neighbour *currNeighbour = currCity->neighbours;
        Neighbour closestNeighbour;
        if (currNeighbour != nullptr)
        {
            closestNeighbour.name = currNeighbour->name;
            closestNeighbour.dist = 1000000000;
        }
        int currCityPos = findCityPos(pq, currCity->name, pos);
        while (currNeighbour != nullptr)
        {
            int currNeigbourPos = findCityPos(pq, currNeighbour->name, pos);
            bool isAlreadyInQ = false;
            if (currNeigbourPos != NOT_FOUND) // jeżeli już jest
                isAlreadyInQ = true;

            if (isAlreadyInQ == false) // dodawanie na koniec tablicy
            {
                pq[pos].name = currNeighbour->name;
                pq[pos].dist = currNeighbour->dist + dist;
                pq[pos].prev = &pq[currCityPos];
                currNeigbourPos = pos;
                isAlreadyInQ = true;
                pos++;
            }

            if (pq[currNeigbourPos].dist > currNeighbour->dist + dist) // aktualizowanie dystansów
            {
                pq[currNeigbourPos].dist = currNeighbour->dist + dist;
                pq[currNeigbourPos].prev = &pq[currCityPos];
            }

            if (currNeighbour->dist + dist < closestNeighbour.dist + dist) // wyszukanie najbliższego sąsiada
            {
                if (pq[currNeigbourPos].visited == false)
                {
                    closestNeighbour = *currNeighbour;
                }
            }
            currNeighbour = currNeighbour->next;
        }
        int closestNeigbourPos = findCityPos(pq, closestNeighbour.name, pos);
        dist = pq[closestNeigbourPos].dist;
        currCity = getCity(closestNeighbour.name, map); // przenoszenie do kolejnego miasta

        if (pq[currCityPos].visited == false)
            pq[currCityPos].visited = true;
    }
    int destPos = findCityPos(pq, destination->name, pos);
    dist = pq[destPos].dist;
    if (type == DIST_ONLY)
        std::cout << dist << std::endl;
    else
    {
        displayPath(map, pq, destPos, dist);
    }
    delete[] pq;
}

void displayPath(Map *map, PriorityQueue *pq, int destPos, int dist)
{
    String *path = new String[map->cityCounter];
    int pathPos = 0;
    PriorityQueue *currCityInQ = &pq[destPos];
    while (currCityInQ->prev != nullptr)
    {
        if (currCityInQ != &pq[destPos])
        {
            path[pathPos] = currCityInQ->name;
            pathPos++;
        }
        currCityInQ = currCityInQ->prev;
    }
    std::cout << dist << " ";
    for (int i = pathPos - 1; i >= 0; i--)
    {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
    delete[] path;
}
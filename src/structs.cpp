#include "structs.hpp"

bool isInsideMap(Map * m, int x, int y)
{
    if (x < 0 || y < 0 || x >= m->width || y >= m->height)
        return false;
    else
        return true;
}

void deleteCityList(City **head)
{
    if (*head != nullptr)
    {
        City *thisNode = *head;
        if (thisNode->next != nullptr)
        {
            thisNode = thisNode->next;
            deleteCityList(&thisNode);
        }
        else
        {
            if (thisNode->neighbours != nullptr)
                deleteNeighboursList(&(thisNode->neighbours));
            delete thisNode;
        }
    }
}

void deleteNeighboursList(Neighbour **head)
{
    if (*head != nullptr)
    {
        Neighbour *thisNode = *head;
        if (thisNode->next != nullptr)
        {
            thisNode = thisNode->next;
            deleteNeighboursList(&thisNode);
        }
        else
            delete thisNode;
    }
}

void addCityToHashTable(City *c, Map* m)
{
    int hash = hashify(c->name, m);
    if (m->cities[hash].city == nullptr)
        m->cities[hash].city = c;
    else
    {
        City *thisNode = m->cities[hash].city;
        while (thisNode->next != nullptr)
        {
            thisNode = thisNode->next;
        }
        thisNode->next = c;
    }
}

void addNeighbour(String &from, String &to, int dist,Map * m)
{
    City *thisCity = getCity(from, m);
    Neighbour *neighbour = new Neighbour;
    neighbour->name = to;
    neighbour->dist = dist;
    if (thisCity->neighbours == nullptr)
    {
        thisCity->neighbours = neighbour;
    }
    else
    {
        Neighbour *thisNeighbour = thisCity->neighbours;
        while (thisNeighbour->next != nullptr)
        {
            thisNeighbour = thisNeighbour->next;
        }
        thisNeighbour->next = neighbour;
    }
}

int hashify(String &name, Map * m)
{
    int hash = 0;
    for (int i = 0; i < name.getLength(); i++)
    {
        hash += name[i];
    }
    hash = hash % m->cityCounter;
    return hash;
}

City *getCity(String &name, Map * m)
{
    int hash = hashify(name, m);
    City *thisNode = m->cities[hash].city;
    while (thisNode != nullptr)
    {
        if (thisNode->name == name)
        {
            return thisNode;
        }
        thisNode = thisNode->next;
    }
    return thisNode; // nullptr gdy nic nie znajdzie
}

void addNewNodeToPath(Path *head, Path *newNode)
{
    Path *thisNode = head;
    while (thisNode->next != nullptr)
    {
        thisNode = thisNode->next;
    }
    thisNode->next = newNode;
}

void clearPath(Path **head)
{
    if (*head != nullptr)
    {
        Path *thisNode = *head;
        if (thisNode->next != nullptr)
        {
            thisNode = thisNode->next;
            clearPath(&thisNode);
        }
        else
            delete thisNode;
    }
}
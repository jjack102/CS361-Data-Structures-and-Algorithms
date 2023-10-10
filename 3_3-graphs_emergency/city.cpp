#include "city.h"
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;


City::City() 
{

}


void City::addRoad(Intersection intersection1, Intersection intersection2, unsigned time, bool pothole) 
{
    unsigned nV = num_vertices(roadMap);
    while (intersection1 >= nV)
        nV = add_vertex(roadMap)+1;
    while (intersection2 >= nV)
        nV = add_vertex(roadMap)+1;
    Road e = add_edge(intersection1, intersection2, roadMap).first;
	/*** Store the time & pothole information for this road. */
    roadMap[e].time = time;
    roadMap[e].pothole = pothole;

}


int City::connectingRoad(Intersection from, Intersection to) const
{
  /*** Your algorithm here */
  unsigned nV = num_vertices(roadMap);
  if(from >= nV || to >= nV) {
    return -1;
  }
  auto possibleEdge = edge(from, to, roadMap);
  if(possibleEdge.second) {
    Road e = possibleEdge.first;
    return roadMap[e].time;
  } else {
    return -1;
  }
}


bool City::hasPothole(Intersection from, Intersection to) const
{
  /*** Your algorithm here */
  unsigned nV = num_vertices(roadMap);
  if(from >= nV || to >= nV) {
    return -1;
  }
  auto possibleEdge = edge(from, to, roadMap);
  if(possibleEdge.second) {
    Road e = possibleEdge.first;
    return roadMap[e].pothole > 0;
  } else {
    return -1;
  }
}

int City::findFastestRoute(Intersection from, Intersection to, unsigned potholeLimit) const
{
  // Initialize the distance map and the priority queue
  unsigned nVertices = num_vertices(roadMap);

  std::vector<Intersection> cameFrom(nVertices);

  std::vector<unsigned> dist(nVertices, INT_MAX);
  dist[(int)from] = 0;

  typedef std::pair<int, Intersection> Element;
  std::priority_queue<Element, std::vector<Element>, std::greater<Element>>
  pq;
  pq.push(Element(0, from));

  // Find the shortest path
  while (!pq.empty())
  {
    Element top = pq.top();
    pq.pop();
    Intersection v = top.second;
    if (v == to) break; // exit when we reach the finish vertex

    int d = dist[v];
    if (top.first == d)
    {
      auto outgoing = out_edges(v, roadMap);
      for (auto e = outgoing.first; e != outgoing.second; ++e)
      {
        Intersection w = target(*e, roadMap);
        unsigned wdist = d + roadMap[*e].time;
        if (dist[w] > wdist && roadMap[*e].pothole <= potholeLimit)
        {
          dist[w] = wdist;
          pq.push(Element(wdist, w));
          cameFrom[w] = v;
        }
      }
    }
  }

  // Calculate total time
  int totalTime = 0;
  Intersection v = to;
  if (dist[v] != INT_MAX)
  {
    while (!(v == from))
    {
      Edge e;
      bool exists;
      std::tie(e, exists) = edge(v, cameFrom[v], roadMap);
      if (exists)
      {
        totalTime += roadMap[e].time;
      }
      v = cameFrom[v];
    }
  }

  return (dist[to] == INT_MAX) ? -1 : totalTime;
}


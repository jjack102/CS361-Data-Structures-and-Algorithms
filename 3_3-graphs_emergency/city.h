#ifndef CITY_H
#define CITY_H

#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

class City
{

    // data for edges
    struct TimeAndPthl { 
        unsigned time; 
        bool pothole;
        int potholeCount;       //do i need this??
    };


    typedef boost::adjacency_list<boost::listS,       // store edges in lists
                                  boost::vecS,        // store vertices in a vector
                                  boost::undirectedS,
								  /*** optional: Bundle data to the vertices
                                     and/or edges. */
                                  bool,
                                  TimeAndPthl                // edge data
                                  >
        Graph;
    typedef boost::graph_traits<Graph> GraphTraits;
    typedef GraphTraits::vertex_descriptor Vertex;
    typedef GraphTraits::edge_descriptor Edge;

    Graph roadMap;
  
    /*** You may add additional private data & functions as desired. */

public:
    typedef Vertex Intersection;
    typedef Edge Road;

    /**
     * Construct a new City object with no roads and intersections.
     * 
     */
    City();

    /**
     * Add a new road connecting two intersections.
     * 
     * @param intersection1  Identifier of 1st intersection
     * @param intersection2  Identifier of 2nd intersection
     * @param time How many minutes required to travel this road between the two intersections
     * @param pothole  true iff this road contains a pothole
     */
    void addRoad(Intersection intersection1, Intersection intersection2, unsigned time, bool pothole);

    /**
     * Find the time of a single road connecting two intersections. 
     * 
     * @param from The starting intersection of the vehicle
     * @param to  The ending intersection of the vehicle
     * @return int The time to traverse that road if it exists. If no single
     *             road connects the two intersection, return -1. 
     */
    int connectingRoad(Intersection from, Intersection to) const;

    /**
     * Indicate whether a road between two intersections has a pothole.
     * 
     * @param from The starting intersection of the vehicle
     * @param to  The ending intersection of the vehicle
     * @return bool True iff there is a single road connecting the two
     *              intersections and that road has a pothole.
     */
    bool hasPothole(Intersection from, Intersection to) const;

    /**
     * Find the total time of the shortest path between two intersections that will
     * not break an axle.
     * 
     * @param from The starting intersection of the vehicle
     * @param to  The ending intersection of the vehicle
     * @param potholeLimit the maximum number of potholes the vehicle may traverse
     * @return int The total time required to go from "from" to "to" while traversing no more
     *             than potholeLimit potholes.  Return -1 if there is no acceptable path between
     *             the two intersections.
     */
    int findFastestRoute(Intersection from, Intersection to, unsigned potholeLimit) const;

};

#endif

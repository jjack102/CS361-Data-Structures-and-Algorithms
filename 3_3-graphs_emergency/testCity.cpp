#include "city.h"
#include <array>
#include <algorithm>
#include "unittest.h"

using namespace std;


UnitTest(testCityConstructor) {
    City city;
    assertThat (city.connectingRoad(0, 1), isEqualTo(-1));
    assertThat (city.hasPothole(0, 1), isEqualTo(false));
    assertThat (city.findFastestRoute(0, 1, 0), isEqualTo(-1));
    assertThat (city.findFastestRoute(0, 0, 0), isEqualTo(0));
}

UnitTest(testOneRoadWithPothole) {
    City city;
    city.addRoad(0, 1, 5, true);
    assertThat (city.connectingRoad(0, 1), isEqualTo(5));
    assertThat (city.connectingRoad(1, 0), isEqualTo(5));
    assertThat (city.hasPothole(0, 1), isEqualTo(true));
    assertThat (city.hasPothole(1, 0), isEqualTo(true));
    
    assertThat (city.findFastestRoute(0, 1, 1), isEqualTo(5));
    assertThat (city.findFastestRoute(1, 0, 1), isEqualTo(5));
    assertThat (city.findFastestRoute(0, 1, 0), isEqualTo(-1));
    assertThat (city.findFastestRoute(0, 0, 0), isEqualTo(0));
}

UnitTest(testOneRoadNoPothole) {
    City city;
    city.addRoad(0, 1, 8, false);
    assertThat (city.connectingRoad(0, 1), isEqualTo(8));
    assertThat (city.connectingRoad(1, 0), isEqualTo(8));
    assertThat (city.hasPothole(0, 1), isEqualTo(false));
    assertThat (city.hasPothole(1, 0), isEqualTo(false));
    
    assertThat (city.findFastestRoute(0, 1, 1), isEqualTo(8));
    assertThat (city.findFastestRoute(1, 0, 1), isEqualTo(8));
    assertThat (city.findFastestRoute(0, 1, 0), isEqualTo(8));
    assertThat (city.findFastestRoute(0, 0, 0), isEqualTo(0));
}

UnitTest(testDisconnected) {
    City city;
    city.addRoad(0, 1, 5, false);
    city.addRoad(2, 3, 5, false);

    assertThat (city.connectingRoad(1, 0), isEqualTo(5));
    assertThat (city.connectingRoad(2, 3), isEqualTo(5));
    assertThat (city.hasPothole(0, 1), isEqualTo(false));
    assertThat (city.hasPothole(2, 3), isEqualTo(false));

    assertThat (city.findFastestRoute(0, 1, 0), isEqualTo(5));
    assertThat (city.findFastestRoute(0, 2, 0), isEqualTo(-1));
    assertThat (city.findFastestRoute(0, 3, 0), isEqualTo(-1));

    assertThat (city.findFastestRoute(1, 1, 0), isEqualTo(0));
    assertThat (city.findFastestRoute(1, 2, 0), isEqualTo(-1));
    assertThat (city.findFastestRoute(1, 3, 0), isEqualTo(-1));

    assertThat (city.findFastestRoute(2, 1, 0), isEqualTo(-1));
    assertThat (city.findFastestRoute(2, 2, 0), isEqualTo(0));
    assertThat (city.findFastestRoute(2, 3, 0), isEqualTo(5));
}



UnitTest(testThreeRoads) {
    City city;
    city.addRoad(0, 1, 5, true);
    city.addRoad(1, 2, 5, true);
    city.addRoad(0, 2, 12, true);

    assertThat (city.connectingRoad(1, 0), isEqualTo(5));
    assertThat (city.connectingRoad(1, 2), isEqualTo(5));
    assertThat (city.connectingRoad(0, 2), isEqualTo(12));
    assertThat (city.hasPothole(0, 1), isEqualTo(true));
    assertThat (city.hasPothole(2, 1), isEqualTo(true));
    assertThat (city.hasPothole(2, 0), isEqualTo(true));


    assertThat (city.findFastestRoute(0, 2, 2), isEqualTo(10));
    assertThat (city.findFastestRoute(2, 0, 2), isEqualTo(10));
    assertThat (city.findFastestRoute(0, 2, 1), isEqualTo(12));
    assertThat (city.findFastestRoute(2, 0, 1), isEqualTo(12));
    assertThat (city.findFastestRoute(0, 2, 0), isEqualTo(-1));
    assertThat (city.findFastestRoute(2, 0, 0), isEqualTo(-1));
}

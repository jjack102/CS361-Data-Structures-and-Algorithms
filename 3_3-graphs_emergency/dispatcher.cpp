#include <iostream>
#include <fstream>

#include"city.h"

using namespace std;




void readCity (istream& in, City& city)
{
  int from;
  while (in >> from)
  {
    int to, time, pothole;
    in >> to >> time >> pothole;
    city.addRoad(from, to, time, pothole>0);
  }
}
    


void solve(istream& in)
{
  int from, to, limit;

  in >> from >> to >> limit;

  City city;
  readCity(in, city);

  int d = city.findFastestRoute(from, to, limit);

  if (d >= 0)
		{
		  cout << "Fastest time for car at " << from
			   << " to the emergency at " << to << " is "
			   << d << " minutes." << endl;
		}
      else
		{
		  cout << "There is no way for the car at " << from
			   << " to reach the emergency at " << to << endl;
		}

}


int main (int argc, char** argv)
{
  if (argc == 1)
    solve(cin);
  else
  {
    ifstream in (argv[1]);
    solve (in);
  }
  return 0;
}
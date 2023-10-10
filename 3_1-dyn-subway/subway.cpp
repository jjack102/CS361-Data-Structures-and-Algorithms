#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;


struct Subway {
  bool** connected; // 2D array, connected[i][j] is true iff stations i
	                // and j are connected by a direct line.
  int nStations;

  Subway (int N);

private:
  // No copying allowed
  Subway (const Subway&) {}
  void operator= (const Subway&) {}
};


Subway::Subway(int N)
{
  nStations = N;
  connected = new bool*[N];
  for (int i = 0; i < N; ++i)
	{
	  connected[i] = new bool[N];
	  fill_n (connected[i], N, false);
	}
}

unsigned long long int callCounter = 0;
void report (int dest, int k)
{
  ++callCounter;
  // Uncomment the following statement if you want to get a feel 
  // for how many times the same subproblems get revisited
  // during the recursive solution.
  //cerr << callCounter << ": (" << dest << "," << k << ")" << endl;
}


/**
 * Count the number of ways we can go from station 0 to station destination
 * traversing exactly nSteps edges.
 */
unsigned long long int tripCounter (const Subway& subway, int destination, int nSteps)
{
  unsigned long long int dp[subway.nStations][nSteps+1];
  // Base case: We can do this in 1 step if destination is
  // directly connected to 0.
  for(int dest = 0; dest < subway.nStations; ++dest) {
	dp[dest][1] = subway.connected[0][dest] ? 1 : 0;
  }

  for(int k = 2; k <= nSteps; ++k) {
	for(int dest = 0; dest < subway.nStations; ++dest) {
		dp[dest][k] = 0;
		for(int S = 0; S < subway.nStations; ++S) {
			if(subway.connected[S][dest]) {
				dp[dest][k] += dp[S][k-1];
			}
		}
	}
  }
  
  return dp[destination][nSteps];
}


// Read the subway description and
// print the number of possible trips.
void solve (istream& input)
{
  int N, k;
  input >> N >> k;
  Subway subway(N);
  int station1, station2;
  while (input >> station1)
	{
	  input >> station2;
	  subway.connected[station1][station2] = true;
	  subway.connected[station2][station1] = true;
	}
  cout << tripCounter(subway, 0, k) << endl;
  // For illustrative/debugging purposes
  cerr << "Recursive calls: " << callCounter << endl;
}




int main (int argc, char** argv)
{
  if (argc > 1) 
	{
	  ifstream in (argv[1]);
	  solve (in);
	}
  else
	{
	  solve (cin);
	}
  return 0;
}


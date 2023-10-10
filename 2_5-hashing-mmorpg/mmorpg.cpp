#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

#include "character.h"
#include "cellIndex.h"
#include "cellMap.h"

using namespace std;

void solve(istream &in)
{
	int N, D;
	in >> N >> D;

	CellMap characterPositions;
	vector<Character> characters;
	characters.reserve(N);
	// Pass 1 : read in the characters and assign them to the appropriate cells.
	for (int i = 0; i < N; ++i)
	{
		Character ch;
		in >> ch.x >> ch.y;
		characters.push_back(ch);
		recordPosition(ch, characterPositions, D);
	}

	// Pass 2 : count the number of characters that are within D of at least one other character
	int count = 0;
	for (Character &ch : characters)
	{
		if (canSeeAnotherCharacter(ch, characterPositions, D))
			++count;
	}
	cout << count << endl;
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		ifstream in(argv[1]);
		solve(in);
	}
	else
		solve(cin);
	return 0;
}

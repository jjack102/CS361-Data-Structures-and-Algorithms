#include <iostream>
#include <vector>
#include "character.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
    srand(time(0));

    int N = atoi(argv[1]);
    int D = atoi(argv[2]);
    int S = atoi(argv[3]);

    const int maxXY = 1000000000;

    vector<Character> v;

    cout << N << ' ' << D << endl;
    for (int i = 0; i < N-S; ++i)
    {
        Character ch;
        ch.x = (rand() % (2*maxXY)) - maxXY;
        ch.y = (rand() % (2*maxXY)) - maxXY;
        v.push_back(ch);
    }

    const double pi = 3.14159265358979323846;
    for (int i = 0; i < S; ++i)
    {
        int k = rand() % (N-S);
        Character ch = v[k];
        int anglei = rand() % 1000;
        double angle = 2.0 * pi * ((double)anglei) / 1000.0;
        double dx = 0.9 * cos(angle) * (double)D;
        double dy = 0.9 * sin(angle) * (double)D;
        ch.x += dx;
        ch.y += dy;
        if (ch == v[k])
            ch.x += D-1;
        v.push_back(ch);
    }

    for (unsigned i = 0; i < v.size(); ++i)
    {
        cout << v[i].x << ' ' << v[i].y << "\n";
    }
    cout << flush;

    return 0;
}
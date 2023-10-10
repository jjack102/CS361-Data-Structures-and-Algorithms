#include "character.h"

using namespace std;

long Character::distanceSq(const Character& p) const
{
	long dx = x - p.x;
	long dy = y - p.y;
	return dx*dx + dy*dy;
}

ostream& operator<< (ostream& out, const Character& p)
{
	out << "(" << p.x << "," << p.y << ")";
	return out;
}


bool operator== (const Character& left, const Character& right)
{
	return (left.x == right.x ) &&
	  (left.y == right.y );
}





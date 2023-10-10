#include "cellIndex.h"

using namespace std;

std::hash<int> int_hash;

std::size_t CellIndex::hash() const {
    return int_hash(i) + int_hash(j);
}

bool operator==(const CellIndex& left, const CellIndex& right) 
{
    return left.i == right.i && left.j == right.j;
}

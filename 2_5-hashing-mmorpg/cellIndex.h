#ifndef CELLINDEX_H_
#define CELLINDEX_H_

#include <cstddef>
#include <iostream>

// Indices of a cell in the world

struct CellIndex {
	int i, j;

	std::size_t hash() const;
};

bool operator==(const CellIndex& left, const CellIndex& right);


namespace std {
	template <>
	struct hash<CellIndex> {
    	std::size_t operator() (const CellIndex& cell) const {
			return (std::size_t)cell.hash();
		}
	};
}

#endif


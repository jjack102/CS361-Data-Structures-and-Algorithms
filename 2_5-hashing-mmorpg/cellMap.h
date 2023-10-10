#ifndef CELLMAP_H_
#define CELLMAP_H_

#include <unordered_map>
#include "cellIndex.h"
#include "character.h"

typedef std::unordered_multimap<CellIndex, Character> CellMap;

/**
 * Record in the map the approrpiate assignment of a character to a cell.
 * Must run in O(1) average time.
 *
 * @param character the character whose position is being recorded
 * @param characterPositions the mapping from cell indices to the characters in that cell
 * @param cellSize the width of a cell, also the max distance at which characters can see one another
 */
void recordPosition (const Character& character, CellMap& characterPositions, int cellSize);


/**
 * Check to see if a given character can see any others.
 * Must run in O(1) average time.
 *
 * @param character the character whose field of vision is to be checked
 * @param characterPositions the mapping from cell indices to the characters in that cell
 * @param cellSize the width of a cell, also the max distance at which characters can see one another
 * @returns true if this character can see at least one other. 
 */
bool canSeeAnotherCharacter (const Character& character, const CellMap& characterPositions, int cellSize);



#endif

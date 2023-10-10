#include "cellMap.h"
#include <cmath>
#include <iostream>

using namespace std;

/**
 * Record in the map the approrpiate assignment of a character to a cell.
 * Must run in O(1) average time.
 *
 * @param character the character whose position is being recorded
 * @param characterPositions the mapping from cell indices to the characters in that cell
 * @param cellSize the width of a cell, also the max distance at which characters can see one another
 */
void recordPosition (const Character& character, CellMap& characterPositions, int cellSize) {
    int cellX = std::floor(character.x /  static_cast<double>(cellSize));
    int cellY = std::floor(character.y /  static_cast<double>(cellSize));

    CellIndex cellIndex{cellX, cellY};

    characterPositions.insert(std::make_pair(cellIndex, character));
}

/**
 * Check to see if a given character can see any others.
 * Must run in O(1) average time.
 *
 * @param character the character whose field of vision is to be checked
 * @param characterPositions the mapping from cell indices to the characters in that cell
 * @param cellSize the width of a cell, also the max distance at which characters can see one another
 * @returns true if this character can see at least one other. 
 */
bool canSeeAnotherCharacter (const Character& character, const CellMap& characterPositions, int cellSize) {
    int cellX = static_cast<int>(std::floor(character.x / static_cast<double>(cellSize)));
    int cellY = static_cast<int>(std::floor(character.y / static_cast<double>(cellSize)));

    CellIndex cellIndex{cellX, cellY};

    auto range = characterPositions.equal_range(cellIndex);
    for(auto it = range.first; it != range.second; ++it) {
        if(it->second == character) {
            continue;
        }
        if(character.distanceSq(it->second) <= cellSize * cellSize) {
            return true;
        }
    }

    for(int i = cellX - 1; i <= cellX + 1; ++i) {
        for(int j = cellY - 1; j <= cellY + 1; ++j) {
            CellIndex neighborCellIndex{i, j};
            auto range = characterPositions.equal_range(neighborCellIndex);
            for(auto it = range.first; it != range.second; ++it) {
                if(it->second == character) {
                    continue;
                }
                if(character.distanceSq(it->second) <= cellSize * cellSize) {
                    return true;
                }
            }
        }
    }

    return false;
}


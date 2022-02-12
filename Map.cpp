#include <iostream>
#include <vector>
using namespace std;

#include "Map.hpp"

extern pair<int, int> IndexToPair(int i, int width);

Map::Map(vector<int> Map, pair<int, int> Dimensions)
{
    this->map = Map;
    this->dimensions = Dimensions;
}

/// <summary>
/// Print's the map in a human-readable format.
/// X - wall.
/// ' ' - empty space.
/// o - start location.
/// * - target location.
/// @ - overlapping start and target location.
/// . - path.
/// </summary>
/// <param name="start">Start coordinates for pathfinding</param>
/// <param name="target">Target coordinates for pathfinding</param>
/// <param name="path">Pathfinding path</param>
void Map::PrintMap(pair<int, int> Start, pair<int, int> Target, vector<int> Path)
{
    cout << string(this->dimensions.first + 2, 'X') << endl; // Top Wall
    for (int y = 0; y < this->dimensions.second; y++) {
        cout << 'X'; // Side walls
        for (int x = 0; x < this->dimensions.first; x++) {
            int cellValue = this->map[x + (this->dimensions.first * y)];

            // Determine what character to print at cell position
            char cellChar = ((cellValue == 1) ? ' ' : 'X'); // empty or wall
            if (x == Start.first && y == Start.second) { // start position
                cellChar = Start == Target ? '@' : 'o'; // check for target overlap
            }
            else if (x == Target.first && y == Target.second) { // end position
                cellChar = '*';
            }
            // display path
            else {
                for (int i = 0; i < Path.size(); i++) {
                    pair<int, int> pathPosition = IndexToPair(Path[i], dimensions.first);
                    if (x == pathPosition.first && y == pathPosition.second) {
                        cellChar = '.';
                    }
                }
            }

            cout << cellChar;
        }
        cout << 'X' << endl; // Side walls
    }
    cout << string(this->dimensions.first + 2, 'X') << endl; // Bottom wall
}
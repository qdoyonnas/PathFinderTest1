#include <iostream>
#include <vector>
#include <chrono>
#include <limits>
using namespace std;

#include "Map.hpp"
#include "PathFinder.hpp"

extern pair<int, int> IndexToPair(int i, int width);

void FindAndPrint(Map Map, pair<int, int> Start, pair<int, int> Target)
{
    vector<int> path;
    if (FindPath(Start, Target, Map.map, Map.dimensions, path)) {
        cout << "Found path!" << endl << endl;
        Map.PrintMap(Start, Target, path);
        cout << endl;
        for (int i = 0; i < path.size(); i++) {
            pair<int, int> position = IndexToPair(path[i], Map.dimensions.first);
            cout << "{ " << position.first << ", " << position.second << " } " << endl;
        }
    }
    else {
        cout << "No path!" << endl << endl;
        Map.PrintMap(Start, Target);
    }
}

int main()
{
    Map exampleMap1 = Map({ 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 }, { 4, 3 });
    Map exampleMap2 = Map({ 0, 0, 1, 0, 1, 1, 1, 0, 1 }, { 3, 3 });
    Map exampleMap3 = Map({ 1 }, { 1, 1 });
    Map exampleMap4 = Map(
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
            1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1,
            1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
            1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
            1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
            0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 
        },
        { 20, 20 });

    // Header
    cout << "Path Finding" << endl;
    cout << string(20, '=') << endl;

    //FindAndPrint(exampleMap4, { 4, 4 }, { 12, 16 });
    
    /*pair<int, int> dimensions{ 10000, 10000 };
    vector<int> bigArray(dimensions.first * dimensions.second, 1);
    Map exampleMap5 = Map(bigArray, dimensions);
    vector<int> path;
    auto start = chrono::high_resolution_clock::now();
    if (FindPath({ 0, 0 }, { dimensions.first - 1, dimensions.second - 1 }, exampleMap5.map, exampleMap5.dimensions, path)) {
        cout << "Path found: " << path.size() << endl;
    }
    else {
        cout << "Path not found!" << endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Duration: " << duration.count() << endl;
    cout << "6 seconds is 6000000" << endl;*/
    
    pair<int, int> dimensions{ 1000, 1000 };
    vector<bool> bigArray(dimensions.first * dimensions.second, true);
    int numOfObstacles = 1000;
    srand(time(NULL));
    for (int i = 0; i < numOfObstacles; i++) {
        int x = rand() % dimensions.first;
        int y = rand() % dimensions.second;
        bigArray[x + (y * dimensions.first)] = false;
    }
    vector<int>* path = NULL;
    auto start = chrono::high_resolution_clock::now();
    vector<int>* p_map = NULL;
    if (FindPath({ 0, 0 }, { dimensions.first - 1, dimensions.second - 1 }, *p_map, dimensions, *path)) {
        cout << "Path found: " << path->size() << endl;
    }
    else {
        cout << "Path not found!" << endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Duration: " << duration.count() << endl;
    cout << "6 seconds is 6000000" << endl;
    
}
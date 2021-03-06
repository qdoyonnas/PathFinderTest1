#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <limits>
using namespace std;

#include "Node.hpp"
#include "PathFinder.hpp"

bool ValidStartAndTarget(pair<int, int> Start, pair<int, int> Target, pair<int, int> MapDimensions)
{
    // Start and Target are within the bounds of the map
    if (Start.first < 0 || Start.first >= MapDimensions.first
        || Start.second < 0 || Start.second >= MapDimensions.second
        || Target.first < 0 || Target.first >= MapDimensions.second
        || Target.second < 0 || Target.second >= MapDimensions.second) {
        return false;
    }
    
    return true;
}

vector<Node*> FindNodeNeighbours(Node* node, const pair<int, int> mapDimensions)
{
    vector<Node*> neighbours(4);

    pair<int, int> nextPosition = node->position;
    // Find left neighbour
    nextPosition.first -= 1;
    if (nextPosition.first >= 0) {
        neighbours[0] = new Node(nextPosition, node);
    }
    // Find right neighbour
    nextPosition.first += 2;
    if (nextPosition.first < mapDimensions.first) {
        neighbours[1] = new Node(nextPosition, node);
    }
    // Find top neighbour
    nextPosition.first -= 1;
    nextPosition.second -= 1;
    if (nextPosition.second >= 0) {
        neighbours[2] = new Node(nextPosition, node);
    }
    // Find bottom neighbour
    nextPosition.second += 2;
    if (nextPosition.second < mapDimensions.second) {
        neighbours[3] = new Node(nextPosition, node);
    }

    return neighbours;
}

vector<int> TracePath(Node* node, pair<int, int> Start, pair<int, int> Target, int mapWidth)
{
    // Traces the path back from start to target by following the parents of each node
    vector<int> path;
    Node* p_node = node->p_parent;
    while (p_node != nullptr) {
        path.push_back(PairToIndex(p_node->position, mapWidth));
        p_node = p_node->p_parent;
    }

    return path;
}

bool FindPath(pair<int, int> Start,
    pair<int, int> Target,
    const vector<bool>& Map,
    pair<int, int> MapDimensions,
    vector<int>& OutPath)
{
    // Convert to vector<int>
    vector<int> intMap(Map.size());
    for (int i = 0; i < Map.size(); i++) {
        intMap[i] = Map[i];
    }

    return FindPath(Start, Target, intMap, MapDimensions, OutPath);
}

bool FindPath(pair<int, int> Start,
    pair<int, int> Target,
    const vector<int>& Map,
    pair<int, int> MapDimensions,
    vector<int>& OutPath)
{
    // This is just evil
    if (&OutPath == nullptr
        || &Map == nullptr) {
        return false;
    }

    // Validate inputs
    if (!ValidStartAndTarget(Start, Target, MapDimensions)
        || Map[PairToIndex(Start, MapDimensions.first)] != 1
        || Map[PairToIndex(Target, MapDimensions.first)] != 1
        || MapDimensions.first <= 0 || MapDimensions.second <= 0) {
        return false;
    }

    // Check for overlapping start and target 
    if (Start == Target) {
        OutPath = {};
        return true;
    }

    // Avoid length errors due to map size being too large for nodeMap 2d-vector
    // XXX: Resolving this issue would be the next step to improve this code
    vector<vector<Node*>> nodeMap;
    if (MapDimensions.first > nodeMap.max_size()
        || MapDimensions.second > vector<Node*>().max_size()) {
        return false;
    }
    nodeMap = vector<vector<Node*>>(MapDimensions.first, vector<Node*>(MapDimensions.second));
    NodeList openNodes;

    // Start at the target node - this avoids having to reverse the resulting path
    Node* targetNode = new Node(Target, nullptr);
    nodeMap[Target.first][Target.second] = targetNode;
    openNodes.insert(openNodes.begin, targetNode);
    
    while (openNodes.size > 0) {
        // Get first (lowest value) node
        Node* lowestValueNode = openNodes.begin;
        openNodes.pop_front();

        // Find Neighbours
        vector<Node*> neighbours = FindNodeNeighbours(lowestValueNode, MapDimensions);
        for (int i = 0; i < neighbours.size(); i++) {
            if (neighbours[i] == nullptr) { continue; }
            // Check if target found
            if (neighbours[i]->position == Start) {
                OutPath = TracePath(neighbours[i], Start, Target, MapDimensions.first);

                // Clean up
                while (openNodes.size > 0) {
                    Node* node = openNodes.begin;
                    openNodes.erase(openNodes.begin);
                    delete node;
                }

                return true;
            }

            // Check if map position is traversable
            if ( Map[PairToIndex(neighbours[i]->position, MapDimensions.first)] != 1) {
                continue;
            }

            // Set neighbour values
            neighbours[i]->distanceToTarget = lowestValueNode->distanceToTarget + 1;
            neighbours[i]->distanceToStart =
                abs(neighbours[i]->position.first - Start.first) +
                abs(neighbours[i]->position.second - Start.second);
            neighbours[i]->value = neighbours[i]->distanceToStart + neighbours[i]->distanceToTarget;


            // Organize nodes in a 2d array matching the map 1-to-1
            // Use this to determine if nodes have already been visited and what the most efficient path to each is
            Node* sameNode = nodeMap[neighbours[i]->position.first][neighbours[i]->position.second];
            if (sameNode == nullptr) {
                nodeMap[neighbours[i]->position.first][neighbours[i]->position.second] = neighbours[i];
            }
            else if(sameNode->value <= neighbours[i]->value) {
                // Node in map is more or equally efficient
                delete neighbours[i];
                continue;
            }
            else {
                // New node (by new path) is more efficient than node in map
                openNodes.erase(sameNode);
                delete sameNode;
                nodeMap[neighbours[i]->position.first][neighbours[i]->position.second] = neighbours[i];
            }

            // Sort openNodes in place for easy access - avoids searching for lowest value node
            // Some cpu profiling determined that starting at the end of the list is faster in most circumstances
            // Results in a sort of depth first search
            Node* it = openNodes.end;
            while (true) {
                if (it == nullptr) {
                    openNodes.push_front(neighbours[i]);
                    break;
                }
                if (it->value < neighbours[i]->value) {
                    if (it->next_node == nullptr) {
                        openNodes.push_back(neighbours[i]);
                    }
                    else {
                        openNodes.insert(it->next_node, neighbours[i]);
                    }
                    break;
                }
                it = it->previous_node;
            }
        }
    }

    OutPath = {};
    return false;
}

int PairToIndex(pair<int, int> position, int width)
{
    return position.first + (position.second * width);
}

pair<int, int> IndexToPair(int i, int width)
{
    return pair<int, int> {i % width, i / width};
}
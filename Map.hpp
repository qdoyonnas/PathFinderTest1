#pragma once

class Map
{
public:
	vector<int> map;
	pair<int, int> dimensions;

	Map(vector<int> map, pair<int, int> mapDimensions);
	void PrintMap(pair<int, int> start = { -1, -1 }, pair<int, int> target = { -1, -1 }, vector<int> path = {});
};
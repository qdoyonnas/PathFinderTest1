#pragma once

/// <summary>
/// Find the shortest path from Start to Target.
/// </summary>
/// <param name="Start">Starting coordinates</param>
/// <param name="Target">Target coordinates</param>
/// <param name="Map">Grid of obstacles provided in 1d vector</param>
/// <param name="MapDimensions">Describes the dimensions of the map in row-major order</param>
/// <param name="OutPath">Receives the resulting path</param>
/// <returns></returns>
bool FindPath(pair<int, int> Start,
    pair<int, int> Target,
    const vector<bool>& Map,
    pair<int, int> MapDimensions,
    vector<int>& OutPath);

/// <summary>
/// Find the shortest path from Start to Target.
/// </summary>
/// <param name="Start">Starting coordinates</param>
/// <param name="Target">Target coordinates</param>
/// <param name="Map">Grid of obstacles provided in 1d vector</param>
/// <param name="MapDimensions">Describes the dimensions of the map in row-major order</param>
/// <param name="OutPath">Receives the resulting path</param>
/// <returns></returns>
bool FindPath(pair<int, int> Start,
    pair<int, int> Target,
    const vector<int>& Map,
    pair<int, int> MapDimensions,
    vector<int>& OutPath);

int PairToIndex(pair<int, int> position, int width);
pair<int, int> IndexToPair(int i, int width);
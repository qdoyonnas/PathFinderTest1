#pragma once

bool FindPath(pair<int, int> Start,
    pair<int, int> Target,
    const vector<bool>& Map,
    pair<int, int> MapDimensions,
    vector<int>& OutPath);

bool FindPath(pair<int, int> Start,
    pair<int, int> Target,
    const vector<int>& Map,
    pair<int, int> MapDimensions,
    vector<int>& OutPath);

int PairToIndex(pair<int, int> position, int width);
pair<int, int> IndexToPair(int i, int width);
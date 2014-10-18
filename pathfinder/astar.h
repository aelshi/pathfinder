#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include "binaryheap.h"
#include "node.h"

using std::vector;

class astar {
        
private:
    
    int reconstruct(const node& s, const node& t, const int bufferSize, int* buffer);
    float distance(const node& s, const node& t) const;
    bool validate(const node& s, const node& t) const;
    void setDebugPath(const node& s, const node& t);
    void clear();
    
    vector<int> pListX, pListY, statusList;
    vector<int> debugPath;
    binaryheap< node, minComparison > heap;
    int width, height;

public:
    astar();
    ~astar();
    
    int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize );
    
    vector<int> getDebugPath() const { return debugPath; };
    
};
#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include "node.h"
#include "intervalheap.h"

/*
 This solution is similiar to the A Star implementation but is memory bounded using an interval heap with a given max size. When the current heap size exceeds the allowed max
 size the largest value is removed from the heap while still maintaing the min property of the tree, and and also the max property.
*/

using std::vector;

class smastar {
    
    
private:
    
    int reconstruct(const node& s, const node& t, const int bufferSize, int* buffer);
    float distance(const node& s, const node& t) const;
    bool validate(const node& s, const node& t) const;
    void setDebugPath(const node& s, const node& t);
    void clear();
    
    vector<int> pListX, pListY, statusList;
    vector<int> debugPath;
    intervalheap<node> heap; // heap for keeping track of lowest F, using a double ended heap
    int width, height;
    
public:
    smastar(int maxSize);
    ~smastar();
    
    int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize );
    vector<int> getDebugPath() const { return debugPath; };

    
};
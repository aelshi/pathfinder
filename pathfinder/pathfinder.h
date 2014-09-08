#ifndef __pathfinder__pathfinder__
#define __pathfinder__pathfinder__

#include <iostream>
#include <vector>
#include <math.h>
#include "bheap.h"
#include "node.h"

using std::vector;

class pathfinder {
    
   //std::mutex mutex_lock;
    
private:
    
    int reconstruct(const node& s, const node& t, const int bufferSize, int* buffer);
    float distance(const node& s, const node& t) const;
    bool validate(const node& s, const node& t) const;
    void setDebugPath(const node& s, const node& t);
    void clear();
    
    vector<int> pListX, pListY, statusList;
    vector<int> debugPath;
    bheap< node, minComparison > heap;
    int width, height;

public:
    pathfinder();
    ~pathfinder();
    
    int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize );
    
    vector<int> getDebugPath() const { return debugPath; };
    
};


#endif /* defined(__pathfinder__pathfinder__) */

#include "pathfinder.h"


pathfinder::pathfinder()
{}

pathfinder::~pathfinder()
{}

int pathfinder::FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize )
{
    
    // if start and target positions are outside the map
    if ( nStartX < 0 && nStartX > nMapWidth && nStartY < 0 && nStartY > nMapHeight )
        return -1;
    
    if ( nTargetX < 0 && nTargetX > nMapWidth && nTargetY < 0 && nTargetY > nMapHeight )
        return -1;
    
    if((int)pMap[nStartY * nMapWidth + nStartX] == 1)
        return -1;
    
    if((int)pMap[nTargetY * nMapWidth + nTargetX] == 1)
        return -1;
    
    
    // coordinates to access a 4-connected neighborhood
    const int dx[4]={0, 0, 1, -1};
    const int dy[4]={1, -1, 0, 0};
    int numberOfOpenListItems = 0;
    const int open = 2;
    const int closed = open + 1;
    
    //mutex_lock.lock();
    
    clear();
    
    width = nMapWidth;
    height = nMapHeight;
    
    statusList.resize(width * height, 0); // list maintaining the open and closed status for nodes
    pListX.resize(width * height);   // parent list for X values
    pListY.resize(width * height);   // parent list for Y values
    heap.reserve(width * height); // heap for keeping track of lowest F
    
    node targetN(nTargetX, nTargetY, 0);

    node startN(nStartX, nStartY, 0);
    startN.f = 0 + distance(startN, targetN); // f = g + h
    
    heap.push_back(startN);
    statusList[nStartY * width + nStartX] = open;
    numberOfOpenListItems++;
    
    while (numberOfOpenListItems != 0) {
        
        const node currNode = heap.pop();
        const int c_x = currNode.x;
        const int c_y = currNode.y;
        
        if (currNode == targetN) {
            // reconstruct path
            setDebugPath(startN, currNode);
            return reconstruct(startN, currNode, nOutBufferSize, pOutBuffer);
        }
        
        // unmark it from the open list and mark it in the closed list
        numberOfOpenListItems--;
        statusList[c_y * width + c_x] = closed;
        
        int n_x = 0;
        int n_y = 0;
        
        // search through 4-connected neighborhood
        for (int i = 0; i <= 3; ++i) {
            
            n_x = c_x + dx[i];
            n_y = c_y + dy[i];
            
            if ( n_x >= 0 && n_x < width && n_y >= 0 && n_y < height )
            {
                
                node neighbor = node(n_x, n_y);
                
                const int neighborIndex = n_y * width + n_x;
                
                // check to see if it's in closed list and if the node is blocked
                if(statusList[neighborIndex] != closed && (int)pMap[neighborIndex] != 1)
                {
                    
                    const float cost = currNode.g + 1 + distance(neighbor, targetN); // g + h
                    
                    // in open list
                    if(statusList[neighborIndex] == open)
                    {
                        
                        if(cost < neighbor.g)
                        {
                            neighbor.g = cost;
                            heap.insert(neighbor);
                            pListX[neighborIndex] = c_x;
                            pListY[neighborIndex] = c_y;
                        }
                        
                    }
                    
                    else
                    {
                        neighbor.g = cost;
                        neighbor.f = cost + distance( neighbor, targetN ); // g + h
                        statusList[neighborIndex] = open;
                        numberOfOpenListItems++;
                        heap.push_back(neighbor);
                        pListX[neighborIndex] = c_x;
                        pListY[neighborIndex] = c_y;
                        
                    }
                }
                
            }
            
            
        }
        
        
    }
    
    
    //mutex_lock.unlock();
    
    return -1;
    
}




float pathfinder::distance(const node& s, const node& t) const
{
    
    int dx = abs(t.x - s.x), dy = abs(t.y - s.y);
    float estimate = abs(dx - dy) + sqrt(2) * std::min(dx, dy);
    //float d = (abs(endNode->x - p->x) + abs(endNode->y - p->y));
    
    return estimate;
    
}




int pathfinder::reconstruct(const node& s, const node& t, const int bufferSize, int* buffer)
{
    int pathSize = 0;
    int pathX = t.x;
    int pathY = t.y;
    int tempx = 0;
    int sX = s.x;
    int sY = s.y;
    
    while (pathX != sX or pathY != sY) {
        ++pathSize;
        tempx = pListX[pathY * width + pathX];
        pathY = pListY[pathY * width + pathX];
        pathX = tempx;
    }
    
    pathSize = pathSize * 2;
    
    if(pathSize <= bufferSize)
    {
        int i = -1;
        
        pathX = t.x;
        pathY = t.y;
        tempx = 0;
        while (pathX != sX or pathY != sY) {
            //std::cout<<"path x: "<<pathX<<" path y: "<<pathY<<std::endl;
            
            buffer[++i] = pathX;
            buffer[++i] = pathY;
            
            tempx = pListX[pathY * width + pathX];
            pathY = pListY[pathY * width + pathX];
            pathX = tempx;
        }
    }
    
    else
        std::cout<<"too large of a buffer"<<std::endl;
    
    
    std::cout<<"FINISH"<<std::endl;
    
    //mutex_lock.unlock();
    
    return pathSize;
    
}

void pathfinder::setDebugPath(const node &s, const node &t)
{
    debugPath.resize(width * height, 0);

    int pathX = t.x;
    int pathY = t.y;
    int sX = s.x;
    int sY = s.y;
    int tempx = 0;
    
    while (pathX != sX or pathY != sY) {
        
        debugPath[(pathY) * width + (pathX)] = 1;
        
        tempx = pListX[pathY * width + pathX];
        pathY = pListY[pathY * width + pathX];
        pathX = tempx;
    }

}

void pathfinder::clear()
{
    pListX.clear();
    pListX.clear();
    statusList.clear();
    heap.clear();
}



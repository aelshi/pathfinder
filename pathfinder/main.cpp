#include <iostream>
#include "astar.h"
#include "smastar.h"
#include <thread>
#include <future>
#include <unistd.h>

int main(int argc, const char * argv[])
{
    int width = 500;
    int height = 500;
    int bufferSize = 600;
    vector<unsigned char> map;
    map.resize(width * height, 0);
    vector<int> output(bufferSize);
    
    /*
    for (int x = 0; x < width; x+=2) {
        
        for (int y = 0; y < height; y+=2) {
            
            int val = rand()%2;
            
            map[y * width + x] = (unsigned char)val;
        }
    }
    */
    
    astar aStar;
    smastar smaStar(50); // max size allowed for the heap
    
    std::cout<<aStar.FindPath(0, 0, 50, 50, &map[0], width, height, &output[0], bufferSize )<<std::endl;
    std::cout<<smaStar.FindPath(0, 0, 50, 50, &map[0], width, height, &output[0], bufferSize)<<std::endl;
        
    return 0;
}


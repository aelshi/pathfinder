#include <iostream>
#include "pathfinder.h"
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
    
    /*for (int x = 0; x < width; x+=2) {
        
        for (int y = 0; y < height; y+=2) {
            
            int val = rand()%2;
            
            map[y * width + x] = (unsigned char)val;
        }
    }
    */
    pathfinder astar;
    
    /*
     
     // Using async for return values (futures). Using launch::async to garantuee threading
     std::future<int> result1 =  std::async(std::launch::async, &pathfinder::FindPath, &astar, 0, 0, 50, 50, &map[0], width, height, &output, 10 );
     
    std::future<int> result2 =  std::async(std::launch::async, &pathfinder::FindPath, &astar, 0, 0, 100, 100, &map[0], width, height, &output, 10 );
     
    int r1 = result1.get();
    int r2 = result2.get();
     
     std::cout<<"result1: "<<r1<<" result2: "<<r2<<std::endl;
    */
    
    std::cout<<astar.FindPath(0, 0, 50, 50, &map[0], width, height, &output[0], bufferSize )<<std::endl;

    sleep(10);
    
    
    return 0;
}


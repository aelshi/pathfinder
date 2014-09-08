#ifndef __pathfinder__bheap__
#define __pathfinder__bheap__

#include <iostream>
#include <vector>

template<class T = std::vector<int>, class Comparison = std::less<T> >
class bheap {
    
private:
    std::vector<T> heap;
    
    int find(const T& n) const
    {
        for (int i = 0; i < heap.size(); ++i) {
            if(n == heap[i])
            {
                return i;
            }
        }
        return -1;
    };
    
    void bubble(int index, const T& n)
    {
        heap[index] = n;
        std::push_heap(heap.begin(), heap.begin() + index + 1, Comparison());
    };
    
    
public:
    
    bheap(){};
    ~bheap(){};
    
    
    void push_back(const T& n)
    {
        heap.push_back(n);
        std::push_heap(heap.begin(), heap.end(), Comparison());
    };
    
    T pop()
    {
        std::pop_heap(heap.begin(), heap.end(), Comparison());
        T n = heap.back();
        heap.pop_back();
        return  n;
    };
    
 
    bool insert(const T& n)
    {
        int index = find(n);
        
        if(index != -1)
        {
            bubble(index, n);
            return true;
        }
        else
        {
            push_back(n);
            return false;
        }
    };
    
    void reserve(const int size)
    {
        heap.reserve(size);
        std::make_heap (heap.begin (), heap.end (), Comparison());
    };
    
    
    void print() const
    {
        std::cout<<"Heap"<<std::endl;
        std::cout<<" ";
        for (int i = 0; i < heap.size(); ++i) {
            std::cout<<heap[i]<<" ";
        }
        std::cout<<std::endl;
        
    };
    
    const int getSize() const { return (int)heap.size(); };
    const bool isEmpty() const { return heap.empty(); };
    void clear() { heap.clear(); };
    
  
    
};

#endif /* defined(__pathfinder__bheap__) */

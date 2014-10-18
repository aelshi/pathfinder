/*

 Interval heap. Similiar to a binary heap but at each node there is a min (left) and max (right) element and follows min-max properties. This means one can prune the min and max 
 values seperately, in constant time.

*/

#pragma once

#include <iostream>
#include "node.h"
#include <vector>

using std::vector;

template<class T = int>
struct node_pair
{
    T left;
    T right;
    
    node_pair()
    {
        left = -1;
        right = -1;
    }
    
    node_pair(const T& x, const T& y)
    {
        left = x;
        right = y;
    }
    
    node_pair& operator= (const node_pair& other)
    {
        if (this != &other)
        {
            left = other.left;
            right = other.right;
  
        }
        
        return *this;
    }
    
    friend std::ostream& operator << (std::ostream &output, const node_pair& n)
    {
        return output << "( min , max ) - ( " << n.left << " , " << n.right << " ) " << "\n";
        
    }
};


template<class T = int>
class intervalheap
{
    
public:
    intervalheap() { nrOfElements = 0; };
    intervalheap(int size)
    {
        maxSize = size;
        nrOfElements = 0;
    };
    ~intervalheap(){};
    
    int size() const { return (int)heap.size(); };
    int getSize() const { return nrOfElements; };
    int getMaxSize() const { return maxSize; };
    bool isEmpty() const { return heap.empty(); };
    void clear() { heap.clear(); nrOfElements = 0; };
    
    void reserve(int size)
    {
        maxSize = size;
        heap.reserve(size);
    };
    
    void print() const
    {
        for (int i = 0; i < heap.size(); ++i) {
            std::cout<<i<<" - "<<heap[i];
        }
    };
    
    T getMin() const
    {
        return heap[0].left;
    };

    T getMax() const
    {
        return getSize() == 1 ? heap[0].left : heap[0].right;
    };
    
    void add(const T& x)
    {
    
        if(nrOfElements % 2 == 0) // even number of elements needs an additional element
        {
            T r;
            r = -1.0f;
            heap.push_back(node_pair<T>(x, r)); // create new element in the heap
        }
        else
        {
            // last node
            node_pair<T>* node = &heap.back();
            
            if(x < node->left)
            {
                node->right = node->left;
                node->left = x;
            }
            else
                node->right = x;
        }
    
        nrOfElements++;
        
        // if there are no parents then there's no need to re order the heap
        if (nrOfElements <= 2)
            return;
        
        node_pair<T> parentNode = heap[(heap.size() - 1) / 2];
        
        if(parentNode.left > x)
            minHeapInsert();
            
        else if(parentNode.right < x)
            maxHeapInsert();
    };
    
    
    T popMin()
    {
        T returnVal = getMin();
        
        // only one element
        if(getSize() == 1)
        {
            heap.erase(heap.begin() + 0);
            nrOfElements--;
            return returnVal;
        }
        
        // move the the min from the last node to the first node
        node_pair<T>* lastNode = &heap[heap.size() - 1];
        heap[0].left = lastNode->left;
        
        // remove the last node if there's odd number of elements
        if(getSize() % 2 == 1)
        {
            heap.pop_back();
        }
        else
        {
            lastNode->left = lastNode->right;
            lastNode->right = -1;
        }
        nrOfElements--;
        
        // bubble down
        
        int index = 0;
        node_pair<T>* currentNode = &heap[index];

        while(true)
        {
            
            // end if there's no children
            if(index * 2 >= heap.size())
                break;
            
            // we at one or two children
            int nextChild = 0;
            
            // for two children we need to compare them and find the smaller one
            if(index * 2 + 1 <= heap.size())
            {
                if(heap[index * 2].left < heap[index * 2 + 1].left)
                    nextChild = index * 2;
                else
                    nextChild = index * 2 + 1;
            }
    
            else
                nextChild = index * 2;
            
            
            node_pair<T>* childNode = &heap[nextChild];
            
            // done when the current min is smaller than it's child
            if(currentNode->left <= childNode->left )
                break;
            
            swap(childNode->left, currentNode->left);
            
            // if this childs min/max is in right places
            if(childNode->right != -1 && childNode->left > childNode->right)
            {
                swap(childNode->left, childNode->right);
            }
            
            //currentNode = &heap[childCompare];
            currentNode = childNode;
            index = nextChild;
        }

        return returnVal;
       
    };
    
    T popMax()
    {
        T returnVal = getMax();
        
        // only one node
        if(getSize() == 1)
        {
            heap.erase(heap.begin() + 0); // or 1?
            nrOfElements--;
            return returnVal;
        }
            
        // move the the max from the last node to the first node
        node_pair<T>* lastNode = &heap[heap.size() - 1];
        
        if(getSize() % 2 == 1) // odd elements, set the min val from last node to the max val in the first node
        {
            heap[0].right = lastNode->left;
            heap.pop_back();
        }
        else
        {
            heap[0].right = lastNode->right;
            lastNode->right = -1;
        }
        nrOfElements--;
        
        
        int index = 0;
        node_pair<T>* currentNode = &heap[index];
        
        while (true) {
            
            // end when there's no children
            if(index * 2 >= heap.size())
                break;
            
            int childCompare = 0;
            
            // two children, compare them
            if(index * 2 + 1 < heap.size())
            {
            
                // at the last node if there is there odd elements
                if(getSize() % 2 == 1 && index * 2 + 1 == heap.size() - 1)
                {
                    
                    if(heap[index * 2].right > heap[index * 2 + 1].left)
                        childCompare = index * 2;
                    else
                        childCompare = index * 2 + 1;
                    
                }
                else
                {
                    if(heap[index * 2].right > heap[index * 2 + 1].right)
                        childCompare = index * 2;
                    else
                        childCompare = index * 2 + 1;
                }

            }
            else
                childCompare = index * 2;
            
            
            node_pair<T>* childNode = &heap[childCompare];
            
            if (childNode->right == -1) {
                
                if (childNode->left < currentNode->right)
                    break;
                
                swap(childNode->left, currentNode->right);
            }
            else
            {
                if(childNode->right <  currentNode->right)
                    break;
                
                swap(childNode->right, currentNode->right);
                
                if(childNode->left > childNode->right)
                {
                    swap(childNode->right, childNode->left);
                }
            }
            
            index = childCompare;
            currentNode = childNode;
        }
        
        return returnVal;
        
    };
    

    
    void insert(const T& n, float f)
    {
    
        int elementIndex = findNode(n);
        
        int heapIndex = (elementIndex / 2 + elementIndex % 2) - 1 ;
        
        // odd node = left element, update it
        if(elementIndex % 2 == 1)
        {
            heap[heapIndex].left = f;
            minBubble(heapIndex);
        }
        else
        {
            heap[heapIndex].right = f;
            
            // if they're in the wrong order
            if(heap[heapIndex].right < heap[heapIndex].left)
            {
                swap(heap[heapIndex].right, heap[heapIndex].left);
                minBubble(heapIndex);
                maxBubble(heapIndex);
            }
            else
                maxBubble(heapIndex);
        }
        
        
        
    };
    
    void minBubble(int index)
    {
        node_pair<T>* node = &heap[index];
        while (index > 0) {
            
            int parentIndex = index / 2;
            node_pair<T>* parentNode = &heap[parentIndex];
            
            if(node->left >= parentNode->left)
                break;
            
            swap(node->left, parentNode->left);
            
            index = parentIndex;
            node = parentNode;
        }
    };
    
    void maxBubble(int index)
    {
    
        node_pair<T>* currentNode = &heap[index];

        int childIndex = 0;
        
        while (true) {
            
            if (index * 2 <= getSize()) {
                break;
            }
            
            if(heap[index * 2].right > heap[index * 2 + 1].right)
                childIndex = index * 2;
            else
                childIndex = index * 2 + 1;
            
            node_pair<T>* childNode = &heap[childIndex];

            
            if(childNode->right >  currentNode->right)
                break;
            
            swap(childNode->right, currentNode->right);
            
            if(childNode->left > childNode->right)
            {
                swap(childNode->right, childNode->left);
            }

            
            index = childIndex;
            currentNode = childNode;
            
        }             
    
    };

private:
    vector< node_pair<T> > heap;
    int nrOfElements;
    int maxSize;
    
    void swap( T& n1,  T& n2)
    {
        T temp = n1;
        n1 = n2;
        n2 = temp;
        
    };

    void minHeapInsert()
    {
        // last node
        int index = (int)heap.size() - 1;
        node_pair<T>* node = &heap[index];
        
        while (index > 0) {
            
            int parentIndex = index / 2;
            node_pair<T>* parentNode = &heap[parentIndex];
            
            if(node->left >= parentNode->left)
                break;
            
            swap(node->left, parentNode->left);

            index = parentIndex;
            node = parentNode;
        }
        
    };
    
    void maxHeapInsert()
    {
        
        // last node
        int index = (int)heap.size() - 1;
        node_pair<T>* node = &heap[index];
        
        while (index > 0) {
            
            int parentIndex = index / 2;
            node_pair<T>* parentNode = &heap[parentIndex];
            
            // special case if there's no max value in the node
            if(node->right == -1)
            {
                
                if(node->left < parentNode->right)
                    break;
                
                swap(node->left, parentNode->right);
      
                index = parentIndex;
                node = parentNode;
            
            }
            else
            {
            
                if(node->right < parentNode->right )
                    break;

                swap(node->right, parentNode->right);
                
                index = parentIndex;
                node = parentNode;
            
            }
            
        }
        
    };
    
    int findNode(const T& n)
    {
        
        int elementIndex = 1;
        
        for (int i = 0; i < heap.size(); ++i) {
            
            node_pair<T>* node = &heap[i];
            
            if(node->left.x == n.x && node->left.y == n.y )
            {
                return elementIndex;
            }
            else if(node->right.x == n.x && node->right.y == n.y)
            {
                elementIndex++; // right node
                return elementIndex;
            }
            elementIndex += 2;
        }
        
        return -1;
    };
};
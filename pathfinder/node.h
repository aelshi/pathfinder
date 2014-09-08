#ifndef __pathfinder__node__
#define __pathfinder__node__

#include <iostream>

class node {

public:
    
    int x, y;
    float f;
    int g;
    
    node()
    {
        node(0, 0);
    }
    
    node(int x, int y)
    {
        this->x = x;
        this->y = y;
        f = 0.0;
        g = 0;
    }
    
    node(int x, int y, float f)
    {
        this->x = x;
        this->y = y;
        this->f = f;
        g = 0;
    }
    
    bool operator==(const node &a) const {
        if (a.x==x && a.y== y)
            return true;
        else
            return false;
    }
    
     
    node& operator= (const node& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            f = other.f;
            g = other.g;
        }

        return *this;
    }
    
    bool operator < (const node& target) const{
        if( f < target.f ) {
            return true;
        } else if( f > target.f ) {
            return false;
        }

        if(x < target.x) {
            return true;
        } else if(x > target.x) {
            return false;
        } else {
            return (y < target.y);
        }
    }
    
    
    friend std::ostream& operator << (std::ostream &output, const node& n)
    {
        return output << "(x, y, f) - ( " << n.x << " , " << n.y << " , " << n.f << " ) " << "\n";
    }
    
};

struct minComparison
{
    bool operator()(const node& a, const node& b) const
    {
        if( a.f > b.f ) {
            return true;
        } else if( a.f < b.f ) {
            return false;
        }
        if(a.x > b.x) {
            return true;
        } else if(a.x < b.x) {
            return false;
        } else {
            return (a.y > b.y);
        }
        
    }
};



#endif /* defined(__pathfinder__node__) */

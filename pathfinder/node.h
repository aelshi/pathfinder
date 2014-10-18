#pragma once

#include <iostream>

class node {

public:
    
    int x, y;
    float f;
    int g;
    
    node()
    {
        x = 0;
        y = 0;
        f = 0.0f;
        g = 0;
    }
    
    node(int x, int y)
    {
        this->x = x;
        this->y = y;
        f = 0.0f;
        g = 0;
    }
    
    node(int x, int y, float f)
    {
        this->x = x;
        this->y = y;
        this->f = f;
        g = 0;
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
    
    node& operator= (const float& ff)
    {
        f = ff;
        return *this;
    }
    
    node& operator= (const int& ff)
    {
        f = (float)ff;
        return *this;
    }
    
    bool operator==(const node &a) const
    {
        return (a.f==f && a.f== f);
    }
    
    bool operator==(const float &ff) const
    {
        return (f == ff);
    }
    
    bool operator==(const int &ff) const
    {
        return (f == (float)ff);
    }
    
    bool operator!= (const float& ff) const
    {
        return !(f == ff);
    }
    
    bool operator!= (const int& ff) const
    {
        return !(f == (float)ff);
    }
    
    bool operator < (const node& target) const
    {
        return f < target.f;
    }
    
    bool operator > (const node& target) const
    {
        return f > target.f;
    }
    
    bool operator >= (const node& target) const
    {
        return f >= target.f;
    }
    
    bool operator <= (const node& target) const
    {
        return f <= target.f;
    }
    
    bool operator < (const float ff) const
    {
        return f < ff;
    }
    
    void print() const
    {
        std::cout<<"(x, y, f) - ( " << this->x << " , " << this->y << " , " << this->f << " ) " << "\n";
    }
    
    friend std::ostream& operator << (std::ostream &output, const node& n)
    {
        //return output << "(x, y, f) - ( " << n.x << " , " << n.y << " , " << n.f << " ) " << "\n";
        return output << n.f;
    }
    
};

struct minComparison
{
    bool operator()(const node& a, const node& b) const
    {
        //return a.f > b.f;
        
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
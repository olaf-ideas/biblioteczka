#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x, y;
    bool operator==(const Point& p) const {return x == p.x && y == p.y;}
    bool operator< (const Point& p) const {return (x==p.x)?y<p.y:x<p.x;}
    Point operator-(const Point& p) const {return Point{x - p.x, y - p.y};}
    int operator*(const Point& p) const {return x*p.y - y * p.x;}
    
    static int norm(const Point& p){
        return p.x * p.x + p.y * p.y;
    }
    static double abs(const Point& p){
        return sqrt(norm(p));
    }
    static bool left(const Point& a,
                     const Point& b,
                     const Point& c){
        return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x) < 0;
    }
    static double dist(const Point& a, const Point& b){
        return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
    }
};

struct Line{
    Point a, b;
    bool operator==(const Line& l) const {return a == l.a && b == l.b;}
    static double dist(const Line& l, const Point& p){
        int x = l.a.x - l.b.x, y = l.a.y - l.b.y;
        return abs(y*(l.a.x-p.x) + x*(p.y-l.a.y)) / sqrt(x*x+y*y);
    }
};

struct Polygon{
    vector<Point> circuit;

    double area(){
        int res = 0;
        for(int i = 0; i < (int)circuit.size()-1; i++)
            res += circuit[i] * circuit[i+1];
        res += circuit.back() * circuit.front();
        return (double)res/2;
    }

    static Polygon convex_hull(vector<Point>& ps){
        Polygon res;
        sort(ps.begin(), ps.end());

        for(const Point& p : ps){
            while(res.circuit.size() >= 2 && 
                Point::left(res.circuit[res.circuit.size()-2],res.circuit.back(),p))  
                res.circuit.pop_back();
            res.circuit.push_back(p);
        }

        for(int i = (int)ps.size()-2, d = (int)res.circuit.size(); i >= 0; i--){
            while(res.circuit.size() > d && 
                Point::left(res.circuit[res.circuit.size()-2],res.circuit.back(),ps[i]))   
                res.circuit.pop_back();
            res.circuit.push_back(ps[i]);
        }
        res.circuit.pop_back();
        return res;
    } 

    static double max_dist(const Polygon& p){
        double res = 0;
        int s = (int)p.circuit.size(), i = s-1, j = 0;
        while(Line::dist(Line{p.circuit[i], p.circuit[(i+1)%s]}, p.circuit[(j+1)%s]) > 
              Line::dist(Line{p.circuit[i], p.circuit[(i+1)%s]}, p.circuit[j]))
            j = (j+1)%s;
        for(;;){
            i = (i+1)%s;
            res = max(res, Point::dist(p.circuit[i], p.circuit[j]));
            while(Line::dist(Line{p.circuit[i], p.circuit[(i+1)%s]}, p.circuit[(j+1)%s]) > 
                  Line::dist(Line{p.circuit[i], p.circuit[(i+1)%s]}, p.circuit[j]) && 
                  j != 0)
                j = (j+1)%s;
            if(j == 0)  break;
        }
        return res;
    }
};

struct Map{
    vector<Point> p;
    // to implement:
    // > zamiatansko
    // > mst
    // > ...
};
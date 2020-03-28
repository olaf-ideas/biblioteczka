#include <bits/stdc++.h>
using namespace std;

template<class T> struct mono_queue{
    deque<T> d, q;
    void push(T x){
        while(!d.empty() && x > d.back())   d.pop_back();
        d.push_back(x);
        q.push_back(x);
    }

    void pop(){
        if(d.front() == q.front())  d.pop_front();
        q.pop_front();
    }

    T top(){return d.front();}
    T front(){return q.front();}
    bool empty(){return q.empty();}
    size_t size(){return q.size();}
};